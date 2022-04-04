#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class Connection
{
    QSqlDatabase db;
public:
    QSqlDatabase getDB()
    {
        return db;
    }
    Connection();
    bool createconnect();
    void closeconnection();
};

#endif // CONNECTION_H
