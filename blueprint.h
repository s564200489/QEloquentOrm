#ifndef BLUEPRINT_H
#define BLUEPRINT_H

#include <QList>
#include <QString>
#include "builder.h"

class BluePrint
{
    /**
     * Only my friends can touch my private,
     * neither my parents nor my children.
     */
    friend class DB;

    class Column
    {
    public:
        Column(const QString &name, const QString &type, bool primaryKey = false);
        Column *primaryKey();
        Column *nullable();
        Column *unique();
        Column *autoIncrement();
        QString toSql();

    protected:
        QString name;
        QString type;
        bool pk;
        bool nn = true;
        bool u = false;
        bool ai = false;
    };

public:
    BluePrint(const QString &predicate, const QString &table);
    ~BluePrint();

    Column *increment(const QString &name);
    Column *integer(const QString &name);
    Column *string(const QString &name);
    Column * timestamps(const QString &name);
    void timestamps();

private:
    bool commit();

    template<typename T>
    bool commit_(){
        QStringList lines;
        for (Column *c : columns)
            lines.append(c->toSql());
        QString statement = QString("%1 %2 (%3);").arg(predicate, table, lines.join(", "));
        return Builder::exec(statement, T::db());
    };

protected:
    QString predicate;
    QString table;
    QList<Column *> columns;
};

#endif // BLUEPRINT_H
