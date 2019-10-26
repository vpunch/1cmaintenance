#ifndef GLOBAL_H
#define GLOBAL_H

#include <map>

#include <QFormlayout>
#include <QScreen>
#include <QApplication>
#include <QFile>
#include <QTextStream>


namespace rot {
    int point2px(int count);

    QFormLayout* formLay();

    using IBasesT = std::map<QString, std::vector<std::pair<QString, QString>>>;
    IBasesT ibases();

    //parseDB();
}

#endif //GLOBAL_H
