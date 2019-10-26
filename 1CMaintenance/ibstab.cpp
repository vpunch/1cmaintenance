#include "ibstab.h"

#include <QDebug>


IBsTab::IBsTab(Storage* stor, QWidget* parent)
    : ListWgt(new QListView, parent)
{
    this->stor = stor;

    ibsModel = new QStandardItemModel(this);

    ibsView = (QListView*)listView;
    ibsView->setModel(ibsModel);
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

    updateList();
}

void IBsTab::updateCommon()
{
    descWgt->loadCommon();
}

void IBsTab::updateList()
{
    ListWgt::updateList();

    if (!ibsView->currentIndex().isValid())
        descWgt->setDisabled(true);
}

void IBsTab::acceptChange(const QString& ibName, const IBDesc& data)
{
    const QModelIndex& cur = ibsView->currentIndex();

    bool ok = stor->saveIB(ibName, data, cur.data().toString());
    if (!ok) {
        //exit
    }

    updateList();
}

void IBsTab::loadList()
{
    const IBs& ibs = stor->getIBs();

    for (auto ib : ibs) {
        auto item = new QStandardItem(ib.first);
        item->setData(QVariant::fromValue<IBDesc>(ib.second));
        ibsModel->appendRow(item);
    }

    readIBs();
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

void IBsTab::add()
{
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
    updateList();
}

void IBsTab::remove()
{
    stor->removeIB(ibsView->currentIndex().data().toString());
    updateList();
}

void IBsTab::fillDescWgt(const QModelIndex& cur, const QModelIndex&)
{
    const QString& ibName = cur.data().toString();
    const IBDesc& data = cur.data(Qt::UserRole + 1).value<IBDesc>();

    descWgt->fill(ibName, data);

    descWgt->setDisabled(false);
}
