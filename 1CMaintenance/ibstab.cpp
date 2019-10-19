#include "ibstab.h"

#include <QDebug>


IBsTab::IBsTab(Storage* stor, QWidget* parent) : QWidget(parent)
{
    this->stor = stor;

    ibsModel = new QStandardItemModel(this);

    ibsView = new QListView;
    ibsView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ibsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ibsView->setModel(ibsModel);
    ibsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ibsView, &QListView::customContextMenuRequested, this, &IBsTab::showMenu);
    connect(ibsView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &IBsTab::fillDescWgt);
    ibsView->setMinimumWidth(200);

    descWgt = new IBDescWgt(stor);
    connect(descWgt, &IBDescWgt::descChanged, this, &IBsTab::acceptChange);

    auto descArea = new QScrollArea;
    descArea->setWidgetResizable(true);
    descArea->setWidget(descWgt);

    auto splt = new QSplitter;
    splt->addWidget(ibsView);
    splt->addWidget(descArea);
    splt->setStretchFactor(0, 0);
    splt->setStretchFactor(1, 1);

    auto lay = new QVBoxLayout;
    lay->addWidget(splt);
    setLayout(lay);

    updateIBs();
}

void IBsTab::updateCommon()
{
    descWgt->loadCommon();
}

void IBsTab::updateIBs()
{
    int r = ibsView->currentIndex().row();

    ibsModel->clear();
    loadIBs();
    readIBs();

    r = std::min(r, ibsModel->rowCount() - 1);
    if (r < 0) {
        descWgt->setDisabled(true);
    } else {
        ibsView->setCurrentIndex(ibsModel->index(r, 0));
    }
}

void IBsTab::acceptChange(const QString& ibName, const IBDesc& data)
{
    const QModelIndex& cur = ibsView->currentIndex();

    bool ok = stor->saveIB(ibName, data, cur.data().toString());
    if (!ok) {
        //exit
    }

    updateIBs();
}

void IBsTab::loadIBs()
{
    const IBs& ibs = stor->getIBs();

    for (auto ib : ibs) {
        auto item = new QStandardItem(ib.first);
        item->setData(QVariant::fromValue<IBDesc>(ib.second));
        ibsModel->appendRow(item);
    }
}

void IBsTab::readIBs()
{
    rot::IBasesT ibases = rot::ibases();

    for (auto group : ibases) {
        for (auto pair : group.second) {
            if (pair.first == "Connect") {
                if (ibsModel->findItems(group.first).isEmpty()) {
                    IBDesc desc = {
                        .tmp = true
                    };

                    QStringList typeSection = pair.second.section(';', 0, 0).split('=');
                    if (typeSection[0] == "File") {
                        desc.dbs = "1С";
                        desc.path = typeSection[1].replace('"', "");
                    }
                    else { //typeSection[0] == "Srvr"
                        desc.dbs = descWgt->currentDBS(true);
                    }

                    auto item = new QStandardItem(QIcon(":/question.svg"), group.first);
                    item->setData(QVariant::fromValue<IBDesc>(desc));

                    ibsModel->appendRow(item);
                }
            }
        }
    }
}

void IBsTab::showMenu(const QPoint& pos)
{
    QMenu areaMenu;
    QAction* addAct = areaMenu.addAction(QIcon(":/plus.svg"), "Добавить");

    QMenu itemMenu;
    QAction* removeAct = itemMenu.addAction("Удалить");

    QPoint globalPos = ibsView->mapToGlobal(pos);
    const QModelIndex& pointedIdx = ibsView->indexAt(pos);

    QAction* selectedAct;
    if (!pointedIdx.isValid()) {
         selectedAct = areaMenu.exec(globalPos);

        if (selectedAct) {
            if (selectedAct == addAct) {
                QString baseName = "Информационная база";

                QString name = baseName;

                int i = 0;
                while (!ibsModel->findItems(name).isEmpty()) {
                    name = baseName + " #" + QString::number(++i);
                }

                IBDesc desc = {
                    .tmp = false,
                    .dbs = descWgt->currentDBS(),
                };

                stor->saveIB(name, desc);
                updateIBs();
            }
        }
    }
    else {
        selectedAct = itemMenu.exec(globalPos);

        if (selectedAct) {
            if (selectedAct == removeAct) {
                stor->deleteIB(pointedIdx.data().toString());
                updateIBs();
            }
        }
    }
}

void IBsTab::fillDescWgt(const QModelIndex& cur, const QModelIndex&)
{
    const QString& ibName = cur.data().toString();
    const IBDesc& data = cur.data(Qt::UserRole + 1).value<IBDesc>();

    descWgt->fill(ibName, data);

    descWgt->setDisabled(false);
}
