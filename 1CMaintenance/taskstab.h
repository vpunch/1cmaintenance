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
    QStandardItemModel* model;

    void add() override;
    void remove() override;

    void loadList() override;

public:
    TasksTab(Storage* stor, QWidget* parent = nullptr);
};

#endif //TASKSTAB_H
