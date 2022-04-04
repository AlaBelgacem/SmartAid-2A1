#include "categories.h"

Categories::Categories(int idC , QString nomC ,QString descriptionC )
{
   this->idC=idC;
   this->nomC=nomC;
   this->descriptionC=descriptionC;
}
bool Categories ::ajouterC ()
{
    QSqlQuery query ;
    QString res=QString::number(idC); //convertir int to string


   //prepare() prend la requete en parametre pour la preparer a lexecution
   query.prepare("insert into CATEGORIES(ID_CAT,NOM,DESCRIPTION)"
                 "values(:idC,:nomC,:descriptionC)");
   //Creation des variables liees
   query.bindValue(":idC",res);
   query.bindValue(":nomC",nomC);
   query.bindValue(":descriptionC",descriptionC);
   return query.exec(); //exec() envoie la requete pour lexecuter

}

bool Categories ::supprimerC(int idC)
{
   QSqlQuery query ; //La classe QSqlQuery permet d'exécuter et de manipuler des instructions SQL.
   query.prepare("Delete from CATEGORIES where ID_CAT= :idC"); //prend la requete en parametre pour la preparer a lexecution
   query.bindValue(":idC",idC); //creation des variables liees
   return query.exec();
}
QSqlQueryModel *Categories ::afficherC() //QSqlQueryModel fournit un modèle de données en lecture seule
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("select ID_CAT , NOM, DESCRIPTION from CATEGORIES");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("idC"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("nomC"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("descriptionC"));
   return model ;

}

bool Categories::modifierC(int idC,QString nomC,QString descriptionC)
{
   QSqlQuery query;
   QString res=QString::number(idC);


   query.prepare("UPDATE CATEGORIES SET NOM=:nomC,DESCRIPTION=:descriptionC WHERE ID_CAT=:idC");
   query.bindValue(":idC",res);
   query.bindValue(":nomC",nomC);
   query.bindValue(":descriptionC",descriptionC);

   return query.exec();

}
QSqlQueryModel *Categories::rechercher(const QString &c)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CATEGORIES where (NOM LIKE '"+c+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_CAT"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    return model;


}
QSqlQueryModel * Categories::triC( QString croissance)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CATEGORIES ORDER BY ID_CAT ASC ");

    return model;
}

QSqlQueryModel * Categories::triD( QString croissance)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM CATEGORIES ORDER BY ID_CAT DESC ");

    return model;
}



