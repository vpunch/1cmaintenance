#include "taskstab.h"

#include <QDebug>


TasksTab::TasksTab(Storage* stor, QWidget* parent)
    : ListWgt(new QTreeView, parent)
{
    this->stor = stor;

    QStringList cols = {"Инф. базы", "Операции", "Время"};
    model = new QStandardItemModel(0, cols.size());
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
    QModelIndex headIdx = model->index(table->currentIndex().row(), 0);
    const QString uuid = model->data(headIdx, Qt::UserRole + 1).toString();
    stor->removeTask(uuid);
    updateTasks();
}

void TasksTab::updateTasks()
{
    int r = table->currentIndex().row();

    model->clear();
    loadTasks();

    r = std::min(r, model->rowCount() - 1);
    if (r >= 0) {
        table->setCurrentIndex(model->index(r, 0));
    }
}

void TasksTab::loadTasks()
{
    for (auto batch : stor->getTasks()) {
        QList<QStandardItem*> items;

        auto headItem = new QStandardItem(batch.ibs.join(", "));
        headItem->setData(batch.uuid);
        items.append(headItem);

        items.append(new QStandardItem(batch.ops.join(", ")));
        items.append(new QStandardItem(batch.time));

        model->appendRow(items);
    }
}
