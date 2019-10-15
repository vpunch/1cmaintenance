#ifndef COMMONTAB_H
#define COMMONTAB_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include <QSettings>

#include "global.h"


struct CommonParam {
    QString user;
};

class CommonTab : public QWidget {
    Q_OBJECT

    CommonParam comParam;

    QLineEdit* userEd;

    void loadParam();
    void saveParam();

    void save();

public:
    explicit CommonTab(QWidget* parent = nullptr);
    ~CommonTab();

    const CommonParam* getComParam() const {return &comParam;}
};

#endif // COMMONTAB_H
