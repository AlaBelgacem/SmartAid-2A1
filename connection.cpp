#include "connection.h"

connection::connection()
{

}


bool connection::createconnect()
{
    bool test=false;
db = QSqlDatabase::addDatabase("QODBC");

db.setDatabaseName("SmartAid");
db.setUserName("Ala");//inserer nom de l'utilisateur
db.setPassword("illsink");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;


    return  test;
}


void connection::closeconnection(){
    db.close();
}
