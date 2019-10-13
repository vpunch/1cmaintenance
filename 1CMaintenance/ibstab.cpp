#include "ibstab.h"

#include <QDebug>


IBsTab::IBsTab(const CommonParam* comParam, QWidget* parent) : QWidget(parent)
{
    ibsModel = new QStandardItemModel(this);

    ibsView = new QListView;
    ibsView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ibsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ibsView->setModel(ibsModel);
    ibsView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ibsView, &QListView::customContextMenuRequested, this, &IBsTab::showMenu);
    connect(ibsView->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &IBsTab::fillDescWgt);

    descWgt = new IBDescWgt(comParam);
    connect(descWgt, &IBDescWgt::descChanged, this, &IBsTab::acceptChange);

    QSplitter* splt = new QSplitter;
    splt->addWidget(ibsView);
    splt->addWidget(descWgt);

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(splt);
    setLayout(lay);

    loadIBs();
    readIBs();
}

void IBsTab::acceptChange(const QString& ibName, const IBDesc& data)
{
    const QModelIndex& cur = ibsView->currentIndex();
    ibsModel->itemFromIndex(cur)->setIcon(QIcon());
    ibsModel->setData(cur, ibName, Qt::DisplayRole);
    ibsModel->setData(cur, QVariant::fromValue(data), DescRole);
}

void IBsTab::loadIBs()
{
    QSettings s;

    size_t size = s.beginReadArray("ibs");

    for (size_t i = 0; i < size; ++i) {
        s.setArrayIndex(i);

        const QString& ibName = s.value("ibName").toString();
        IBDesc desc = {
            .isTmp = false,
            .user = s.value("user").toString(),
            .pass = s.value("pass").toString(),
            .dbs = s.value("dbs").toString()
        };

        auto item = new QStandardItem(ibName);
        item->setData(QVariant::fromValue<IBDesc>(desc));
        ibsModel->appendRow(item);
    }
    s.endArray();
}

void IBsTab::readIBs()
{
    for (size_t i = 0; i < ibsModel->rowCount(); i++) {
        QStandardItem* item = ibsModel->item(i);
        const IBDesc& ibdesc = item->data().value<IBDesc>();

        if (ibdesc.isTmp)
            ibsModel->removeRow(i);
    }

#ifdef Q_OS_WIN
    const QString& roaming = qEnvironmentVariable("APPDATA");
    QString fname = roaming + "\\1C\\1CEStartt\\ibases.v8i";
#endif

    QFile file(fname);
    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream text(&file);
    text.setCodec(QTextCodec::codecForName("UTF-8"));

    QString group;
    while (!text.atEnd()) {
        const QString& line = text.readLine().trimmed();

        if (line.startsWith('[')) {
            int len = line.indexOf(']') - 1;
            group = line.mid(1, len);

            if (ibsModel->findItems(group).isEmpty()) {
                IBDesc desc = {
                    .isTmp = true,
                    .dbs = "1C"
                };

                auto item = new QStandardItem(QIcon(":/question.svg"), group);
                item->setData(QVariant::fromValue<IBDesc>(desc));

                ibsModel->appendRow(item);
            }

            continue;
        }

        auto pair = line.split("=");
        if (pair.size() > 1) {
        }
    }
}

void IBsTab::saveIBs()
{
    QSettings s;

    s.beginWriteArray("ibs");
    for (size_t i = 0, j = 0; i < ibsModel->rowCount(); ++i) {
        QStandardItem* item = ibsModel->item(i);

        const QString& ibName = item->text();
        const IBDesc& desc = item->data().value<IBDesc>();

        if (!desc.isTmp) {
            s.setArrayIndex(j++);
            s.setValue("ibName", ibName);
            s.setValue("user", desc.user);
            s.setValue("pass", desc.pass);
            s.setValue("dbs", desc.dbs);
        }
    }
    s.endArray();

    s.sync();
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
    const IBDesc& data = cur.data(DescRole).value<IBDesc>();

    descWgt->fill(ibName, data);
}

IBsTab::~IBsTab()
{
    saveIBs();
}
