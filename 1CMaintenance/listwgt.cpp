#include "listwgt.h"


ListWgt::ListWgt(QAbstractItemView* listView, QWidget* parent) : QWidget(parent)
{
    this->listView = listView;

    listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(listView, &QAbstractItemView::customContextMenuRequested,
            this, &ListWgt::showMenu);

    QAction* addAct = areaMenu.addAction(QIcon(":/plus.svg"), "Добавить");
    connect(addAct, &QAction::triggered, this, &ListWgt::add);
    itemMenu.addAction(addAct);

    QAction* removeAct = itemMenu.addAction("Удалить");
    connect(removeAct, &QAction::triggered, this, &ListWgt::remove);
}

void ListWgt::showMenu(const QPoint& pos)
{
    QPoint globalPos = listView->mapToGlobal(pos);
    const QModelIndex& pointedIdx = listView->indexAt(pos);

    if (!pointedIdx.isValid())
        areaMenu.exec(globalPos);
    else
        itemMenu.exec(globalPos);
}

void ListWgt::updateList()
{
    QAbstractItemModel* model = listView->model();
    int curRow = listView->currentIndex().row();

    model->removeRows(0, model->rowCount());

    loadList();

    curRow = std::min(curRow, model->rowCount() - 1);
    if (curRow >= 0)
        listView->setCurrentIndex(model->index(curRow, 0));
}
