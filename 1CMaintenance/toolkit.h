#ifndef TOOLKIT_H
#define TOOLKIT_H

#include <QScreen>
#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>


namespace rot {
    int point2px(int count);
    QHBoxLayout* getField(const QString& name, QWidget* wgt);
}

#endif // TOOLKIT_H
