#include "storage.h"

//#include <QDebug>


Storage::Storage()
{
    //если будет создано несколько экземпляров, новое соединение заменит старое,
    //инициализируются они одиноково
    QSqlDatabase conn = QSqlDatabase::addDatabase("QSQLITE");
    conn.setDatabaseName(
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/db");

    if (!conn.open()) {
        throw StorageError("Can't open database");
    }

    QFile f(":/initdb.sql");
    f.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream s(&f);
    s.setCodec("UTF-8");

    for (const QString& stat : s.readAll().split(';', QString::SkipEmptyParts)) {
        QSqlQuery q(stat);
    }
}

IBs Storage::getIBs() {
    IBs ibs;

    QSqlQuery q(R"(
            SELECT name, usr, passwd, dbs, path, host, port, db, dbusr FROM InfoBase;
    )");

    if (!q.isActive()) {
        //журнал

        return ibs;
    }

    while (q.next()) {
        IBDesc desc {
            .tmp = false,
            .usr = q.value(1).toString(),
            .passwd = q.value(2).toString(),
            .dbs = q.value(3).toString(),
            .path = q.value(4).toString(),
            .host = q.value(5).toString(),
            .port = q.value(6).toString(),
            .db = q.value(7).toString(),
            .dbusr = q.value(8).toString()
        };

        ibs[q.value(0).toString()] = desc;
    }

    return ibs;
}

QString Storage::fillQuStr(const QString &str, const IBDesc &desc)
{
    return str.arg(desc.usr)
            .arg(desc.passwd)
            .arg(desc.dbs)
            .arg(desc.path)
            .arg(desc.host)
            .arg(desc.port)
            .arg(desc.db)
            .arg(desc.dbusr);
}

bool Storage::saveIB(const QString& name, const IBDesc& desc, const QString& oldName)
{
    QString quStr = R"(
            UPDATE InfoBase
            SET name=:name, usr='%1', passwd='%2', dbs='%3', path='%4', host='%5', port='%6', db='%7', dbusr='%8'
            WHERE name=:oldName
    )";
    quStr = fillQuStr(quStr, desc);

    QSqlQuery q;
    q.prepare(quStr);
    q.bindValue(":name", name);
    q.bindValue(":oldName", oldName); //пустая строка не вызывает ошибку

    if (q.exec() && q.numRowsAffected() == 0) {
        q.clear();

        QString quStr = R"(
                INSERT INTO InfoBase
                VALUES (?, '%1', '%2', '%3', '%4', '%5', '%6', '%7', '%8')
        )";
        quStr = fillQuStr(quStr, desc);

        q.prepare(quStr);
        q.addBindValue(name);
        q.exec();
    }

    if (!q.isActive()) {
        //журнал
    }

    return q.isActive();
}

bool Storage::setParam(const QString name, const QString& value)
{
    QString quStr = QString("UPDATE Param SET value='%1' WHERE name='%2'")
            .arg(value).arg(name);
    QSqlQuery q(quStr);

    if (q.isActive() && q.numRowsAffected() == 0) {
        q.clear();

        QString quStr = QString("INSERT INTO Param VALUES ('%1', '%2')")
                .arg(name).arg(value);
        q.exec(quStr);
    }

    if (!q.isActive()) {
        //журнал
    }

    return q.isActive();
}

QString Storage::getParam(const QString name)
{
    QString quStr = QString("SELECT value FROM Param WHERE name='%1'").arg(name);
    QSqlQuery q(quStr);

    if (!q.isActive()) {
        //журнал
    }

    //вернет пустую строку, даже если вариант невалидный
    q.next();
    return q.value(0).toString();
}

QStringList Storage::getOps()
{
    QStringList res;

    QSqlQuery q("SELECT name FROM Op");

    if (!q.isActive()) {
        //журнал
    }

    while (q.next()) { //вернет ложь, если неактивный
        res << q.value(0).toString();
    }

    return res;
}

Storage::~Storage()
{
}
