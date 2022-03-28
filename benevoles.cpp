#include "benevoles.h"
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>


bool benevoles::ajouter()
{
  QSqlQuery query;

  //prepare() prend la requete en paramètre à l'exécution

    query.prepare("insert into benevoles (NOM,PRENOM,DATE_NAISSANCE,ADRESSE,TELEPHONE,EMAIL) values(:NOM,:PRENOM,:DATE_NAISSANCE,:ADRESSE,:TELEPHONE,:EMAIL)");

  //Création des variables liées

    query.bindValue(":DATE_NAISSANCE",date_naissance);
    query.bindValue(":NOM",nom);
    query.bindValue(":PRENOM",prenom);
    query.bindValue(":ADRESSE",adresse);
    query.bindValue(":TELEPHONE",tel);
    query.bindValue(":EMAIL",email);

    return query.exec(); //exec envoie la requete pour l'exécuter
}


QSqlQueryModel * benevoles::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from benevoles");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_BE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));

    qDebug()<< model;

    return model;
}


bool benevoles::supprimer()
{
    QSqlQuery query;

        query.prepare("delete from benevoles where id_be=:id");
        query.bindValue(":id",id_be);

        return query.exec();
}

bool benevoles::modifier()
{
    QSqlQuery query;
    query.prepare("update benevoles set NOM=:nom,PRENOM=:prenom,DATE_NAISSANCE=:date_naissance,ADRESSE=:adresse,TELEPHONE=:tel,EMAIL=:email where id_be=:id");
      query.bindValue(":date_naissance",date_naissance);
      query.bindValue(":nom",nom);
      query.bindValue(":prenom",prenom);
      query.bindValue(":adresse",adresse);
      query.bindValue(":tel",tel);
      query.bindValue(":email",email);
      query.bindValue(":id",id_be);

      return query.exec();
  }

    QSqlQueryModel* benevoles::chercher(QString nom)
    {
       QSqlQueryModel* model = new QSqlQueryModel();
       QString search = "%"+nom+"%";
        model->setQuery("SELECT * FROM BENEVOLES WHERE NOM like '"+search+"'");

        return model ;
}

    void benevoles::generer()
    {
         QSqlQuery query;
         query.prepare("SELECT * FROM benevoles");
         if(query.exec())
         {
             QFile file("C:/Users/salma/OneDrive/Documents/GitHub/SmartAid-2A1/BENEVOLES.xlsx");
                   file.open(QIODevice::WriteOnly | QIODevice::Text);
                   QTextStream out(&file);

             while(query.next())
             {
                  out << "Test , hhhh \n ggggg";
             }
         }
    }
