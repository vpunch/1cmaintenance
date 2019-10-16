#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QTextEdit>

#include "ibstab.h"
#include "commontab.h"
#include "taskstab.h"
#include "storage.h"
#include "global.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

    Storage stor;

public:
    MainWindow(QWidget* parent = nullptr);
};

#endif // MAINWINDOW_H
