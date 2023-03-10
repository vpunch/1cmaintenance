#ifndef IBDESCWGT_H
#define IBDESCWGT_H

#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>

#include "global.h"
#include "ibfield.h"
#include "storage.h"


//Info Base Description Widget
class IBDescWgt : public QWidget {
    Q_OBJECT

    Storage* stor;

    IBField* nameEd;
    IBField* usrEd;
    IBField* passEd;
    QComboBox* dbsCombo; //database system

    QGroupBox* ocGroup; //1(one)c Group
    IBField* pathEd;

    QGroupBox* extGroup; //external Group
    IBField* hostEd;
    IBField* portEd;
    IBField* dbEd;
    IBField* extusrEd;
    IBField* extpassEd;

private slots:
    void save();
    void activateGroup(int dbsIdx);

public:
    explicit IBDescWgt(Storage* stor, QWidget* parent = nullptr);

    void fill(const QString& ibName, const IBDesc& data);
    QString currentDBS(bool external = false);

public slots:
    void loadCommon();

signals:
    void descChanged(const QString& ibName, const IBDesc& data);
};

#endif //IBDESCWGT_H
