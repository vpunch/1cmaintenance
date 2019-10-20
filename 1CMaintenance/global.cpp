#include "global.h"

#include <QDebug>


int rot::point2px(int count)
{
    QScreen* pscreen = QApplication::primaryScreen();
    qreal logDPI = pscreen->logicalDotsPerInch();
    int pixels = (count * logDPI) / 80;

    return pixels;
}

QFormLayout* rot::formLay()
{
    auto lay = new QFormLayout;
    lay->setRowWrapPolicy(QFormLayout::DontWrapRows);
    lay->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    lay->setFormAlignment(Qt::AlignLeft | Qt::AlignTop);
    lay->setLabelAlignment(Qt::AlignLeft);

    return lay;
}

rot::IBasesT rot::ibases()
{
    IBasesT ibases;

#ifdef Q_OS_WIN
    const QString& roaming = qEnvironmentVariable("APPDATA");
    QString fname = roaming + "\\1C\\1CEStartt\\ibases.v8i";
#endif

    QFile file(fname);
    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream text(&file);
    text.setCodec("UTF-8");

    QString group;
    while (!text.atEnd()) {
        const QString& line = text.readLine().trimmed();

        if (line.startsWith('[')) {
            int len = line.indexOf(']') - 1;
            group = line.mid(1, len);

            ibases[group] = std::vector<std::pair<QString, QString>> {};

            continue;
        }

        QString key = line.section('=', 0, 0);
        QString value = line.section('=', 1);

        if (!key.isEmpty()) {
            ibases[group].emplace_back(key, value);
        }
    }

    return ibases;
}
