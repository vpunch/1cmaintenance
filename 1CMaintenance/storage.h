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
#include <QUuid>


struct TaskBatch {
    QString uuid;
    QStringList ibs;
    QStringList ops;
    QString time;
};

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

    IBs getIBs();
    bool saveIB(const QString& name,
            const IBDesc& desc,
            const QString& oldName = QString());
    bool removeIB(const QString& name);

    bool setParam(const QString& name, const QString& value);
    QString getParam(const QString& name);

    QStringList getOps();

    std::vector<TaskBatch> getTasks();
    bool saveTasks(const TaskBatch& batch);
    bool removeTask(const QString& uuid);
};

#endif //STORAGE_H
