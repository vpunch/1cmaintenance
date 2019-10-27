#ifndef TASKSTAB_H
#define TASKSTAB_H

#include <QTreeView>
#include <QPushButton>

#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QProcess>
#include <QInputDialog>

#include "listwgt.h"
#include "storage.h"
#include "taskwizard.h"
#include "global.h"

#include <Windows.h>
#define SECURITY_WIN32
#include <Security.h>
#include <Lmcons.h>


class TasksTab : public ListWgt {
    Q_OBJECT

    Storage* stor;

    QTreeView* table;
    QStandardItemModel* model;

    void add() override;
    void remove() override;

    void loadList() override;

public:
    TasksTab(Storage* stor, QWidget* parent = nullptr);
};

#endif //TASKSTAB_H
