#ifndef LISTWGT_H
#define LISTWGT_H

#include <QAbstractItemView>
#include <QMenu>


class ListWgt : public QWidget {
    Q_OBJECT

private slots:
    void showMenu(const QPoint& pos);

protected:
    QAbstractItemView* listView;

    QMenu itemMenu, areaMenu;

    virtual void add() = 0;
    virtual void remove() = 0;

public:
    explicit ListWgt(QAbstractItemView* listView, QWidget* parent = nullptr);
};

#endif //LISTWGT_H
