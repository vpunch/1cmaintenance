#include "taskstab.h"


TasksTab::TasksTab(QWidget* parent) : QWidget(parent)
{
    QTreeView* table = new QTreeView;
    //table->header()->setDefaultSectionSize();
    //table->header()->setDefaultAlignment(Qt::AlignCenter);
    //view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //view->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    //view->setAutoScroll(false);
    //view->setMinimumHeight(rot::logDpToPx(200));
    //view->setMinimumWidth(rot::logDpToPx(600));

    QStandardItemModel* model = new QStandardItemModel(0, 4);
    QStringList cols {"", "Инф. базы", "Операции", "Время"};
    for (int i = 0; i < cols.size(); ++i)
        model->setHeaderData(i, Qt::Horizontal, cols[i], Qt::DisplayRole);

    table->setModel(model);

    QVBoxLayout* lay = new QVBoxLayout;
    lay->addWidget(table);
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
    taskWiz->exec();
}
