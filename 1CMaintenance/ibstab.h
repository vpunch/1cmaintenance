#ifndef IBSTAB_H
#define IBSTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QListView>
#include <QMenu>

#include <QSettings>
#include <QTextCodec>
#include <QFile>
#include <QStandardItem>
#include <QTextStream>

#include "ibdescwgt.h"
#include "commontab.h"


class IBsTab : public QWidget {
    Q_OBJECT

    Qt::ItemDataRole DescRole = (Qt::ItemDataRole)(Qt::UserRole + 1);

    QStandardItemModel* ibsModel;

    QListView* ibsView;
    IBDescWgt* descWgt;

    void readIBs();
    void saveIBs();
    void loadIBs();

    void showMenu(const QPoint& pos);
    void fillDescWgt(const QModelIndex& cur, const QModelIndex&);
    void acceptChange(const QString& ibName, const IBDesc& data);

public:
    // IBsTab владеет указателем и сам заботится об уничтожении объекта
    const QStandardItemModel* getIBsModel() const {return ibsModel;}

    explicit IBsTab(const CommonParam* comParam, QWidget* parent = nullptr);
    ~IBsTab();
};

#endif // IBSTAB_H
