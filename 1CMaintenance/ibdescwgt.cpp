#include "ibdescwgt.h"

#include <QDebug>


IBDescWgt::IBDescWgt(Storage* stor, QWidget* parent) : QWidget(parent)
{
    this->stor = stor;

    nameEd = new QLineEdit;

    userEd = new QLineEdit;

    passEd = new QLineEdit;
    passEd->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    dbsCombo = new QComboBox; //data base system
    dbsCombo->addItem("1C");
    dbsCombo->addItem("PostgreSQL");

    auto ocWgt = new QWidget; //1(one)C widget

    auto dbsWgts = new QStackedWidget;
    dbsWgts->addWidget(ocWgt);

    auto saveBtn = new QPushButton("Сохранить");
    connect(saveBtn, &QPushButton::clicked, this, &IBDescWgt::save);

    // layout
    auto lay = new QVBoxLayout;
    lay->addLayout(rot::getField("Имя:", nameEd));
    lay->addLayout(rot::getField("Пользователь:", userEd));
    lay->addLayout(rot::getField("Пароль:", passEd));
    lay->addLayout(rot::getField("СУБД:", dbsCombo));
    lay->addWidget(dbsWgts);
    lay->addWidget(saveBtn);
    this->setLayout(lay);
}

void IBDescWgt::save()
{
    IBDesc data {
        .tmp = false,
        .usr = userEd->text(),
        .passwd = passEd->text(),
        .dbs = dbsCombo->currentText()
    };

    emit descChanged(nameEd->text(), data);
}

void IBDescWgt::fill(const QString& ibName, const IBDesc& data)
{
    nameEd->setText(ibName);

    if (data.usr.isEmpty()) {
        userEd->setPlaceholderText(stor->getParam("user"));
    }
    else {
        userEd->setText(data.usr);
    }

    passEd->setText(data.passwd);
    dbsCombo->setCurrentText(data.dbs);
}
