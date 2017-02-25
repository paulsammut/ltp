# The Lidar Test Platform
Rev1-2/25/2017

The Lidar Test Platform, or LTP is a low cost LIDAR system. Its main goal is to give Sammut Tech LLC the ability to have multiple LIDAR units at low cost, which are necassary for rapid and cost effective development of TD1.

The LTP system has the following features:

* Cost under 500 dollars
* Capable of close to 500 Hz sampling rate (per point)
* Up to 1000 RPM head rotation whic gives a full 360 degree scan at 15Hz
* The head can be set a desired fixed tilt
* Closed loop PID control of head position


## General overview
![Diagram of the LTP][overview]
The LTP has a head that can spin around continuously and acquire distance and angle measurements. 
There is a [custom build circuit board](https://workspace.circuitmaker.com/Projects/Details/Paul-Sammut-2/LTP-Board) that takes in power and has a USB connector to interface with a computer. Communications to and from the LTP is done as binary data encoded with COBS. 

![Functional overview of the LTP][func-overview]

The LTP sends LtpSamples over serial asynchronously as fast as it can. The LTP can also be commanded to stop, spin, go to a position, or follow a sweep profile at a set frequency. 

### LTP Lidar Head
The head contains a [Garmin LIDAR-Lite V3](https://buy.garmin.com/en-US/US/p/557294). It spins on an a hollow 8mm shaft with wires going through a [slip ring](http://www.digikey.com/product-detail/en/adafruit-industries-llc/736/1528-1152-ND/5353612).

### USB Serial Data Connection
The USB connection is handled through an [FTDI232RL usb - uart controller](http://www.ftdichip.com/Support/Documents/DataSheets/ICs/DS_FT232R.pdf) and the computer sees it as serial port. Data rate is 230800 baud, which takes about 300-500us to transfer an LtpSample packet (see below). Data to and from the LTP is sent as COBS encoded binary data. Thee reason it is sent as binary and not ASCII is to minize packet length. The reason COBS is uses is to have a unique packet delimeter which allows for a robust and quick method of identifying packets in a potentially interruptable UART stream. 

![LtpSample packet being sent over UART takes only 300us!][scope_serial_packet]

### Motor
The LTP was designed to be able to work with a variety of cheap brushed DC motors. Because the LTP has as a closed loop PID control along with space for the user to place timing belt pulleys of varying gear ratios, motors of varying no-load shaft RPMs can be selected. As a general rule of thumb, a motor's power can be roughly estimated by the size of it's shaft. A motor with a shaft of 3mm - 4mm is recommended, which is in the neighborhood of 50-100 watts. 

## Reference Frames
The LTP's job is to give us LIDAR hits, which are a points in space. For points in space to mean anything, they need to be in a reference frame. The LTP uses two reference frames.
* Internal reference frame used in the LtpSample
* LTP_Body reference frame used in the LtpHitXyz

### Internal Reference Frame
![Internal reference frame of the LTP][internal_reference_1]
This reference frame is used by the firmware for its calculations and also during LTP to Host communication. This reference frame has two components:
* Head angle in 0-3999 encoder counts. Increments clockwise.
* Distance in 0-4000 centimeters. 
* Head tilt phi
![Head tilt of LTP][internal_reference_2]
The user does not have to worry about this reference frame as it is handled by the lower level code. Conversion from this to LtpHitXyz is done with simple [spherical coordinate to cartesian coordinate transform math](http://mathinsight.org/spherical_coordinates). 

### LTP_Body Reference Frame
![LTP_Body reference frame][LTP_Body_reference_frame]
The LTP_Body reference frame is compatible with the ROS standard for vehicle coordinates. X is positive forward, Y is positive west, and Z is positive up. 
LtpHitXyz data is in this reference frame.

## Software
There is a set of software that is required for operation of the LTP. They are as follows:
* LTP Firmware that runs on the LTP Board
* LTP Host software that runs on a host computer and interfaces with the LTP

### UML Overview
![UML overview of LTP software][ltp_uml]
The firmware and host software share a header file that defines communications between the two.

### Host Software
The host is defined as the computer the LTP is connected to. Software written for the LTP Host has two functions:
* Decode packets coming from the LTP
* Allow commands to be send to the LTP

#### Decoding packets coming from the LTP
The LTP host software monitors the serial port and looks for an LtpMessage packet. This a packet of COBS encoded binary data that has 0x00 at the end of it. If a packet is received, it is decoded from COBS and converted it to an X, Y, Z LIDAR hit location. This hit location is defined as an LtpHitXyz data structure. 
![PollRead() of LTP][ltp::pollread]

#### Sending Commands to the LTP
Commands to the LTP are done via LtpCommand structers serialized into a byte array and encoded with COBS and then sent over the UART. 

### LTP Firmware
The LTP Board contains a PIC24FV16KM204 microntroller. Firmare for this chip was written in MplabX using the C30 compiler. The firmware handles the following operation:
* Setup on the various subsystems for proper configurations
* Monitor the serial port for any commands
* Operate a state machine in three modes:
    * Spin: A constant signal is given and head spins
    * Position: An angular position is given and the head, using a PID loop, goes to that position and stays there
    * Sweep: A start angle, end angle, and frequency is given and the head follows that generated sweep signal
* Sample the lidar and send out raw LTP Samples over the UART as fast as it can

This microcontroller communicates to the following systems: 
* DRV8801 motorcontroller via PWM singal and direction digital line
* LFLS7366R encoder processor chip via SPI
* LIDAR-Lite V3 via I2C
* FT242RL via UART


The firmware generates raw LTP sample packets, encodes them in COBS and sends them over UART as fast as it can. 
The firmware also monitors the UART for incoming control packets encoded in COBS. 
The firmware uses the LtpMessage.h file for definition of the structure used for communication over the wire.



[overview]: http://i.imgur.com/LRjJuDY.png
[func-overview]: http://i.imgur.com/LEC2WGl.png
[scope_serial_packet]:http://imageshack.com/a/img923/8107/ma0xyx.png
[internal_reference_1]:http://imageshack.com/a/img921/6228/4nVc99.png
[internal_reference_2]: http://imageshack.com/a/img923/9338/u3L9cl.png
[LTP_Body_reference_frame]:http://imageshack.com/a/img922/7089/RiCDlJ.png
[ltp::pollread]:http://imageshack.com/a/img924/605/cw8iT9.png
[ltp_uml]:http://imageshack.com/a/img924/8889/jINLZ6.png
