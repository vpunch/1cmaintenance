#include "taskstab.h"


TasksTab::TasksTab(QWidget* parent) : QWidget(parent)
{
    QStandardItemModel* model = new QStandardItemModel(0, 4);
    QStringList cols = {"", "Инф. базы", "Операции", "Время"};
    for (int i = 0; i < cols.size(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, cols[i], Qt::DisplayRole);
    }

    QTreeView* table = new QTreeView;
    table->setModel(model);

    QPushButton* saveBtn = new QPushButton;

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(table);
    lay->addWidget(saveBtn);
    this->setLayout(lay);

    QWizardPage* ibsPage = new QWizardPage;
    ibsPage->setTitle("Информационные базы");
    ibsPage->setSubTitle("Для каких ИБ создать задачу?");

    QWizardPage* opsPage = new QWizardPage;
    opsPage->setTitle("Операции");
    opsPage->setSubTitle("Какие операции выполнять?");

    QWizardPage* timePage = new QWizardPage;
    timePage->setTitle("Время");
    timePage->setSubTitle("В какое время выполнять?");

    QWizard* taskWiz = new QWizard;
    taskWiz->addPage(ibsPage);
    taskWiz->addPage(opsPage);
    taskWiz->addPage(timePage);
}
