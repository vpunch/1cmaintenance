#ifndef IBFIELD_H
#define IBFIELD_H

#include <QLineEdit>
#include <QIntValidator>
#include <QToolButton>
#include <QAction>
#include <QDir>
#include <QFileDialog>

#include "global.h"


class IBField : public QWidget {
    Q_OBJECT

public:
    enum Type {Port, Pass, Path, Simple};

    IBField(Type type = Simple, QWidget* parent = nullptr);

    void setValue(const QString& val, const QString& defval = QString());
    QString value();

private:
    Type type;

    QLineEdit* le;

private slots:
    void getPath();
};

#endif // IBFIELD_H
