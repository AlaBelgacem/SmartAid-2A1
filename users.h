#ifndef USERS_H
#define USERS_H
#include<qstring.h>
#include<QtSql/QSqlQuery>
#include<QtSql/qsqlquerymodel.h>
#include<QMessageBox>
#include"connection.h"
#include<QDate>
#include"employes.h"

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
    bool Login(QString e,QString mdp);
    users session(QString e,QString mdp);


};

#endif // USERS_H
