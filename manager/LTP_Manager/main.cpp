#include "ltp_manager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LTP_Manager w;
    w.show();

    return a.exec();
}
