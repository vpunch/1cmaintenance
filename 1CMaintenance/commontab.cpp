#include "commontab.h"


CommonTab::CommonTab(QWidget* parent) : QWidget(parent)
{
    userEd = new QLineEdit;

    auto saveBtn = new QPushButton("Сохранить");
    connect(saveBtn, &QPushButton::clicked, this, &CommonTab::save);

    auto lay = new QVBoxLayout;
    lay->addLayout(rot::getField("Пользователь:", userEd));
    lay->addWidget(saveBtn);
    this->setLayout(lay);

    loadParam();
}

void CommonTab::save()
{
    comParam.user = userEd->text();
}

void CommonTab::saveParam()
{
    QSettings s;

    s.setValue("user", comParam.user);

    s.sync();
}

void CommonTab::loadParam()
{
    QSettings s;

    comParam.user = s.value("user").toString();
    userEd->setText(comParam.user);
}

CommonTab::~CommonTab()
{
    saveParam();
}
