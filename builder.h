#ifndef BUILDER_H
#define BUILDER_H

#include <QString>
#include <QVariant>
#include <QSqlQuery>
#include "model.h"
#include "collection.h"

class Collection;

class Builder
{
    friend class BluePrint;

    class Query : public QSqlQuery
    {
    public:
        Query(const QString &statement);
        Query(const QString &statement, QSqlDatabase db);
        operator bool();

    protected:
        bool succeeded;
    };

public:
    explicit Builder(const QString &table);
    explicit Builder(const QString &table,const QString connecName);
    bool insert(Model &model);
    bool update(Model &model);

    Builder &where(const QString &key, const QString &op, const QVariant &value,
                   const QString &boolean = "and");
    Builder &where(const QString &key, const QVariant &value);

    Builder &take(int limit);
    Builder &skip(int offset);

    Collection select(const QString &column = "*") const;
    //Collection get(const QString &column = "*") const;
    Model first();
    static Query exec(const QString &statement, QSqlDatabase db=QSqlDatabase::database());

    template<typename T>
    static Query exec_(const QString &statement){
        return Query(statement,T::db());
    };

private:

    QString escapeTable() const;
    QString escapeKey(const QString &key) const;
    QString escapeValue(const QVariant &value) const;

protected:
    QString tableClause;
    QString whereClause;
    QString groupByClause;
    QString havingClause;
    QString orderByClause;
    QString connectionName;
    int limit;
    int offset;
};

#endif // BUILDER_H
