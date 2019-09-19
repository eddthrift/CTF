#include "ControlWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ControlWindow w;
    w.show();                   //Opens ControlWindow
    return a.exec();
}
