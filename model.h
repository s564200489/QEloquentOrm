#ifndef MODEL_H
#define MODEL_H


/*********************************************************************************
  *Author:  szj
  *Version:  0.1
  *Date:  2020.5.9
  *Description:
  * It`s base on https://github.com/foreshadow/Inloquent.git
  * a C++ Qt version of PHP Laravel Eloquent style ORM.
  * I fixed some bug and made it support to access multiple database.
**********************************************************************************/






#include <QMap>
#include <QString>
#include <QVariant>
#include <QSqlDatabase>

class Model
{
    friend class Builder;

    class AttributeRef
    {
    public:
        AttributeRef(Model &model, const QString &key);
        QVariant &operator =(const QVariant &value) const;
        QString toString() const;
        operator QVariant() const;
        operator QString() const;
        operator int() const;

    protected:
        Model &model;
        QString key;
    };

public:
    Model();
    Model(const QMap<QString, QVariant> &map);
    virtual ~Model();

    QString get(const QString &key) const;
    int getInt(const QString &key) const;
    void set(const QString &key, const QVariant &value);

    virtual int id() const;
    QStringList keys() const;
    QStringList dirtyKeys() const;

    virtual QString created_at() const;
    virtual QString updated_at() const;
    virtual bool useTimestamps() const;
    void touch();

    /**
     * If the QMap (base class) and original is both empty,
     * this Model is considered to be invalid, vise versa.
     */
    operator bool() const;

    AttributeRef operator [](const char *key);
    AttributeRef operator [](const QString &key);

    bool exists;
    virtual QSqlDatabase getDb();

private:
    void saved();


protected:
    QMap<QString, QVariant> data;
    QMap<QString, QVariant> original;
};

#include "inloquentmodel.h"

#endif // MODEL_H
