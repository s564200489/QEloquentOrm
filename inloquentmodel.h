#ifndef INLOQUENTMODEL_H
#define INLOQUENTMODEL_H

#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include "builder.h"
#include "collection.h"

#define BUILDER_ADAPTER(method) \
    template<typename ...types> \
    static Builder method(types... args) \
    { return Builder(table()).method(args...); }

#define INLOQUENT_MODEL(class_, tableName, primaryKey_) \
    public: \
        class_() \
        {} \
        class_(Model model) : Model(model) \
        {} \
        class_(const QMap<QString, QVariant> &map) : Model(map)\
        {} \
        static QString className() \
        { return #class_; } \
        static QString table() \
        { return #tableName; } \
        static QString primaryKey() \
        { return #primaryKey_; } \
        static Collection all() \
        { return Builder(table()).select(); } \
        static Model find(const QVariant &key) \
        { return Builder(table()).where(primaryKey(), key).first(); } \
        bool save() \
        { return exists ? Builder(table()).where(primaryKey(), select(primaryKey())).update(*this) : Builder(table()).insert(*this); } \
        /* relations */ \
        template<class T> Collection hasMany(const QString &foreignKey = className().toLower() + "_" + primaryKey(), const QString &localKey = primaryKey()) const \
        { return Builder(T::table()).where(foreignKey, get(localKey)).select(); } \
        template<class T> T hasOne(const QString &foreignKey = className().toLower() + "_" + primaryKey(), const QString &localKey = primaryKey()) const \
        { return Builder(T::table()).where(foreignKey, get(localKey)).first(); } \
        template<class T> Collection belongsToMany(const QString &foreignKey = className().toLower() + "_" + primaryKey(), const QString &localKey = primaryKey()) const \
        { return Builder(T::table()).where(localKey, get(foreignKey)).select(); } \
        template<class T> T belongsTo(const QString &foreignKey = className().toLower() + "_" + primaryKey(), const QString &localKey = primaryKey()) const \
        { return Builder(T::table()).where(localKey, get(foreignKey)).first(); } \
        BUILDER_ADAPTER(where) \
        /* debug */ \
        void dump() \
        { qDebug() << className(); for (QString key : this->keys()) qDebug("%s: %s,", key.toLatin1().data(), (*this)[key].toString().toLatin1().data()); } \
        void dump(const QString &key) \
        { qDebug() << className(); qDebug("%s: %s,", key.toLatin1().data(), (*this)[key].toString().toLatin1().data()); } \


#define BUILDER_ADAPTER_DB(method) \
    template<typename ...types> \
    static Builder method(types... args) \
    { return Builder(table(), connection()).method(args...); }

#define INLOQUENT_MODEL_DB(class_, connectionName, tableName, primaryKey_) \
    public: \
        class_() \
        {} \
        class_(Model model) : Model(model) \
        {} \
        class_(const QMap<QString, QVariant> &map) : Model(map)\
        {} \
        static QSqlDatabase db() \
        { return QSqlDatabase::database(#connectionName); } \
        static QString connection() \
        { return #connectionName; } \
        static QString className() \
        { return #class_; } \
        static QString table() \
        { return #tableName; } \
        static QString primaryKey() \
        { return #primaryKey_; } \
        static Collection all() \
        { return Builder(table(), #connectionName).select(); } \
        static Model find(const QVariant &key) \
        { return Builder(table(), #connectionName).where(primaryKey(), key).first(); } \
        bool save() \
        { return exists ? Builder(table(), #connectionName).where(primaryKey(), get(primaryKey())).update(*this) : Builder(table(), #connectionName).insert(*this); } \
        /* relations */ \
        template<class T> Collection hasMany(const QString &foreignKey = className().toLower() + "_" + primaryKey(), const QString &localKey = primaryKey()) const \
        { return Builder(T::table(), #connectionName).where(foreignKey, get(localKey)).select(); } \
        template<class T> T hasOne(const QString &foreignKey = className().toLower() + "_" + primaryKey(), const QString &localKey = primaryKey()) const \
        { return Builder(T::table(), #connectionName).where(foreignKey, get(localKey)).first(); } \
        template<class T> Collection belongsToMany(const QString &foreignKey = className().toLower() + "_" + primaryKey(), const QString &localKey = primaryKey()) const \
        { return Builder(T::table(), #connectionName).where(localKey, get(foreignKey)).select(); } \
        template<class T> T belongsTo(const QString &foreignKey = className().toLower() + "_" + primaryKey(), const QString &localKey = primaryKey()) const \
        { return Builder(T::table(), #connectionName).where(localKey, get(foreignKey)).first(); } \
        BUILDER_ADAPTER_DB(where) \
        /* debug */ \
        void dump() \
        { qDebug() << className(); for (QString key : this->keys()) qDebug("%s: %s,", key.toLatin1().data(), (*this)[key].toString().toLatin1().data()); } \
        void dump(const QString &key) \
        { qDebug() << className(); qDebug("%s: %s,", key.toLatin1().data(), (*this)[key].toString().toLatin1().data()); } \


/*
#define INLOQUENT_MODEL_CLASS(class_) \
    class class_ : public Model \
    { INLOQUENT_MODEL(class_, class_, id) };
*/

#endif // INLOQUENTMODEL_H
