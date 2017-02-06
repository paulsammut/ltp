#ifndef LTP_MANAGER_H
#define LTP_MANAGER_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

namespace Ui {
class LTP_Manager;
}

class LTP_Manager : public QMainWindow
{
    Q_OBJECT

public:
    explicit LTP_Manager(QWidget *parent = 0);
    ~LTP_Manager();

private slots:
    //    void writeData(const QByteArray &data);
    void readData();

    void on_button_Quit_clicked();

    void on_button_Connect_clicked();

    void on_button_Disconnect_clicked();

private:
    Ui::LTP_Manager *ui;
    QSerialPort *serial;
    bool portOpen;

};

#endif // LTP_MANAGER_H
