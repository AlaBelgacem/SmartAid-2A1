#ifndef CONNECTION_H
#define CONNECTION_H
#include<QtSql/QSqlDatabase>

class connection
{
    QSqlDatabase db;
public:
    connection();
    QSqlDatabase getdb(){return db;}
    bool createconnection();
    void closeconnection();
};

#endif // CONNECTION_H
