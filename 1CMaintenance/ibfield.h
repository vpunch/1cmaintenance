#ifndef IBFIELD_H
#define IBFIELD_H

#include <QLineEdit>
#include <QToolButton>
#include <QFileDialog>

#include <QIntValidator>
#include <QAction>
#include <QDir>

#include "global.h"


class IBField : public QWidget {
    Q_OBJECT

public:
    enum Type {Port, Pass, Path, Simple};

    IBField(Type type = Simple, QWidget* parent = nullptr);

    void setValue(const QString& val);
    void setDefaultValue(const QString& val);
    QString value();

private:
    Type type;

    QLineEdit* le;

private slots:
    void getPath();
};

#endif //IBFIELD_H
