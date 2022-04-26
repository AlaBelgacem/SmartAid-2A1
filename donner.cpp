#include "donner.h"

donner::donner()
{

}


donner::donner(int id_ne, int id_don, int quantite, float montant)
{
    this->id_ne=id_ne;
    this->id_don=id_don;
    this->quantite=quantite;
    this->montant=montant;
}


bool donner::ajouter ()
{
    QTableView table;
    QSqlQueryModel * Mod=new  QSqlQueryModel();

         QSqlQuery qry;




    QSqlQuery query,q2,q3 ;
    QString res=QString::number(id_ne); //convertir int to string
    QString res2=QString::number(id_don);

   //prepare() prend la requete en parametre pour la preparer a lexecution
   query.prepare("insert into donner(ID_NE,ID_DON)"
                 "values(:id_ne,:id_don)");
   //Creation des variables liees
   query.bindValue(":id_ne",res);
   query.bindValue(":id_don",res2);



   /// quantite de la table dons
   qry.prepare("select QUANTITE_DON, MONTANT_DON from DONS WHERE ID_DON=:id");
   qry.bindValue(":id",res2);
   qry.exec();
   Mod->setQuery(qry);
   table.setModel(Mod);

   int qu = table.model()->data(table.model()->index(0, 0)).toInt();
   float mo = table.model()->data(table.model()->index(0, 1)).toFloat();
   int new_qu=qu-quantite;
   float new_mon=mo-montant;

   QString result= QString::number(new_mon);

   QString res3=QString::number(new_qu);
   qDebug()<<qu;
   if(new_qu>0 && new_mon>0){
   q2.prepare("UPDATE DONS SET QUANTITE_DON=:quantite, MONTANT_DON=:montant WHERE ID_DON=:id_don");
   q2.bindValue(":quantite",res3);
   q2.bindValue(":montant",result);
   q2.bindValue(":id_don",res2);
   q2.exec();
}
   return query.exec(); //exec() envoie la requete pour lexecuter

}
/*
bool donner ::supprimer(int id)
{
   QSqlQuery query ; //La classe QSqlQuery permet d'exécuter et de manipuler des instructions SQL.
   query.prepare("Delete from donner where ID_NE= :id"); //prend la requete en parametre pour la preparer a lexecution
   query.bindValue(":id",id); //creation des variables liees
   return query.exec();
}
*/
