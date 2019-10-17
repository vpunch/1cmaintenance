#include "commontab.h"


CommonTab::CommonTab(QWidget* parent) : QWidget(parent)
{
    usrEd = new IBField;
    passEd = new IBField(IBField::Pass);

    auto baseLay = rot::getFormLay();
    baseLay->addRow("Пользователь:", usrEd);
    baseLay->addRow("Пароль:", passEd);

    auto baseGroup = new QGroupBox("Информационная база");
    baseGroup->setLayout(baseLay);


    hostEd = new IBField;
    portEd = new IBField(IBField::Port);
    dbEd = new IBField;
    extusrEd = new IBField;
    extpassEd = new IBField(IBField::Pass);

    auto extLay = rot::getFormLay();
    extLay->addRow("Хост:", hostEd);
    extLay->addRow("Порт:", portEd);
    extLay->addRow("БД:", dbEd);
    extLay->addRow("Пользователь:", extusrEd);
    extLay->addRow("Пароль:", extpassEd);

    auto extGroup = new QGroupBox("Внешняя СУБД");
    extGroup->setLayout(extLay);


    auto otherLay = rot::getFormLay();

    storageEd = new IBField(IBField::Path);

    otherLay->addRow("Хранилище:", storageEd);


    auto saveBtn = new QPushButton("Сохранить");
    connect(saveBtn, &QPushButton::clicked, this, &CommonTab::save);

    // layout
    auto lay = new QVBoxLayout;
    lay->addWidget(baseGroup);
    lay->addWidget(extGroup);
    lay->addLayout(otherLay);
    lay->addStretch(1);
    lay->addWidget(saveBtn, 0, Qt::AlignLeft);
    this->setLayout(lay);
}

void CommonTab::save()
{
}

void CommonTab::saveParam()
{


}

void CommonTab::loadParam()
{

}

/*
void Window::browse()


*/
