#include "ltp_manager.h"
#include "ui_ltp_manager.h"

#include <QtSerialPort/QSerialPort>


LTP_Manager::LTP_Manager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LTP_Manager)
{
    ui->setupUi(this);
    portOpen = false;

    // new serial port
    serial = new QSerialPort(this);
    ui->button_Connect->setEnabled(true);
    ui->button_Disconnect->setEnabled(false);

    connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
}

LTP_Manager::~LTP_Manager()
{
    delete ui;
    if(portOpen)
        serial->close();
}

void LTP_Manager::on_button_Quit_clicked()
{
    qApp->quit();
}

void LTP_Manager::on_button_Connect_clicked()
{
    serial->setPortName("/dev/ttyACM0");
    serial->setBaudRate(115200);
    serial->open(QIODevice::ReadWrite);
    ui->button_Connect->setEnabled(false);
    ui->button_Disconnect->setEnabled(true);
}

void LTP_Manager::on_button_Disconnect_clicked()
{
     serial->close();
     ui->button_Connect->setEnabled(true);
     ui->button_Disconnect->setEnabled(false);
}

void LTP_Manager::readData()
{
    QByteArray data = serial->readAll();
    ui->textBox->setText(data.toHex());
}


