#ifndef IBSTAB_H
#define IBSTAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QListView>
#include <QMenu>

#include <QFile>
#include <QStandardItem>
#include <QTextStream>

#include "ibdescwgt.h"
#include "storage.h"


class IBsTab : public QWidget {
    Q_OBJECT

    Storage* stor;
    QStandardItemModel* ibsModel;
    QListView* ibsView;
    IBDescWgt* descWgt;

    void readIBs();
    void loadIBs();

    void showMenu(const QPoint& pos);
    void fillDescWgt(const QModelIndex& cur, const QModelIndex&);
    void acceptChange(const QString& ibName, const IBDesc& data);

public:
    explicit IBsTab(Storage* stor, QWidget* parent = nullptr);

    void updateIBs();
};

#endif // IBSTAB_H
