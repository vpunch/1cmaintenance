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

    descWgt = new IBDescWgt(stor);
    connect(descWgt, &IBDescWgt::descChanged, this, &IBsTab::acceptChange);

    auto splt = new QSplitter;
    splt->addWidget(ibsView);
    splt->addWidget(descWgt);

    auto lay = new QVBoxLayout;
    lay->addWidget(splt);
    setLayout(lay);

    updateIBs();
}

void IBsTab::updateIBs()
//вызывать этот метод, loadIBs и readIBs вспомогательные
{
    ibsModel->clear();
    loadIBs();
    readIBs();
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
#ifdef Q_OS_WIN
    const QString& roaming = qEnvironmentVariable("APPDATA");
    QString fname = roaming + "\\1C\\1CEStartt\\ibases.v8i";
#endif

    QFile file(fname);
    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream text(&file);
    text.setCodec("UTF-8");

    QString group;
    while (!text.atEnd()) {
        const QString& line = text.readLine().trimmed();

        if (line.startsWith('[')) {
            int len = line.indexOf(']') - 1;
            group = line.mid(1, len);

            if (ibsModel->findItems(group).isEmpty()) {
                IBDesc desc {
                    .tmp = true,
                    .dbs = "1C"
                };

                auto item = new QStandardItem(QIcon(":/question.svg"), group);
                item->setData(QVariant::fromValue<IBDesc>(desc));

                ibsModel->appendRow(item);
            }

            continue;
        }

        QStringList pair = line.split("=");
        if (pair.size() > 1) {
        }
    }
}

void IBsTab::showMenu(const QPoint& pos)
{
    QPoint globalPos = ibsView->mapToGlobal(pos);

    QMenu areaMenu;
    QAction* addAct = areaMenu.addAction(QIcon(":/plus.svg"), "Добавить");

    //QMenu itemMenu;
    //QAction* removeAct = menuForItem.addAction("Удалить");
    //сохранить

    const QModelIndex& pointedIdx = ibsView->indexAt(pos);

    QAction* selectedAct;
    if (!pointedIdx.isValid()) {
        selectedAct = areaMenu.exec(globalPos);

        if (selectedAct) {
            if (selectedAct == addAct) {
            }
        }
    }
    else {

    }
}

void IBsTab::fillDescWgt(const QModelIndex& cur, const QModelIndex&)
{
    const QString& ibName = cur.data().toString();
    const IBDesc& data = cur.data(Qt::UserRole + 1).value<IBDesc>();

    descWgt->fill(ibName, data);
}
