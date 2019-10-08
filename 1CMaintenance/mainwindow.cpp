#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QListView* ibsView = new QListView;
    ibsView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ibsView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //---info base description wgt

    QWidget* ibDescWgt = new QWidget;

    QLabel* ibName = new QLabel;
    ibName->setText("СЕВУР БУХГАЛТЕРИЯ");

    QLabel* userLbl = new QLabel("Пользователь:");
    QLineEdit* userEd = new QLineEdit;
    QHBoxLayout* userLay = new QHBoxLayout;
    userLay->addWidget(userLbl);
    userLay->addWidget(userEd);

    QLabel* passLbl = new QLabel("Пароль:");
    QLineEdit* passEd = new QLineEdit;
    passEd->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    QHBoxLayout* passLay = new QHBoxLayout;
    userLay->addWidget(passLbl);
    userLay->addWidget(passEd);

    QLabel* dbsLbl = new QLabel("СУБД:"); //data base system label
    QComboBox* dbsCombo = new QComboBox;
    dbsCombo->addItem("1С");
    dbsCombo->addItem("PostgreSQL");
    QHBoxLayout* dbsLay = new QHBoxLayout;
    userLay->addWidget(dbsLbl);
    userLay->addWidget(dbsCombo);

    QWidget* ocWgt = new QWidget; //1(one)C widget

    QStackedWidget* dbsWgts = new QStackedWidget;
    dbsWgts->addWidget(ocWgt);

    QVBoxLayout* ibDescLay = new QVBoxLayout;
    ibDescLay->addWidget(ibName);
    ibDescLay->addLayout(userLay);
    ibDescLay->addLayout(passLay);
    ibDescLay->addLayout(dbsLay);
    ibDescLay->addWidget(dbsWgts);

    QSplitter* splt = new QSplitter;
    //splt->setOrientation(Qt::Vertical);
    splt->addWidget(ibsView);
    splt->addWidget(ibDescWgt);

    //---info bases wgt

    QWidget* ibsTab = new QWidget;
    QVBoxLayout* ibsLay = new QVBoxLayout;
    ibsLay->addWidget(splt);
    ibsTab->setLayout(ibsLay);

    QTabWidget* mainWgt = new QTabWidget;
    mainWgt->addTab(ibsTab, "Базы");


    this->setCentralWidget(mainWgt);

#ifdef Q_OS_WIN
    QSettings ibases("%APPDATA%/1C/1CEStart/ibases.v8i", QSettings::IniFormat);

    foreach (const QString &group, ibases.childGroups()) {
        ibases.beginGroup(group);

        if (ibases.contains("connection")) {
        }

        ibases.endGroup();
    }
#endif

    /*
    setPlaceholderText
    m_pwCallM = new QStandardItemModel(0,1);
    m_pwCallM->setHeaderData(0, Qt::Horizontal, "Call list", Qt::DisplayRole);
    m_pwCallV->setModel(m_pwCallM);
    */
}

MainWindow::~MainWindow()
{
}

