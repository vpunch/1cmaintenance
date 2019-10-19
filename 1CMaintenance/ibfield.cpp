#include "ibfield.h"

#include <QDebug>


IBField::IBField(Type type, QWidget* parent) : QWidget(parent)
{
    this->type = type;

    setMaximumWidth(rot::point2px(200));

    le = new QLineEdit;

    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(le, 1);

    switch (type) {
    case Port:
        le->setValidator(new QIntValidator(1, 49151));
        break;

    case Pass:
        le->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        break;

    case Path: {
        auto act = new QAction();
        act->setIconText("...");
        connect(act, &QAction::triggered, this, &IBField::getPath);

        auto btn = new QToolButton();
        btn->setDefaultAction(act);
        lay->addWidget(btn);
        break;
    }
    case Simple:
        break;
    }

    lay->setMargin(0);
    setLayout(lay);
}

void IBField::setValue(const QString& val)
{
    le->setText(val);
}

void IBField::setDefaultValue(const QString& val)
{
    if (type == Pass)
        le->setPlaceholderText(QString(val.size(), L'●'));
    else
        le->setPlaceholderText(val);
}

QString IBField::value()
{
    return le->text();
}

void IBField::getPath()
{
    const QString& path = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(
            this, "", QDir::currentPath()));

    if (!path.isEmpty()) {
        le->setText(path);
    }
}
