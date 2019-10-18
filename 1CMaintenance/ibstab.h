#ifndef IBSTAB_H
#define IBSTAB_H

#include <algorithm>

#include <QVBoxLayout>
#include <QSplitter>
#include <QListView>
#include <QMenu>
#include <QScrollArea>

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

    /*
     * Вспомогательные методы, используй updateIBs вместо них
     */
    void readIBs();
    void loadIBs();

public:
    explicit IBsTab(Storage* stor, QWidget* parent = nullptr);

    void updateIBs();
    void acceptChange(const QString& ibName, const IBDesc& data);

protected slots:
    void showMenu(const QPoint& pos);
    void fillDescWgt(const QModelIndex& cur, const QModelIndex&);
//    void acceptChange(const QString& ibName, const IBDesc& data);
};

#endif // IBSTAB_H
