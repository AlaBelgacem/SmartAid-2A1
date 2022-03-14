#ifndef EMPLOYES_H
#define EMPLOYES_H
#include<qstring.h>
#include<QtSql/QSqlQuery>
#include<QtSql/qsqlquerymodel.h>
#include<QMessageBox>
#include"connection.h"
#include<QDate>


class Employes
{
private:
    int id_em;
    QString nom;
    QString prenom;
    QString date_nais;
    QString telephone;
    int code_postal;
    QString Adresse;
    QString ville;
    QString email;
    QString type;
    QString image;
    QString sexe;

public:
    //costructeurs
    Employes(){};
    Employes(int id,QString nom,QString prenom,QString date,QString email,QString ad,QString telephone,QString im,QString type,QString sexe)
   {
       this->id_em=id;
       this->nom=nom;
       this->prenom=prenom;
       this->date_nais=date;
       this->email=email;
       this->telephone=telephone;
       this->Adresse=ad;
       this->image=im;
       this->type=type;
        this->sexe=sexe;

   }

    //setters
    void setID_em(int i){id_em=i;}
    void setNom(QString n){nom=n;}
    void setPrenom(QString n){prenom=n;}
    void setDate_nais(QString n){date_nais=n;}
    void setTelephone(QString n){telephone=n;}
    void setAdresse(QString n){Adresse=n;}
    void setCode_postal(int n){code_postal=n;}
    void setVille(QString n){ville=n;}
    void setEmail(QString n){email=n;}
    void setImage(QString n){image=n;}
    void setType(QString n){type=n;}
    void setSexe(QString n){sexe=n;}
    //getters
    int getID_em(){return id_em;}
    QString getTelephone(){return telephone;}
    int getCode_postal(){return code_postal;}
    QString getNom(){return nom;}
    QString getAdresse(){return Adresse;}
    QString getPrenom(){return prenom;}
    QString getDate_nais(){return date_nais;}
    QString getVille(){return ville;}
    QString getEmail(){return email;}
    QString getImage(){return image;}
    QString getType(){return type;}
    QString getSexe(){return sexe;}

    //functions
    bool Ajouter_em();
    QSqlQueryModel *Afficher_em();
    bool Modifier_em();
    bool Supprimer_em();
    QSqlQueryModel *Rechercher_em(QString value );
    QSqlQueryModel *Trier_em(QString croissance,QString critere);


};

#endif // EMPLOYES_H
