#ifndef COMMONTAB_H
#define COMMONTAB_H

#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>

#include "global.h"
#include "ibfield.h"


class CommonTab : public QWidget {
    Q_OBJECT

    IBField* usrEd;
    IBField* passEd;

    IBField* hostEd;
    IBField* portEd;
    IBField* dbEd;
    IBField* extusrEd;
    IBField* extpassEd;

    IBField* storageEd;

    void loadParam();
    void saveParam();

    void save();

public:
    explicit CommonTab(QWidget* parent = nullptr);

signals:
    void defaultChanged();
};

#endif // COMMONTAB_H
