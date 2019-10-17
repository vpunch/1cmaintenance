#include "global.h"


int rot::point2px(int count)
{
    QScreen* pscreen = QApplication::primaryScreen();
    qreal logDPI = pscreen->logicalDotsPerInch();
    int pixels = (count * logDPI) / 80;

    return pixels;
}

QFormLayout* rot::getFormLay()
{
    auto lay = new QFormLayout;
    lay->setRowWrapPolicy(QFormLayout::DontWrapRows);
    lay->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    lay->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    lay->setLabelAlignment(Qt::AlignLeft);

    return lay;
}
