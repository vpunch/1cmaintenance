#include "ibdescwgt.h"

#include <QDebug>


IBDescWgt::IBDescWgt(const CommonParam* comParam, QWidget* parent) : QWidget(parent)
{
    this->comParam = comParam;

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
    IBDesc data = {
        .isTmp = false,
        .user = userEd->text(),
        .pass = passEd->text(),
        .dbs = dbsCombo->currentText()
    };

    emit descChanged(nameEd->text(), data);
}

void IBDescWgt::fill(const QString& ibName, const IBDesc& data)
{
    nameEd->setText(ibName);
    userEd->setText(data.user);
    passEd->setText(data.pass);
    dbsCombo->setCurrentText(data.dbs);

    if (userEd->text().isEmpty()) {
        userEd->setPlaceholderText(comParam->user);
    }
}
