#include "ibfield.h"

#include <QDebug>


IBField::IBField(Type type, QWidget* parent) : QWidget(parent)
{
    QHBoxLayout* lay = new QHBoxLayout;

    le = new QLineEdit;

    lay->addWidget(le, 1);
    this->type = type;

    setMaximumWidth(rot::point2px(200));

    switch (type) {
    case Port:
        le->setValidator(new QIntValidator(1, 49151));
        break;

    case Pass:
        le->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        break;

    case Path: {
        QToolButton* btn = new QToolButton();
        auto act = new QAction();
       //act->setText("....");
       act->setIconText("...");
       btn->setDefaultAction(act);
       connect(act, &QAction::triggered, this, &IBField::browse);
        lay->addWidget(btn);
        break;
    }

    case Simple:
        break;
    }

    lay->setMargin(0);
    setLayout(lay);
}

void IBField::setValue(const QString& val, const QString& defval)
{
    if (type == Pass) {
        le->setPlaceholderText(QString(L'●', defval.size()));
    }
    else
        le->setPlaceholderText(defval);

    le->setText(val);
}

QString IBField::text()
{
    return le->text();
}

void IBField::browse()
{
    QString directory =
        QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this, tr("Find Files"), QDir::currentPath()));

    if (!directory.isEmpty()) {
        qDebug() << directory;
        /*
        if (directoryComboBox->findText(directory) == -1)
            directoryComboBox->addItem(directory);
        directoryComboBox->setCurrentIndex(directoryComboBox->findText(directory));
        */
    }
}
