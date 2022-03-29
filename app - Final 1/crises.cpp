#include "crises.h"
#include <QDebug>
#include <QSqlRecord>


Crises::Crises ( QString nom,QString adresse, int niveau,QString description,  QString date_cr,QString etat) //classe::constructeur

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

QSqlQuery query; //La classe QSqlQuery permet d'exécuter et de manipuler des instructions SQL.
QString res = QString::number(niveau);

//prepare () prend la requete en parametre pour la préparer à l'exécution

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
    QSqlQueryModel * model=new QSqlQueryModel(); //La classe QSqlQueryModel fournit un modèle de données en lecture seule pour les ensembles de résultats SQL.
    model->setQuery("select * from crises");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NIVEAU"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_CR"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ETAT"));
    //qDebug()<< model;
    return model;
}

bool Crises::supprimer (int id)
{
    QSqlQuery query;
    query.prepare("Delete from crises where ID_CR=:id");
    query.bindValue(":id",id);

    return query.exec();
}


bool Crises::modifier(int id, QString nom,QString adresse, int niveau,QString description,  QString date_cr,QString etat)
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


QSqlQueryModel *Crises::rechercher(const QString &c)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from crises where (NOM LIKE '"+c+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CR"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NIVEAU"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DESCRIPTION"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("DATE_CR"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("ETAT"));
    return model;


}

QSqlQueryModel * Crises::trierC( QString croissance)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Crises ORDER BY ID_CR ASC ");

    return model;
}

QSqlQueryModel * Crises::trierD( QString croissance)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Crises ORDER BY ID_CR DESC ");

    return model;
}


void Crises::stat(QString *x1,QString *x2,QString *x3){
    int somme(0);
    int y1(0),y2(0),y3(0);
    QSqlQuery query,query1,query2,query3;
    query.prepare("select count(ID_CR) from Crises");
    if(query.exec())
    while(query.next())
    {
        somme = query.value(0).toInt();
    }
    query1.prepare("select count(ID_CR) from Crises where etat = 'Traiter'");
    if(query1.exec())
        while(query1.next())
        {
            y1 = query1.value(0).toInt();
        }
    query2.prepare("select count(ID_CR) from Crises where etat = 'En cours'");
    query2.exec();
    while(query2.next())
    {

      y2 = query2.value(0).toInt();}
     query3.prepare("select count(ID_CR) from Crises where etat = 'Non traiter'");
        query3.exec();
        while(query3.next())
        {

            y3 = query2.value(0).toInt();


    }
    y1 = (y1 * 100)/somme;
    y2 = (y2 * 100)/somme;
    y3 = (y3 * 100)/somme;

    *x1 = QString::number(y1);
    *x2 = QString::number(y2);
    *x3 = QString::number(y3);


}

float Crises::etatT()
{
double somme=0;
int y1(0);
double pourcent ;
QSqlQuery query,query1,query2,query3;
query.prepare("select count(ID_CR) from Crises");
if(query.exec())
while(query.next())
{
    somme = query.value(0).toInt();
}
query1.prepare("select count(ID_CR) from Crises where etat = 'Traiter'");
if(query1.exec())
    while(query1.next())
    {
        y1 = query1.value(0).toInt();
    }

    pourcent=(y1 * 100)/somme;
return pourcent ;
}
float Crises::etatEC()
{
double somme=0;
int y1(0);
double pourcent ;
QSqlQuery query,query1,query2,query3;
query.prepare("select count(ID_CR) from Crises");
if(query.exec())
while(query.next())
{
    somme = query.value(0).toInt();
}
query1.prepare("select count(ID_CR) from Crises where etat = 'En cours'");
if(query1.exec())
    while(query1.next())
    {
        y1 = query1.value(0).toInt();
    }

    pourcent=(y1 * 100)/somme;
return pourcent ;
}
float Crises::etatNT()
{
double somme=0;
int y1(0);
double pourcent ;
QSqlQuery query,query1,query2,query3;
query.prepare("select count(ID_CR) from Crises");
if(query.exec())
while(query.next())
{
    somme = query.value(0).toInt();
}
query1.prepare("select count(ID_CR) from Crises where etat = 'Non traiter'");
if(query1.exec())
    while(query1.next())
    {
        y1 = query1.value(0).toInt();
    }

    pourcent=(y1 * 100)/somme;
return pourcent ;
}
