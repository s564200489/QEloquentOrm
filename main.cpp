#include <bits/stdc++.h>
#include "model.h"
#include "db.h"
#include <QSqlResult>
using namespace std;

class User : public Model
{
    INLOQUENT_MODEL_DB(User, user, users, id);
public:
    static void regist(BluePrint *table){
        table->increment("id")->unique();
        table->string("name");
        table->string("info");
    }
};

class Pet : public Model
{
    INLOQUENT_MODEL_DB(Pet, pet, pets, id);
public:
    static void regist(BluePrint *table){
        table->increment("id")->unique();
        table->string("petname");
        //table->timestamps();
    }
};



int main(int, char *[])
{
    if (DB::initialize("QSQLITE", "user.db","user") == false)
        qDebug()<<"init db faill"<<DB::lastErrorMessage();
    if (DB::initialize("QSQLITE", "pet.db","pet") == false)
        qDebug()<<"init db faill"<<DB::lastErrorMessage();

    bool ok = DB::createIfNotExists<User>(User::regist);
    if (ok == false)
        qDebug() << DB::lastErrorMessage();

    ok = DB::createIfNotExists<Pet>(Pet::regist);
        if (ok == false)
            qDebug() << DB::lastErrorMessage();


    User user;
    user.set("name", "Infinity");
    if (user.save() == false)
        qDebug() << DB::lastErrorMessage();
    return  1;
    qDebug()<<"User::find"<<User::find(1).get("name");

    auto li = User::where("name", "Infinity").select();
    if(li.size() > 0)
        qDebug()<<"get "<<li[0].get("name");
    //Q_ASSERT(User::find(1).get("name") == "Infinity");
    //Q_ASSERT(User::where("name", "Infinity").first()["id"] == 1);
    return 0;
}
