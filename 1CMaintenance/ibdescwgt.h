#ifndef IBDESCWGT_H
#define IBDESCWGT_H

#include <QLabel>
#include <QStackedWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>


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

    QLineEdit* nameEd;
    QLineEdit* userEd;
    QLineEdit* passEd;
    QComboBox* dbsCombo;

    QHBoxLayout* getField(const QString& name, QWidget* wgt);
    void save();

public:
    explicit IBDescWgt(QWidget* parent = nullptr);

    void fill(const QString& ibName, const IBDesc& data);

signals:
    void needSave(const IBDesc& data);
};

#endif // IBDESCWGT_H
