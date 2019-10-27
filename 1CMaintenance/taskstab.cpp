#include "taskstab.h"

#include <QDebug>


TasksTab::TasksTab(Storage* stor, QWidget* parent)
    : ListWgt(new QTreeView, parent)
{
    this->stor = stor;

    QStringList cols = {"Инф. базы", "Операции", "Время"};
    model = new QStandardItemModel(0, cols.size());
    for (int i = 0; i < cols.size(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, cols[i], Qt::DisplayRole);
    }

    table = (QTreeView*)listView;
    table->setModel(model);

    auto lay = new QVBoxLayout;
    lay->addWidget(table);
    this->setLayout(lay);

    updateList();
}

void TasksTab::add()
{
    TaskWizard wiz(stor, this);

    connect(&wiz, &QDialog::accepted, this, [this] {
        updateList();
    });

    wiz.exec();
}

void TasksTab::remove()
{
    QModelIndex headIdx = model->index(table->currentIndex().row(), 0);
    const QString uuid = model->data(headIdx, Qt::UserRole + 1).toString();
    stor->removeTask(uuid);
    updateList();
}

void TasksTab::loadList()
{
    for (auto batch : stor->getTasks()) {
        QList<QStandardItem*> items;

        auto headItem = new QStandardItem(batch.ibs.join(", "));
        headItem->setData(batch.uuid);
        items.append(headItem);

        items.append(new QStandardItem(batch.ops.join(", ")));


        QStringList timeSects = batch.time.split(' ');

        QString time = timeSects[1] + ":" + timeSects[0];

        if (timeSects[2] != "*") {
            time += " " + timeSects[2];
        }
        else {
            QStringList weeks;
            for (const QString& weekN : timeSects[4].split(','))
                weeks << rot::weekOrder[weekN.toInt()];
            time += " " + weeks.join(',');
        }

        items.append(new QStandardItem(time));


        model->appendRow(items);

        QString name;
#ifdef Q_OS_WIN
    WCHAR acUserName[256];
    DWORD nUserName = sizeof(acUserName);
    if (GetUserNameExW(NameSamCompatible, acUserName, &nUserName))
         name = QString::fromWCharArray(acUserName);
#endif

    bool ok;
       QString text = QInputDialog::getText(this, name,
                                            tr("Пароль:"), QLineEdit::Password,
                                            "HERE", &ok);
       if (ok && !text.isEmpty())
           qDebug() << text;

        /*
        QString prog = "cmd.exe";
        QStringList args = {"/C", "schtasks", "/Create", "/RU", ""};

        arguments << "/Create"
                << "/RU" << "Ivan"
                << "/RP" << "bbwovwV"
                << "/SC" << "WEEKLY"
                << "/TN" << "1CM" + batch.uuid
                << "/TR" << qApp->applicationFilePath() + "-i " + batch.uuid;

        QProcess *myProcess = new QProcess(this);
        myProcess->start("cmd.exe", {

                         });
        myProcess->waitForStarted();
        myProcess->waitForFinished();
        qDebug() << myProcess->readAll();
        */

    }
}
