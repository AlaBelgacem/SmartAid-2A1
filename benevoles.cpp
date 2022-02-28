#include "benevoles.h"

bool benevoles::ajouter()
{
  QSqlQuery query;
    query.prepare("insert into benevoles (NOM,PRENOM,DATE_NAISSANCE,ADRESSE,TELEPHONE,EMAIL) values(:NOM,:PRENOM,:DATE_NAISSANCE,:ADRESSE,:TELEPHONE,:EMAIL)");
    query.bindValue(":DATE_NAISSANCE",date_naissance);
    query.bindValue(":NOM",nom);
    query.bindValue(":PRENOM",prenom);

    query.bindValue(":ADRESSE",adresse);
    query.bindValue(":TELEPHONE",tel);
    query.bindValue(":EMAIL",email);

    return query.exec();
}

QSqlQueryModel * benevoles::afficher()
{
    //TO DO
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

