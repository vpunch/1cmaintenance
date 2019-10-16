#include "mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setMinimumSize(rot::point2px(500), rot::point2px(300));

    auto ibsTab = new IBsTab(&stor);

    auto comTab = new CommonTab;

    auto tasksTab = new TasksTab;

    auto logTab = new QTextEdit;

    auto cenWgt = new QTabWidget;
    cenWgt->addTab(ibsTab, "Инф. базы");
    cenWgt->addTab(comTab, "Общее");
    cenWgt->addTab(tasksTab, "Задачи");
    cenWgt->addTab(logTab, "Журнал"); //информация о выполнении задач, прочие ошибки в другом

    this->setCentralWidget(cenWgt);
}
