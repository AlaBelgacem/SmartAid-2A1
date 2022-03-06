#ifndef NECESSITEUX_H
#define NECESSITEUX_H
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



class necessiteux
{
    QString nom,prenom,email,adresse,date_naissance,besoin,telephone;
    int id;

public:
    //constructors
    necessiteux();
    necessiteux(int,QString,QString,QString,QString,QString,QString,QString);
    //
    // getters
    int getID();
    QString getNom();
    QString  getPrenom();
    QString  getEmail();
    QString getTelephone();
    QString  getAdresse();
    QString  getDateNai();
    QString  getBesoin();

     //////////////      CRUD        ///////////////////

    void ajouterNecessiteux();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int);
    ////////////////// METIERS ////////////////////////

    QSqlQueryModel * rechercher(QString);

    ////////////////////////////////////////////////////
    //setters
    void setID(int id);
    void setNom(QString nom);
    void setPrenom(QString prenom);
    void setEmail(QString email);
    void setTelephone(QString telephone);
    void setAdresse(QString adresse);
    void setDateNai(QString date_naissance);
    void setBesoin(QString besoin);

};

#endif // NECESSITEUX_H
