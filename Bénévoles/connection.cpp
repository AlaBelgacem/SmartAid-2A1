#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("Smart_Aid");
db.setUserName("Salma");
db.setPassword("system");

if(db.open()) test=true;

return test;
}

void Connection::closeConnection(){db.close();}
