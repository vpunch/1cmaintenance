#ifndef GLOBAL_H
#define GLOBAL_H

#include <QLabel>
#include <QHBoxLayout>

#include <QScreen>
#include <QApplication>


namespace rot {
    int point2px(int count);
    QHBoxLayout* getField(const QString& name, QWidget* wgt);
}

#endif // GLOBAL_H
