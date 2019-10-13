#ifndef TASKSTAB_H
#define TASKSTAB_H

#include <QWidget>
#include <QTreeView>
#include <QWizard>

#include <QStandardItemModel>
#include <QVBoxLayout>


class TasksTab : public QWidget {
    Q_OBJECT

public:
    TasksTab(QWidget* parent = nullptr);
};

#endif // TASKSTAB_H
