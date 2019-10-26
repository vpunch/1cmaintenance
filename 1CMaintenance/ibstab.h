#ifndef IBSTAB_H
#define IBSTAB_H

#include <QSplitter>
#include <QListView>
#include <QScrollArea>

#include <QVBoxLayout>
#include <QStandardItem>

#include "ibdescwgt.h"
#include "listwgt.h"
#include "storage.h"


class IBsTab : public ListWgt {
    Q_OBJECT

    Storage* stor;

    QStandardItemModel* ibsModel;
    QListView* ibsView;

    IBDescWgt* descWgt;

    void readIBs();

    void add() override;
    void remove() override;

    void loadList() override;

private slots:
    void fillDescWgt(const QModelIndex& cur, const QModelIndex&);
    void acceptChange(const QString& ibName, const IBDesc& data);

public:
    explicit IBsTab(Storage* stor, QWidget* parent = nullptr);

    void updateList() override;

public slots:
    void updateCommon();
};

#endif //IBSTAB_H
