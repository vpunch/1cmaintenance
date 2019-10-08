#include "mainwindow.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();

    /*
     * Перенести разработку на Windows, установить туда 1С
     * Протестировать парсинг файла
     * Таб Общие
     * Сохранение параметров
     * Таб задачи со специфик кодом
     */
}
