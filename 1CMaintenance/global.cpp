#include "global.h"


int rot::point2px(int count)
{
    QScreen* pscreen = QApplication::primaryScreen();
    qreal logDPI = pscreen->logicalDotsPerInch();
    int pixels = (count * logDPI) / 80;

    return pixels;
}

QHBoxLayout* rot::getField(const QString& name, QWidget* wgt)
{
    QLabel* lbl = new QLabel(name);

    QHBoxLayout* lay = new QHBoxLayout;
    lay->addWidget(lbl);
    lay->addWidget(wgt);

    return lay;
}
