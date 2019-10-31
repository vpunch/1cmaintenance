#ifndef TASKWIZARD_H
#define TASKWIZARD_H

#include <QWizard>
#include <QCheckBox>
#include <QTimeEdit>
#include <QLabel>
#include <QComboBox>
#include <QStackedWidget>
#include <QInputDialog>

#include <QGridLayout>
#include <QProcess>

#include "storage.h"
#include "global.h"

#ifdef Q_OS_WIN
#include <Windows.h>
#define SECURITY_WIN32
#include <Security.h>
#include <Lmcons.h>
#endif


class TaskWizard : public QWizard {
    Storage* stor;

    QList<QCheckBox*> ibCBs;

    QList<QCheckBox*> opCBs;

    QTimeEdit* timeEd;
    QComboBox* typeCombo;
    QList<QCheckBox*> monthDayCBs;
    QList<QCheckBox*> weekDayCBs;

public:
    TaskWizard(Storage* stor, QWidget* parent = nullptr);

    void accept() override;
};

#endif //TASKWIZARD_H
