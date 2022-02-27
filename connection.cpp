#include "connection.h"

connection::connection(){}

bool connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("smart_aid");
    db.setUserName("louay");
    db.setPassword("louayy");
    if(db.open()) test=true;
    return test;
}

void connection::closeconnection(){db.close();}
