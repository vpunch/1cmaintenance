#ifndef STORAGE_H
#define STORAGE_H

#include <stdexcept>
#include <vector>
#include <utility>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>


struct IBDesc {
    bool tmp;
    QString usr, pass, dbs, path, host, port, db, extusr, extpass;
};

Q_DECLARE_METATYPE(IBDesc)

using IBs = std::vector<std::pair<QString, IBDesc>>;

class StorageError : public std::runtime_error {
public:
    explicit StorageError(const std::string& expl) : std::runtime_error(expl) { }
};

/*
 * Обертка над встраиваемой базой данных.
 * Если возникает ошибка извлечения данных, клиент получает пустой ответ или отрицание.
 * Сама ошибка фиксируется в специальном журнале.
 */
class Storage {
    void bindIB(QSqlQuery& q, const QString& name, const IBDesc& desc);

public:
    Storage();
    ~Storage();

    IBs getIBs();
    bool saveIB(const QString& name,
            const IBDesc& desc,
            const QString& oldName = QString());

    bool setParam(const QString& name, const QString& value);
    QString getParam(const QString& name);

    QStringList getOps();
};

#endif //STORAGE_H
