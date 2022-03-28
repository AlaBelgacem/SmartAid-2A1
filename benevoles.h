#ifndef BENEVOLES_H
#define BENEVOLES_H
#include <QString>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlQueryModel>
#include<QDate>
#include<QDebug>
#include"connection.h"

class benevoles
{
private:

    int id_be ;
    QString nom,prenom,adresse,tel,email,date_naissance;
    bool type ;

public:

    //Constructeurs
    benevoles(){}
    benevoles(int,QString,QString,QString,QString,QString,QString,bool);

    //Getters
    int getId(){return id_be ;}
    QString getNom(){return nom ;}
    QString getPrenom(){return prenom ;}
    QString getAdresse(){return adresse ;}
    QString getTel(){return tel ;}
    QString getEmail(){return email ;}
    QString getDateNaissance(){return date_naissance ;}
    bool getType (){return type ;}

    //Setters
    void setId(int ID){id_be=ID ;}
    void setNom(QString n){nom=n ;}
    void setPrenom(QString p){prenom=p ;}
    void setAdresse(QString ad){adresse=ad ;}
    void setTel(QString te){tel=te ;}
    void setEmail(QString em){email=em ;}
    void setDateNaissance(QString dn){date_naissance=dn ;}
    bool setType(bool t){type=t ;}

    //Fonctionnalités de Base relatives à l'entité benevole
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer();
    bool modifier();
    QSqlQueryModel*chercher(QString nom);
    void generer();
};
#endif // BENEVOLES_H
