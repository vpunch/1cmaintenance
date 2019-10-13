#ifndef IBDESCWGT_H
#define IBDESCWGT_H

#include <QLabel>
#include <QStackedWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>

#include "toolkit.h"
#include "commontab.h"


struct IBDesc {
    bool isTmp;
    QString user;
    QString pass;
    QString dbs;
};

Q_DECLARE_METATYPE(IBDesc)

// Info Base Description Widget
class IBDescWgt : public QWidget {
    Q_OBJECT

    const CommonParam* comParam;

    QLineEdit* nameEd;
    QLineEdit* userEd;
    QLineEdit* passEd;
    QComboBox* dbsCombo;

    void save();

public:
    explicit IBDescWgt(const CommonParam* comParam, QWidget* parent = nullptr);

    void fill(const QString& ibName, const IBDesc& data);

signals:
    void descChanged(const QString& ibName, const IBDesc& data);
};

#endif // IBDESCWGT_H
