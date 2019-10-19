#ifndef IBSTAB_H
#define IBSTAB_H

#include <algorithm>

#include <QSplitter>
#include <QListView>
#include <QMenu>
#include <QScrollArea>

#include <QVBoxLayout>
#include <QStandardItem>

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

private slots:
    void showMenu(const QPoint& pos);
    void fillDescWgt(const QModelIndex& cur, const QModelIndex&);
    void acceptChange(const QString& ibName, const IBDesc& data);

public:
    explicit IBsTab(Storage* stor, QWidget* parent = nullptr);

    void updateIBs();

public slots:
    void updateCommon();
};

#endif //IBSTAB_H
