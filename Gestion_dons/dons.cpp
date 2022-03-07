#include "dons.h"

Dons::Dons(int id , QString nom ,QString description ,  QString montant ,int quantite  )
{
this->id=id;
    this->nom=nom;
    this->description=description;
    this->montant=montant ;
    this->quantite=quantite;

}
bool Dons ::ajouter ()
{
    QSqlQuery query ;
    QString res=QString::number(id);
     QString res2=QString::number(quantite);

    //prepare() prend la requete en parametre pour la preparer a lexecution
    query.prepare("insert into dons(ID_DON,NOM_DON,DESCRIPTION_DON,MONTANT_DON,QUANTITE_DON)"
                  "values(:id,:nom,:description,:montant,:quantite)");
    //Creation des variables liees
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":description",description);
    query.bindValue(":montant",montant);
    query.bindValue(":quantite",res2);
    return query.exec(); //exec() envoie la requete pour lexecuter

}

bool Dons ::supprimer(int id)
{
    QSqlQuery query ;
    query.prepare("Delete from dons where ID_DON= :id");
    query.bindValue(":id",id);
    return query.exec();
}
QSqlQueryModel *Dons ::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select ID_DON , NOM_DON, DESCRIPTION_DON ,MONTANT_DON ,QUANTITE_DON   from DONS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("montant"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("quantite"));
    return model ;

}

bool Dons::modifier(int id,QString nom,QString description,QString montant,int quantite){
    QSqlQuery query;
    QString res=QString::number(id);
    QString res2=QString::number(quantite);

    query.prepare("UPDATE DONS SET NOM_DON=:nom,DESCRIPTION_DON=:description,MONTANT_DON=:montant,QUANTITE_DON=:quantite WHERE ID_DON=:id");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":description",description);
    query.bindValue(":montant",montant);
    query.bindValue(":quantite",res2);

    return query.exec();

}
