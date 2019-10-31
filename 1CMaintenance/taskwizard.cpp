#include "taskwizard.h"

#include <QDebug>
#include <QTextCodec>
#include <QTimer>


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
    for (const QString& week : rot::weekOrder) {
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

#ifdef Q_OS_WIN
//get user name
    QStringList samUName;

    WCHAR bSamUName[256];
    DWORD nSamUName = sizeof(bSamUName);
    if (GetUserNameExW(NameSamCompatible, bSamUName, &nSamUName))
        samUName = QString::fromWCharArray(bSamUName).split("\\");

//get user password
    bool ok;
    QString passW = QInputDialog::getText(
            this, samUName.join("\\"), "Пароль:", QLineEdit::Password, "", &ok/*, Qt::MSWindowsFixedSizeDialogHint*/);

    if (!ok || passW.isEmpty())
        return;

//check user creds
    LPCWSTR bUName = samUName[1].toStdWString().c_str();
    LPCWSTR bDName = samUName[0].toStdWString().c_str();
    LPCWSTR bPassW = passW.toStdWString().c_str();
    HANDLE token;

    bool userExists = LogonUserW(
            bUName, bDName, bPassW,
            LOGON32_LOGON_NETWORK,
            LOGON32_PROVIDER_DEFAULT,
            &token);

    CloseHandle(token);
    if (!userExists)
        return;

//add task
    QString taskName = "1CM-" + batch.uuid;
    QString shell = "cmd.exe";
    QStringList cmd = {
        "/C",
        "schtasks" "/Query", "/TN", taskName, "||",
        "schtasks", "/Create",
            "/RU", samUName.join("\\"), "/RP", "",
            "/TN", taskName, "/SC", "WEEKLY",
            "/TR", qApp->applicationFilePath() + " -i " + batch.uuid
    };


    QProcess* newTaskProc = new QProcess();
    newTaskProc->start(shell, cmd);
    newTaskProc->waitForStarted();
    newTaskProc->write(passW.toUtf8() + "\r\n");
    //QTextCodec::codecForName("CP866")->toUnicode(newTaskProc->readAllStandardError());
#endif

    for (auto ibCB : ibCBs)
        if (ibCB->isChecked())
            batch.ibs << ibCB->text();


    for (auto opCB : opCBs)
        if (opCB->isChecked())
            batch.ops << opCB->text();


    QString time; //m h d m w;

    time += timeEd->sectionText(QDateTimeEdit::MinuteSection) + " ";
    time += timeEd->sectionText(QDateTimeEdit::HourSection) + " ";

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
