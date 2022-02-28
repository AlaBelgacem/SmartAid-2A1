#ifndef DONS_H
#define DONS_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class Dons
{
    QString nom ,description,montant ;
    int id ,quantite,seuil ;

public:
    //constructeus
    Dons(){}
    Dons(int,QString,QString,QString,int);
    //getters
    QString getNom(){return nom ;}
    QString getDescription(){return description ;}
    int getID(){return id ;}
    int getQuantite(){return quantite ;}
    int getSeuil(){return seuil ;}
    QString getMontant(){return montant ;}
    //setters
    void setNom(QString n){nom=n;}
    void setDescription(QString d){description=d;}
    void setID(int id){this->id=id;}
    void setQuantite(int q){this->quantite=q;}
    void setSeuil(int s){this->seuil=s;}
    void setMontant(QString m ){this->montant=m;}
    //Fonctionnalités de base relatives à l'entité Dons
    bool ajouter ();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier(int,QString,QString,QString,int);
};

#endif // DONS_H
