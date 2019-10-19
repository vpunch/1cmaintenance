#include "ibdescwgt.h"

#include <QDebug>


IBDescWgt::IBDescWgt(Storage* stor, QWidget* parent) : QWidget(parent)
{
    this->stor = stor;


    nameEd = new IBField;
    usrEd = new IBField;
    passEd = new IBField(IBField::Pass);

    dbsCombo = new QComboBox;
    dbsCombo->addItem("1С");
    dbsCombo->addItem("PostgreSQL");
    dbsCombo->setCurrentIndex(-1);
    connect(dbsCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &IBDescWgt::activateGroup);

    auto baseLay = rot::formLay(); //основная форма
    baseLay->addRow("Имя:", nameEd);
    baseLay->addRow("Пользователь:", usrEd);
    baseLay->addRow("Пароль:", passEd);
    baseLay->addRow("СУБД:", dbsCombo);


    pathEd = new IBField(IBField::Path);

    auto ocLay = rot::formLay(); //форма встроенной СУБД
    ocLay->addRow("Путь:", pathEd);

    ocGroup = new QGroupBox("1С");
    ocGroup->setLayout(ocLay);


    hostEd = new IBField;
    portEd = new IBField(IBField::Port);
    dbEd = new IBField;
    extusrEd = new IBField;
    extpassEd = new IBField(IBField::Pass);

    auto extLay = rot::formLay(); //форма внешней СУБД
    extLay->addRow("Хост:", hostEd);
    extLay->addRow("Порт:", portEd);
    extLay->addRow("БД:", dbEd);
    extLay->addRow("Пользователь:", extusrEd);
    extLay->addRow("Пароль:", extpassEd);

    extGroup = new QGroupBox("Внешняя");
    extGroup->setLayout(extLay);


    auto saveBtn = new QPushButton("Сохранить");
    connect(saveBtn, &QPushButton::clicked, this, &IBDescWgt::save);

    auto lay = new QVBoxLayout;
    lay->addLayout(baseLay);
    lay->addWidget(ocGroup);
    lay->addWidget(extGroup);
    lay->addStretch(1);
    lay->addWidget(saveBtn, 0, Qt::AlignLeft);
    this->setLayout(lay);


    loadCommon();
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
    IBDesc data = {
        .tmp = false,
        .usr = usrEd->value(),
        .pass = passEd->value(),
        .dbs = dbsCombo->currentText(),
        .path = pathEd->value(),
        .host = hostEd->value(),
        .port = portEd->value(),
        .db = dbEd->value(),
        .extusr = extusrEd->value(),
        .extpass = extpassEd->value()
    };

    emit descChanged(nameEd->value(), data);
}

QString IBDescWgt::currentDBS(bool external)
{
    if (dbsCombo->currentIndex() < 0)
        return dbsCombo->itemText(0);

    if (external && dbsCombo->currentIndex() == 0)
        return dbsCombo->itemText(1);

    return dbsCombo->currentText();
}

void IBDescWgt::fill(const QString& ibName, const IBDesc& data)
{
    nameEd->setValue(ibName);
    usrEd->setValue(data.usr);
    passEd->setValue(data.pass);

    int dbsIdx = dbsCombo->findText(data.dbs);
    if (dbsIdx < 0) {
        //exit
    }
    dbsCombo->setCurrentIndex(dbsIdx);

    pathEd->setValue(data.path);

    hostEd->setValue(data.host);
    portEd->setValue(data.port);
    dbEd->setValue(data.db);
    extusrEd->setValue(data.extusr);
    extpassEd->setValue(data.extpass);
}

void IBDescWgt::loadCommon()
{
    usrEd->setDefaultValue(stor->getParam("usr"));
    passEd->setDefaultValue(stor->getParam("pass"));

    hostEd->setDefaultValue(stor->getParam("host"));
    portEd->setDefaultValue(stor->getParam("port"));
    extusrEd->setDefaultValue(stor->getParam("extusr"));
    extpassEd->setDefaultValue(stor->getParam("extpass"));
}
