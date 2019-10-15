#ifndef IBDESCWGT_H
#define IBDESCWGT_H

#include <QLabel>
#include <QStackedWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>

#include "global.h"
#include "storage.h"


// Info Base Description Widget
class IBDescWgt : public QWidget {
    Q_OBJECT

    Storage* stor;

    QLineEdit* nameEd;
    QLineEdit* userEd;
    QLineEdit* passEd;
    QComboBox* dbsCombo;

    void save();

public:
    explicit IBDescWgt(Storage* stor, QWidget* parent = nullptr);

    void fill(const QString& ibName, const IBDesc& data);

signals:
    void descChanged(const QString& ibName, const IBDesc& data);
};

#endif // IBDESCWGT_H
