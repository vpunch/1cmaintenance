#include "taskstab.h"

#include <QDebug>


TasksTab::TasksTab(Storage* stor, QWidget* parent)
    : ListWgt(new QTreeView, parent)
{
    this->stor = stor;

    auto model = new QStandardItemModel(0, 4);
    QStringList cols = {"", "Инф. базы", "Операции", "Время"};
    for (int i = 0; i < cols.size(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, cols[i], Qt::DisplayRole);
    }

    table = (QTreeView*)listView;
    table->setModel(model);

    auto lay = new QVBoxLayout;
    lay->addWidget(table);
    this->setLayout(lay);

    updateTasks();
}

void TasksTab::add()
{
    TaskWizard wiz(stor, this);

    connect(&wiz, &QDialog::accepted, this, [this] {
        updateTasks();
    });

    wiz.exec();
}

void TasksTab::remove()
{
}

void TasksTab::updateTasks()
{

}
