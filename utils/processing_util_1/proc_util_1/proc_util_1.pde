import processing.serial.*;

Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
float inLIDAR = 0;
float inEncoder =0;
float x = 0;
float y = 0;

int arrayLength =200;
float[][] myArray = new float[arrayLength][2];

PFont f;

void setup () {
    f = createFont("Arial",16,true); // STEP 2 Create Font
    // set the window size:
    fullScreen();

    // List all the available serial ports
    // if using Processing 2.1 or later, use Serial.printArray()
    println(Serial.list());

    // I know that the first port in the serial list on my mac
    // is always my  Arduino, so I open Serial.list()[0].
    // Open whatever port is the one you're using.
    myPort = new Serial(this, Serial.list()[0], 115200);

    // don't generate a serialEvent() unless you get a newline character:
    myPort.bufferUntil('\n');

    // set inital background:
    background(0);
    translate(width/2, height/2);
    ellipseMode(CENTER);
    noStroke();
    fill(200);
}

void draw () {
    background(0);
    translate(width/2, height/2);

    // This is for creating different colors based on how new the point is. 
    for (int i = 0; i< arrayLength; i++) {
        int curColor = (int) map(i, 0,arrayLength, 0, 255);
        fill(255 - curColor, curColor, i);
        ellipse(myArray[i][0], myArray[i][1], 5, 5);
    }

    textFont(f,16);                // STEP 3 Specify font to be used
    fill(0, 255, 0);               // STEP 4 Specify font color
    text(inEncoder,-1000,-1000);   // STEP 5 Display Text
}


void serialEvent (Serial myPort) {
    // get the ASCII string:
    String inString = myPort.readStringUntil('\n');

    if (inString != null) {
        // trim off any whitespace:
        inString = trim(inString);

        String[] tempS = split(inString, ',');
        //printArray(tempS);
        if(tempS.length == 2) {
            // convert to an int and map to the screen height:
            inLIDAR = float(tempS[0]);
            inEncoder = float(tempS[1]);

            //Handle zeros
            if(inEncoder > 0)
                inEncoder = inEncoder/2000*3.14159;


            x = inLIDAR * cos(inEncoder);
            y = inLIDAR * sin(inEncoder);
            
            // Shift array. We want the freshest value at 0
            for(int i = arrayLength-1; i > 0; i--)
            {
                myArray[i][0] = myArray[i-1][0];
                myArray[i][1] = myArray[i-1][1];
            }

            myArray[0][0] = x;
            myArray[0][1] = y;

            println(myArray[0][0] + " " + myArray[0][1]);
        }
    }
}