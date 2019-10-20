#ifndef TASKSTAB_H
#define TASKSTAB_H

#include <QTreeView>
#include <QWizard>
#include <QPushButton>
#include <QCheckBox>
#include <QTimeEdit>
#include <QLabel>
#include <QComboBox>
#include <QStackedWidget>

#include <QVBoxLayout>
#include <QStandardItemModel>
#include <QGridLayout>

#include "listwgt.h"
#include "storage.h"
#include "global.h"


class TasksTab : public ListWgt {
    Q_OBJECT

    Storage* stor;

    QTreeView* table;

    void add() override;
    void remove() override;

public:
    TasksTab(Storage* stor, QWidget* parent = nullptr);
};

#endif //TASKSTAB_H
