#ifndef TASKSTAB_H
#define TASKSTAB_H

#include <QTreeView>
#include <QWizard>
#include <QPushButton>
#include <QVBoxLayout>

#include <QStandardItemModel>


class TasksTab : public QWidget {
    Q_OBJECT

public:
    TasksTab(QWidget* parent = nullptr);
};

#endif //TASKSTAB_H
