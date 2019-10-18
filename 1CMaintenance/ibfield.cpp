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

        QToolButton* btn = new QToolButton();
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

void IBField::setValue(const QString& val, const QString& defval)
{
    if (type == Pass)
        le->setPlaceholderText(QString(L'●', defval.size()));
    else
        le->setPlaceholderText(defval);

    le->setText(val);
}

QString IBField::value()
{
    qDebug() << le->text().isNull();
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
