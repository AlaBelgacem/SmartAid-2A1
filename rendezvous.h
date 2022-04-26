#ifndef RENDEZVOUS_H
#define RENDEZVOUS_H
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlQueryModel>
#include <QDate>
#include <QDateEdit>
#include <QDateTime>
#include <QCalendarWidget>

class rendezvous
{
private:
    int id_re, id_ne;
    QString adresse, date;
public:
    rendezvous();
    rendezvous(int,QString,QString,int);

    /////////////// getters
    int getID_Re();
    int getID_Ne();
    QString getAdresse();
    QString getDate();

    ////////////// setters
    void setID_Re(int id_re);
    void setID_Ne(int id_ne);
    void setAdresse(QString adresse);
    void setDate(QString date);

    ////////////// CRUD //////////////////
    void ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
    ///////////////////////////////////////
    QSqlQueryModel * rechercher(QString rech);
    QSqlQueryModel * trier(QString);
};

#endif // RENDEZVOUS_H
