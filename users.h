#ifndef USERS_H
#define USERS_H
#include<qstring.h>
#include<QtSql/QSqlQuery>
#include<QtSql/qsqlquerymodel.h>
#include<QMessageBox>
#include"connection.h"
#include<QDate>
#include <QProcess>
#include"employes.h"
#include<time.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

class users
{
private:
    Employes em;
    QString email;
    QString mdp;

public:
    users(){};
    users(Employes e,QString email,QString mdp)
    {
        this->em=e;
        this->email=email;
        this->mdp=mdp;
    }

    //setters
    void setEm(Employes e){this->em=e;}
    void setEmail(QString m){this->email=m;}
    void setMdp(QString m){this->mdp=m;}

    //getters
    Employes getEm(){return em;}
    QString getEmail(){return email;}
    QString getMdp(){return mdp;}

    //functions
    bool Ajouter_user();
    int Login(QString e,QString mdp);
    users session(QString e,QString mdp);
    int Envoyer_sms(QString num);
     int check_token(users u,QString tok);
     bool Maj_pass(users u, QString pass);


};

#endif // USERS_H
