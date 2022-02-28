#include "connection.h"

connection::connection()
{

}


bool connection::createconnect()
{
    db=QSqlDatabase :: addDatabase("QODBC");
    bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("SmartAid");
db.setUserName("Essyl");//inserer nom de l'utilisateur
db.setPassword("Essyl");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;


    return  test;
}

void connection :: closeConnection()
{
    db.close();
}
