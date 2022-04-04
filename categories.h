#ifndef CATEGORIES_H
#define CATEGORIES_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include "connection.h"


class Categories
{


    QString nomC ,descriptionC ;
    int idC ;

public:
    //constructeur pour allouer de la mémoire pour les attributs
    Categories(){}
    Categories(int,QString,QString);
    //getters
    QString getNom(){return nomC ;}
    QString getDescription(){return descriptionC ;}
    int getID(){return idC ;}

    //setters
    void setNom(QString nC){nomC=nC;}
    void setDescription(QString dC){descriptionC=dC;}
    void setID(int idC){this->idC=idC;}//this pour différencier le paramétre de l'attribut

    //Fonctionnalités de base relatives à l'entité Dons
    bool ajouterC ();
    QSqlQueryModel * afficherC(); //La classe QSqlQueryModel fournit un modèle de données en lecture seule pour les ensembles de résultats SQL.
    bool supprimerC(int);
    bool modifierC(int,QString,QString);
    QSqlQueryModel *rechercher(const QString &);
    QSqlQueryModel *triC(QString );
    QSqlQueryModel *triD(QString );
};

#endif // CATEGORIES_H
