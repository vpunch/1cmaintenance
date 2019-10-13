#include "mainwindow.h"

#include <QDebug>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    CommonTab* comTab = new CommonTab;

    //разрушение в обратном порядке
    IBsTab* ibsTab = new IBsTab(comTab->getComParam());

    TasksTab* tasksTab = new TasksTab;

    QTextEdit* logTab = new QTextEdit;

    QTabWidget* cenWgt = new QTabWidget;
    cenWgt->addTab(ibsTab, "Инф. базы");
    cenWgt->addTab(comTab, "Общее");
    cenWgt->addTab(tasksTab, "Задачи");
    cenWgt->addTab(logTab, "Журнал");

    this->setCentralWidget(cenWgt);
}

MainWindow::~MainWindow()
{
}
