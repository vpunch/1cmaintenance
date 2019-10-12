#include "mainwindow.h"

//#include <QDebug>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{


    IBsTab* ibsTab = new IBsTab;

    QTabWidget* cenWgt = new QTabWidget;
    cenWgt->addTab(ibsTab, "Базы");

    this->setCentralWidget(cenWgt);
}

MainWindow::~MainWindow()
{
}
