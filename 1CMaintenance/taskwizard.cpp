#include "taskwizard.h"

#include <QDebug>


TaskWizard::TaskWizard(Storage* stor, QWidget* parent) : QWizard(parent)
{
    this->stor = stor;

//Info Bases Page
    auto ibsPage = new QWizardPage;
    ibsPage->setTitle("Информационные базы");
    ibsPage->setSubTitle("Для каких ИБ создать задачу?");

    auto ibsPageLay = new QVBoxLayout;

    for (const auto& ib : stor->getIBs()) {
        auto ibCB = new QCheckBox(ib.first);
        ibCBs << ibCB;
        ibsPageLay->addWidget(ibCB);
    }

    ibsPage->setLayout(ibsPageLay);

//Operations Page
    QWizardPage* opsPage = new QWizardPage;
    opsPage->setTitle("Операции");
    opsPage->setSubTitle("Какие операции выполнять?");

    auto opsPageLay = new QVBoxLayout;

    for (const QString& op : stor->getOps()) {
        auto opCB = new QCheckBox(op);
        opCBs << opCB;
        opsPageLay->addWidget(opCB);
    }

    opsPage->setLayout(opsPageLay);

//Time Page
    QWizardPage* timePage = new QWizardPage;
    //timePage->setStyleSheet("border: 1px solid black;");
    timePage->setTitle("Время");
    timePage->setSubTitle("В какое время выполнять?");

    timeEd = new QTimeEdit;
    timeEd->setDisplayFormat("hh:mm");
    timeEd->setMaximumWidth(rot::point2px(90));

    typeCombo = new QComboBox;
    typeCombo->addItem("ежедневно");
    typeCombo->addItem("еженедельно,");
    typeCombo->addItem("ежемесячно,");

    auto timeTypeLay = new QHBoxLayout;
    timeTypeLay->addWidget(new QLabel("В"));
    timeTypeLay->addWidget(timeEd);
    timeTypeLay->addWidget(new QLabel(","));
    timeTypeLay->addWidget(typeCombo);
    timeTypeLay->addStretch(1);


    auto monthlyLay = new QGridLayout;

    int rowlen = 10;
    int row, col;
    for (int i = 0; i < 31; ++i) {
        row = i / rowlen;
        col = i % rowlen;

        auto monthDayCB = new QCheckBox(QString::number(i + 1));
        monthDayCBs << monthDayCB;
        monthlyLay->addWidget(monthDayCB, row, col);
    }
    ++col;
    monthlyLay->addWidget(new QLabel("числа."), row, col, 1, rowlen - col);
    monthlyLay->setColumnStretch(rowlen - 1, 1);
    monthlyLay->setMargin(0);

    auto monthlyWgt = new QWidget;
    monthlyWgt->setLayout(monthlyLay);


    auto weeklyLay = new QHBoxLayout;

    weeklyLay->addWidget(new QLabel("по"));
    QStringList weeks = {"вс.", "пн.", "вт.", "ср.", "чт.", "пт.", "сб."};
    for (const QString& week : weeks) {
        auto weekDayCB = new QCheckBox(week);
        weekDayCBs << weekDayCB;
        weeklyLay->addWidget(weekDayCB);
    }
    weeklyLay->addStretch(1);
    weeklyLay->setMargin(0);

    auto weeklyWgt = new QWidget;
    weeklyWgt->setLayout(weeklyLay);


    auto typeWgts = new QStackedWidget;
    typeWgts->addWidget(new QWidget);
    typeWgts->addWidget(weeklyWgt);
    typeWgts->addWidget(monthlyWgt);

    connect(typeCombo, QOverload<int>::of(QComboBox::currentIndexChanged),
            [typeWgts] (int idx) {
        typeWgts->setCurrentIndex(idx);
    });

    auto timePageLay = new QVBoxLayout;
    timePageLay->addLayout(timeTypeLay);
    timePageLay->addWidget(typeWgts);
    timePageLay->addStretch(1);

    timePage->setLayout(timePageLay);


    addPage(ibsPage);
    addPage(opsPage);
    addPage(timePage);
    setWindowTitle("Мастер создания задач");
}

void TaskWizard::accept()
{
    TaskBatch batch;

    batch.uuid = QUuid::createUuid().toString();


    for (auto ibCB : ibCBs)
        if (ibCB->isChecked())
            batch.ibs << ibCB->text();


    for (auto opCB : opCBs)
        if (opCB->isChecked())
            batch.ops << opCB->text();


    QString time; //m h d m w;

    time += QString::number(timeEd->time().minute()) + " ";
    time += QString::number(timeEd->time().hour()) + " ";

    switch (typeCombo->currentIndex()) {
    case 0:
        time += "* * *";

        break;
    case 1: {
        QStringList weekDays;

        for (int i = 0; i < weekDayCBs.size(); ++i)
            if (weekDayCBs[i]->isChecked())
                weekDays << QString::number(i);

        QString weekDaysStr = weekDays.join(',');

        if (weekDaysStr.isEmpty()) {
        }

        time += "* * " + weekDaysStr;

        break;
    }
    case 2: {
        QStringList monthDays;

        for (auto monthCB : monthDayCBs)
            if (monthCB->isChecked())
                monthDays << monthCB->text();

        QString monthDaysStr = monthDays.join(',');

        time += monthDaysStr + " * *";

        break;
    }
    }

    batch.time = time;


    stor->saveTasks(batch);

    QDialog::accept();
}
