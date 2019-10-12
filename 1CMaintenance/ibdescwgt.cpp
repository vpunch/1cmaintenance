#include "ibdescwgt.h"

#include <QDebug>


IBDescWgt::IBDescWgt(QWidget* parent) : QWidget(parent)
{
    nameEd = new QLineEdit;

    userEd = new QLineEdit;

    passEd = new QLineEdit;
    passEd->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    dbsCombo = new QComboBox; //data base system
    dbsCombo->addItem("1C");
    dbsCombo->addItem("PostgreSQL");

    QWidget* ocWgt = new QWidget; //1(one)C widget

    QStackedWidget* dbsWgts = new QStackedWidget;
    dbsWgts->addWidget(ocWgt);

    QPushButton* saveBtn = new QPushButton("Сохранить");
    connect(saveBtn, &QPushButton::clicked, this, &IBDescWgt::save);

    // layout
    QVBoxLayout* ibDescLay = new QVBoxLayout;
    ibDescLay->addLayout(getField("Имя:", nameEd));
    ibDescLay->addLayout(getField("Пользователь:", userEd));
    ibDescLay->addLayout(getField("Пароль:", passEd));
    ibDescLay->addLayout(getField("СУБД:", dbsCombo));
    ibDescLay->addWidget(dbsWgts);
    ibDescLay->addWidget(saveBtn);

    this->setLayout(ibDescLay);
}

QHBoxLayout* IBDescWgt::getField(const QString& name, QWidget* wgt)
{
    QLabel* lbl = new QLabel(name);

    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(lbl);
    lay->addWidget(wgt);

    return lay;
}

void IBDescWgt::save()
{
    IBDesc data = {
        .isTmp = false,
        .user = userEd->text(),
        .pass = passEd->text(),
        .dbs = dbsCombo->currentText()
    };

    emit needSave(data);
}

void IBDescWgt::fill(const QString& ibName, const IBDesc& data)
{
    nameEd->setText(ibName);
    userEd->setText(data.user);
    passEd->setText(data.pass);
    dbsCombo->setCurrentText(data.dbs);
}
