#ifndef TASKWIZARD_H
#define TASKWIZARD_H

#include <QWizard>
#include <QCheckBox>
#include <QTimeEdit>
#include <QLabel>
#include <QComboBox>
#include <QStackedWidget>

#include <QGridLayout>

#include "storage.h"
#include "global.h"


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
