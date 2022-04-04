#ifndef DONS_H
#define DONS_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include "connection.h"


class Dons
{


    QString nom ,description,montant ;
    int id ,quantite,seuil,id_cat ;

public:
    //constructeur pour allouer de la mémoire pour les attributs
    Dons(){}
    Dons(int,QString,QString,QString,int,int);
    //getters
    QString getNom(){return nom ;}
    QString getDescription(){return description ;}
    int getID(){return id ;}
    int getIDCat(){return id_cat ;}
    int getQuantite(){return quantite ;}
    int getSeuil(){return seuil ;}
    QString getMontant(){return montant ;}
    //setters
    void setNom(QString n){nom=n;}
    void setDescription(QString d){description=d;}
    void setID(int id){this->id=id;}
    void setIDCat(int id_cat){this->id_cat=id_cat;}
    void setQuantite(int q){this->quantite=q;} //this pour différencier le paramétre de l'attribut
    void setSeuil(int s){this->seuil=s;}
    void setMontant(QString m ){this->montant=m;}
    //Fonctionnalités de base relatives à l'entité Dons
    bool ajouter ();
    QSqlQueryModel * afficher(); //La classe QSqlQueryModel fournit un modèle de données en lecture seule pour les ensembles de résultats SQL.
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,int);
    QSqlQueryModel *chercher(const QString &);
    QSqlQueryModel *trierC(QString );
    QSqlQueryModel *trierD(QString );

};

#endif // DONS_H
