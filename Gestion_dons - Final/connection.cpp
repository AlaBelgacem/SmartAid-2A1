#include "connection.h"

connection::connection()
{

}


bool connection::createconnect()
{
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("smart_aid");
db.setUserName("Emna");//inserer nom de l'utilisateur
db.setPassword("emna");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;


    return  test;
}
void connection :: closeconnection()
{
    db.close();
}
