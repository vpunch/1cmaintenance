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


class IBsTab : public QWidget {
    Q_OBJECT

    QListView* ibsView;
    QStandardItemModel* ibsModel;
    IBDescWgt* descWgt;

    void readIBs();
    void saveIBs();
    void loadIBs();
    void showMenu(const QPoint& pos);
    void fillDescWgt(const QModelIndex& midx);

public:
    explicit IBsTab(QWidget* parent = nullptr);
    ~IBsTab();
};

#endif // IBSTAB_H
