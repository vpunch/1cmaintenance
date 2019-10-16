#include "ibdescwgt.h"

#include <QDebug>


IBDescWgt::IBDescWgt(Storage* stor, QWidget* parent) : QWidget(parent)
{
    this->stor = stor;

//основная форма
    nameEd = new QLineEdit;
    usrEd = new QLineEdit;

#define PASSED(name) \
    name = new QLineEdit; \
    name->setEchoMode(QLineEdit::PasswordEchoOnEdit);

    PASSED(passEd)

    dbsCombo = new QComboBox; //data base system
    dbsCombo->addItem("1С");
    dbsCombo->addItem("PostgreSQL");
    dbsCombo->setCurrentIndex(-1);
    connect(dbsCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &IBDescWgt::activateGroup);

    auto baseLay = new QFormLayout;
    baseLay->setRowWrapPolicy(QFormLayout::DontWrapRows);
    baseLay->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    baseLay->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    baseLay->setLabelAlignment(Qt::AlignLeft);

    baseLay->addRow("Имя:", nameEd);
    baseLay->addRow("Пользователь:", usrEd);
    baseLay->addRow("Пароль:", passEd);
    baseLay->addRow("СУБД:", dbsCombo);

//форма встроенной СУБД
    pathEd = new QLineEdit;

    auto ocLay = new QFormLayout;
    ocLay->addRow("Путь:", pathEd);

    ocGroup = new QGroupBox; //1(one)c Group
    ocGroup->setTitle("1С");
    ocGroup->setLayout(ocLay);

//форма внешней СУБД
    hostEd = new QLineEdit;

    portEd = new QLineEdit;
    portEd->setValidator(new QIntValidator(1, 49151));

    dbEd = new QLineEdit;
    extusrEd = new QLineEdit;

    PASSED(extpassEd)

    auto extLay = new QFormLayout;
    extLay->addRow("Хост:", hostEd);
    extLay->addRow("Порт:", portEd);
    extLay->addRow("БД:", dbEd);
    extLay->addRow("Пользователь:", extusrEd);
    extLay->addRow("Пароль:", extpassEd);

    extGroup = new QGroupBox; //external Group
    extGroup->setTitle("Внешняя");
    extGroup->setLayout(extLay);

//
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
    nameEd->setText(ibName);

    if (data.usr.isEmpty()) {
        usrEd->setPlaceholderText(stor->getParam("usr"));
    }
    else {
        usrEd->setText(data.usr);
    }

    if (data.pass.isEmpty()) {
    }
    else {
        passEd->setText(data.pass);
    }

    int dbsIdx = dbsCombo->findText(data.dbs);
    if (dbsIdx < 0) {
        //exit
    }
    dbsCombo->setCurrentIndex(dbsIdx);

    pathEd->setText(data.path);

    if (data.host.isEmpty())
        hostEd->setPlaceholderText(stor->getParam("host"));
    else
        hostEd->setText(data.host);

    if (data.port == 0)
        portEd->setPlaceholderText(stor->getParam("port"));
    else
        portEd->setText(QString::number(data.port));

    if (data.db.isEmpty())
        dbEd->setPlaceholderText(stor->getParam("db"));
    else
        dbEd->setText(data.db);

    if (data.extusr.isEmpty())
        extusrEd->setPlaceholderText(stor->getParam("extusr"));
    else
        extusrEd->setText(data.extusr);

    if (data.extpass.isEmpty()) {
    }
    else
        extpassEd->setText(data.extpass);
}
