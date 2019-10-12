#include <QApplication>

#include "mainwindow.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("Rot");
    QApplication::setApplicationName("1CMaintenance");

    MainWindow w;
    w.show();

    return a.exec();
}
