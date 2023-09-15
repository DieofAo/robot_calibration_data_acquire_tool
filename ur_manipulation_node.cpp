#include <QApplication>
#include "ur_test.h"
//https://github.com/xpharry/ros-qt-gui

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    ur_test w(argc, argv);
    w.setWindowTitle("Robot control");
    w.show();
    return a.exec();
}
