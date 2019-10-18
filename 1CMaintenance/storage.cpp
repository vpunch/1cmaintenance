#include "storage.h"

#include <QDebug>


Storage::Storage()
{
    //при создании нескольких экземпляров, новое соединение просто заменит старое,
    //так как инициализируются они одинаково
    QSqlDatabase conn = QSqlDatabase::addDatabase("QSQLITE");
    conn.setDatabaseName(
            QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/db");

    if (!conn.open())
        throw StorageError("Can't open database");

    QFile f(":/initdb.sql");
    f.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream s(&f);
    s.setCodec("UTF-8");

    for (const QString& stat : s.readAll().split(';', QString::SkipEmptyParts))
        QSqlQuery q(stat);
}

IBs Storage::getIBs()
{
    IBs ibs;

    QSqlQuery q(R"(
            SELECT name, usr, pass, dbs, path, host, port, db, extusr, extpass FROM InfoBase
    )");

    if (!q.isActive()) {
        //журнал

        return ibs;
    }
    while (q.next()) {
        IBDesc desc = {
            .tmp = false,
            .usr = q.value(1).toString(),
            .pass = q.value(2).toString(),
            .dbs = q.value(3).toString(),
            .path = q.value(4).toString(),
            .host = q.value(5).toString(),
            .port = q.value(6).toString(),
            .db = q.value(7).toString(),
            .extusr = q.value(8).toString(),
            .extpass = q.value(9).toString()
        };

        ibs.emplace_back(q.value(0).toString(), desc);
    }

    return ibs;
}

void Storage::bindIB(QSqlQuery& q, const QString& name, const IBDesc& desc)
{
#define STR_VARIANT(str) str.isEmpty() ? QVariant(QVariant::String) : str

    QVariantList ibTuple = {
        STR_VARIANT(name),
        STR_VARIANT(desc.usr),
        STR_VARIANT(desc.pass),
        STR_VARIANT(desc.dbs),
        STR_VARIANT(desc.path),
        STR_VARIANT(desc.host),
        desc.port.isEmpty() ? QVariant(QVariant::UInt) : desc.port.toUInt(), //вернет 0 в случае неудачи
        STR_VARIANT(desc.db),
        STR_VARIANT(desc.extusr),
        STR_VARIANT(desc.extpass)
    };

    for (auto variant : ibTuple)
        q.addBindValue(variant);
}

bool Storage::saveIB(const QString& name, const IBDesc& desc, const QString& oldName)
{
    QSqlQuery q;

    q.prepare(R"(
            UPDATE InfoBase
            SET name=?, usr=?, pass=?, dbs=?, path=?, host=?, port=?, db=?, extusr=?, extpass=?
            WHERE name=?
    )");
    bindIB(q, name, desc);
    q.addBindValue(oldName); //пустая строка не вызывает ошибку

    if (q.exec() && q.numRowsAffected() == 0) {
        q.clear();

        q.prepare( R"(
                INSERT INTO InfoBase
                VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
        )");
        bindIB(q, name, desc);

        q.exec();
    }

    if (!q.isActive()) {
        //журнал
    }

    return q.isActive();
}

bool Storage::setParam(const QString& name, const QString& value)
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

QString Storage::getParam(const QString& name)
{
    QString quStr = QString("SELECT value FROM Param WHERE name='%1'").arg(name);
    QSqlQuery q(quStr);

    if (!q.isActive()) {
        //журнал
    }

    QString res;
    if (q.next())
        res = q.value(0).toString();

    return res;
}

QStringList Storage::getOps()
{
    QStringList res;

    QSqlQuery q("SELECT name FROM Op");

    if (!q.isActive()) {
        //журнал
    }

    while (q.next()) //вернет ложь, если неактивный
        res << q.value(0).toString();

    return res;
}

Storage::~Storage()
{
}
