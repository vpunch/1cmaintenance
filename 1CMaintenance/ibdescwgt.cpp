#include "ibdescwgt.h"

#include <QDebug>


IBDescWgt::IBDescWgt(Storage* stor, QWidget* parent) : QWidget(parent)
{
    this->stor = stor;

//основная форма
    nameEd = new IBField;
    usrEd = new IBField;
    passEd = new IBField(IBField::Path);

    dbsCombo = new QComboBox; //data base system
    dbsCombo->addItem("1С");
    dbsCombo->addItem("PostgreSQL");
    dbsCombo->setCurrentIndex(-1);
    connect(dbsCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &IBDescWgt::activateGroup);

    auto baseLay = rot::getFormLay();
    baseLay->addRow("Имя:", nameEd);
    baseLay->addRow("Пользователь:", usrEd);
    baseLay->addRow("Пароль:", passEd);
    baseLay->addRow("СУБД:", dbsCombo);

//форма встроенной СУБД
    pathEd = new IBField(IBField::Path);

    auto ocLay = rot::getFormLay();
    ocLay->addRow("Путь:", pathEd);

    ocGroup = new QGroupBox("1С"); //1(one)c Group
    ocGroup->setLayout(ocLay);

//форма внешней СУБД
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

    extGroup = new QGroupBox("Внешняя СУБД"); //external Group
    extGroup->setLayout(extLay);


    auto saveBtn = new QPushButton("Сохранить");
    connect(saveBtn, &QPushButton::clicked, this, &IBDescWgt::save);

    // layout
    auto lay = new QVBoxLayout;
    lay->addLayout(baseLay);
    lay->addWidget(ocGroup);
    lay->addWidget(extGroup);
    lay->addStretch(1);
    lay->addWidget(saveBtn, 0, Qt::AlignLeft);
    this->setLayout(lay);
}

void IBDescWgt::activateGroup(int dbsIdx)
{
    ocGroup->setEnabled(false);
    extGroup->setEnabled(false);

    if (dbsIdx == 0)
        ocGroup->setEnabled(true);
    else
        extGroup->setEnabled(true);
}

void IBDescWgt::save()
{
    IBDesc data {
        .tmp = false,
        .port = portEd->text().toUInt(),
        .usr = usrEd->text(),
        .pass = passEd->text(),
        .dbs = dbsCombo->currentText(),
        .path = pathEd->text(),
        .host = hostEd->text(),
        .db = dbEd->text(),
        .extusr = extusrEd->text(),
        .extpass = extpassEd->text()
    };

    emit descChanged(nameEd->text(), data);
}

void IBDescWgt::fill(const QString& ibName, const IBDesc& data)
{
    nameEd->setValue(ibName);
    usrEd->setValue(data.usr, stor->getParam("usr"));
    passEd->setValue(data.pass); //не отображается, но учитывается

    int dbsIdx = dbsCombo->findText(data.dbs);
    if (dbsIdx < 0) {
        //exit
    }
    dbsCombo->setCurrentIndex(dbsIdx);

    pathEd->setValue(data.path);

    hostEd->setValue(data.host, stor->getParam("host"));
    portEd->setValue(QString::number(data.port), stor->getParam("port"));
    dbEd->setValue(data.db, stor->getParam("db"));
    extusrEd->setValue(data.extusr, stor->getParam("extusr"));
    extpassEd->setValue(data.extpass);
}
