#ifndef IBDESCWGT_H
#define IBDESCWGT_H

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QGroupBox>
#include <QSpinBox>
#include <QFormLayout>

#include "global.h"
#include "storage.h"


// Info Base Description Widget
class IBDescWgt : public QWidget {
    Q_OBJECT

    Storage* stor;

    QLineEdit* nameEd;
    QLineEdit* usrEd;
    QLineEdit* passEd;
    QComboBox* dbsCombo;

    QGroupBox* ocGroup;
    QLineEdit* pathEd;

    QGroupBox* extGroup;
    QLineEdit* hostEd;
    QLineEdit* portEd;
    QLineEdit* dbEd;
    QLineEdit* extusrEd;
    QLineEdit* extpassEd;

public:
    explicit IBDescWgt(Storage* stor, QWidget* parent = nullptr);

    void fill(const QString& ibName, const IBDesc& data);

signals:
    void descChanged(const QString& ibName, const IBDesc& data);

protected slots:
    void save();
    void activateGroup(int dbsIdx);
};

#endif // IBDESCWGT_H
