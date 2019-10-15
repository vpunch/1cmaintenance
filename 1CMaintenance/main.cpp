#include <QApplication>
#include <QDir>
#include <QStandardPaths>

#include "mainwindow.h"

//#include <QDebug>


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QApplication::setOrganizationName("Rot");
    QApplication::setApplicationName("1CMaintenance");
    QDir().mkpath(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

    if (argc > 1) {
    }

    MainWindow w;
    w.show();

    return a.exec();
}
