#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql/QSqlDatabase>

class Connection
{
    QSqlDatabase db;
public:
    Connection();
    QSqlDatabase getdb()
    {
        return db;
    }
    bool createconnection();
    void closeConnection();
};

#endif // CONNECTION_H
