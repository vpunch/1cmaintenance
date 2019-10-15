#ifndef STORAGE_H
#define STORAGE_H

#include <stdexcept>
#include <map>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QFile>
#include <QStandardPaths>
#include <QTextStream>


class StorageError : public std::runtime_error {
public:
    explicit StorageError(const std::string& expl) : std::runtime_error(expl) { }
};

struct IBDesc {
    bool tmp;
    QString usr, passwd, dbs, path, host, port, db, dbusr;
};

Q_DECLARE_METATYPE(IBDesc)

using IBs = std::map<QString, IBDesc>;

//если возникает ошибка извлечения данных из базы, то клиент получает пустой ответ
//или отрицание, а ошибка фиксируется в журнале
class Storage {
    QString fillQuStr(const QString& str, const IBDesc& desc);

public:
    Storage();
    ~Storage();

    IBs getIBs();
    bool saveIB(const QString& name,
            const IBDesc& desc,
            const QString& oldName = QString());

    bool setParam(const QString name, const QString& value);
    QString getParam(const QString name);

    QStringList getOps();
};

#endif // STORAGE_H
