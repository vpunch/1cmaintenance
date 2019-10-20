#include "taskstab.h"


TasksTab::TasksTab(Storage* stor, QWidget* parent)
    : ListWgt(new QTreeView, parent)
{
    this->stor = stor;

    QStandardItemModel* model = new QStandardItemModel(0, 4);
    QStringList cols = {"", "Инф. базы", "Операции", "Время"};
    for (int i = 0; i < cols.size(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, cols[i], Qt::DisplayRole);
    }

    table = (QTreeView*)listView;
    table->setModel(model);

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(table);
    this->setLayout(lay);
}

void TasksTab::add()
{
    QWizardPage* ibsPage = new QWizardPage;
    ibsPage->setTitle("Информационные базы");
    ibsPage->setSubTitle("Для каких ИБ создать задачу?");

    auto ibsLay = new QVBoxLayout;

    for (auto ib : stor->getIBs())
        ibsLay->addWidget(new QCheckBox(ib.first));

    ibsPage->setLayout(ibsLay);


    QWizardPage* opsPage = new QWizardPage;
    opsPage->setTitle("Операции");
    opsPage->setSubTitle("Какие операции выполнять?");

    auto opsLay = new QVBoxLayout;

    for (auto op : stor->getOps())
        opsLay->addWidget(new QCheckBox(op));

    opsPage->setLayout(opsLay);


    QWizardPage* timePage = new QWizardPage;
    timePage->setTitle("Время");
    timePage->setSubTitle("В какое время выполнять?");

    auto typeCombo = new QComboBox;
    typeCombo->addItem("ежедневно");
    typeCombo->addItem("еженедельно");
    typeCombo->addItem("ежемесячно");

    auto typeWgts = new QStackedWidget;

    auto monthlyLay = new QGridLayout;

    int rowlen = 10;
    int row = 0, col = 0;
    for (int i = 0; i < 28; ++i) {
        monthlyLay->addWidget(new QCheckBox(QString::number(i + 1)), row, col);

        row = i / rowlen;
        col = i % rowlen;
    }
    monthlyLay->addWidget(new QLabel("числа"), row, col, 1, i - (i % row));

    auto timeEd = new QTimeEdit;
    timeEd->setDisplayFormat("hh:mm");
    timeEd->setMaximumWidth(rot::point2px(80));


    auto timeTypeLay = new QHBoxLayout;
    timeTypeLay->addWidget(new QLabel("В"));
    timeTypeLay->addWidget(timeEd);
    timeTypeLay->addWidget(new QLabel(", "));
    timeTypeLay->addWidget(typeCombo);
    timeTypeLay->addWidget(new QLabel(", "));
    timeTypeLay->addStretch(1);

    auto timeLay = new QVBoxLayout;
    timeLay->addLayout(timeTypeLay);
    timeLay->addLayout(monthlyLay);

    timePage->setLayout(timeLay);


    QWizard* taskWiz = new QWizard;
    taskWiz->addPage(ibsPage);
    taskWiz->addPage(opsPage);
    taskWiz->addPage(timePage);
    taskWiz->exec();
}

void TasksTab::remove()
{

}
