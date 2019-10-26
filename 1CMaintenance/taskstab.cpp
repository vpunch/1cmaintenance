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

    updateList();
}

void TasksTab::add()
{
    TaskWizard wiz(stor, this);

    connect(&wiz, &QDialog::accepted, this, [this] {
        updateList();
    });

    wiz.exec();
}

void TasksTab::remove()
{
    QModelIndex headIdx = model->index(table->currentIndex().row(), 0);
    const QString uuid = model->data(headIdx, Qt::UserRole + 1).toString();
    stor->removeTask(uuid);
    updateList();
}

void TasksTab::loadList()
{
    for (auto batch : stor->getTasks()) {
        QList<QStandardItem*> items;

        auto headItem = new QStandardItem(batch.ibs.join(", "));
        headItem->setData(batch.uuid);
        items.append(headItem);

        items.append(new QStandardItem(batch.ops.join(", ")));


//parse time
        std::map<uint, QString> weekMap = {
            {0, "вс."},
            {1, "пн."},
            {2, "вт."},
            {3, "ср."},
            {4, "чт."},
            {5, "пт."},
            {6, "сб."}
        };

        QStringList timeSects = batch.time.split(' ');

        QString time = timeSects[1] + ":" + timeSects[0];

        if (timeSects[2] != "*") {
            time += " " + timeSects[2];
        }
        else {
            QStringList weeks;
            for (const QString& weekN : timeSects[4].split(","))
                weeks << weekMap[weekN.toUInt()];
            time += " " + weeks.join(",");
        }

        items.append(new QStandardItem(time));


        model->appendRow(items);
    }
}
