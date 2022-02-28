#include "crises.h"
#include <QDebug>
#include <QSqlRecord>
Crises::Crises ( QString nom,QString adresse, int niveau,QString description,  QDate date_cr,QString etat)

{

this->nom=nom;
this->adresse=adresse;
this->niveau=niveau;
this->description=description;
this->date_cr=date_cr;
this->etat=etat;

}


bool Crises::ajouter()

{

QSqlQuery query;
QString res = QString::number(niveau);

//prepare( prend la requete en parametre pour la préparer à l'exécution

query.prepare("insert into crises (nom,adresse,niveau,description,date_cr,etat)"
              "values(:nom,:adresse,:niveau,:description,:date_cr,:etat)");

//Création des variables liées

query.bindValue(":nom",nom);
query.bindValue(":adresse",adresse);
query.bindValue(":niveau",res);
query.bindValue(":description",description);
query.bindValue(":date_cr",date_cr);
query.bindValue(":etat",etat);

return query.exec(); //exec() envoie la requete pour l'executer

}

QSqlQueryModel * Crises::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select id_cr,nom,adresse from crises");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Desciption"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Niveau"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Etat"));

    return model;
}

bool Crises::supprimer (int id)
{
    QSqlQuery query;
    query.prepare("Delete from crises where ID_CR=:id");
    query.bindValue(":id",id);

    return query.exec();
}


bool Crises::modifier(int id, QString nom,QString adresse, int niveau,QString description,  QDate date_cr,QString etat)
{
    QSqlQuery query;


    query.prepare("update Crises set Nom = :nom, Adresse= :adresse, Niveau= :niveau, Description= :description, Date_Cr= :date_cr,Etat= :etat  WHERE ID_CR = :id");
    query.bindValue(":nom", nom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":niveau", niveau);
    query.bindValue(":description", description);
    query.bindValue(":date_cr", date_cr);
    query.bindValue(":etat", etat);
    query.bindValue(":id",id);
    return query.exec();
}
