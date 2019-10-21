#ifndef TASKSTAB_H
#define TASKSTAB_H

#include <QTreeView>
#include <QPushButton>

#include <QVBoxLayout>
#include <QStandardItemModel>

#include "listwgt.h"
#include "storage.h"
#include "taskwizard.h"


class TasksTab : public ListWgt {
    Q_OBJECT

    Storage* stor;

    QTreeView* table;

    void add() override;
    void remove() override;

    void updateTasks();

public:
    TasksTab(Storage* stor, QWidget* parent = nullptr);
};

#endif //TASKSTAB_H
