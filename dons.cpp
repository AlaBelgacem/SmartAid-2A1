#include "dons.h"

Dons::Dons(int id , QString nom ,QString description ,  QString montant ,int quantite , int id_cat )
{
   this->id=id;
   this->nom=nom;
   this->description=description;
   this->montant=montant ;
   this->quantite=quantite;
   this->id_cat=id_cat;

}
bool Dons ::ajouter ()
{
    QSqlQuery query ;
    QString res=QString::number(id); //convertir int to string
    QString res2=QString::number(quantite);
    QString res3=QString::number(id_cat);
   //prepare() prend la requete en parametre pour la preparer a lexecution
   query.prepare("insert into dons(ID_DON,NOM_DON,DESCRIPTION_DON,MONTANT_DON,QUANTITE_DON,ID_CAT)"
                 "values(:id,:nom,:description,:montant,:quantite,:id_cat)");
   //Creation des variables liees
   query.bindValue(":id",res);
   query.bindValue(":nom",nom);
   query.bindValue(":description",description);
   query.bindValue(":montant",montant);
   query.bindValue(":quantite",res2);
   query.bindValue(":id_cat",res3);

   return query.exec(); //exec() envoie la requete pour lexecuter

}

bool Dons ::supprimer(int id)
{
   QSqlQuery query ; //La classe QSqlQuery permet d'exécuter et de manipuler des instructions SQL.
   query.prepare("Delete from dons where ID_DON= :id"); //prend la requete en parametre pour la preparer a lexecution
   query.bindValue(":id",id); //creation des variables liees
   return query.exec();
}
QSqlQueryModel *Dons ::afficher() //QSqlQueryModel fournit un modèle de données en lecture seule
{
   QSqlQueryModel * model=new QSqlQueryModel();
   model->setQuery("select dons.ID_DON ,dons.NOM_DON, dons.DESCRIPTION_DON ,dons.MONTANT_DON ,dons.QUANTITE_DON, categories.ID_CAT, categories.NOM, categories.DESCRIPTION from DONS "
                   "INNER JOIN CATEGORIES "
                   "ON dons.ID_CAT=categories.ID_CAT");
   model->setHeaderData(0,Qt::Horizontal,QObject::tr("id"));
   model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("description"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("montant"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("quantite"));
   model->setHeaderData(5,Qt::Horizontal,QObject::tr("id categorie"));
   model->setHeaderData(6,Qt::Horizontal,QObject::tr("categorie"));
   model->setHeaderData(7,Qt::Horizontal,QObject::tr("description"));
   return model ;

}

bool Dons::modifier(int id,QString nom,QString description,QString montant,int quantite)
{
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
QSqlQueryModel *Dons::chercher(const QString &d)
{
   QSqlQueryModel * model= new QSqlQueryModel();
   model->setQuery("select * from DONS where (NOM_DON LIKE '"+d+"%')");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_DON"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM_DON"));
   model->setHeaderData(2,Qt::Horizontal,QObject::tr("DESCRIPTION_DON"));
   model->setHeaderData(3,Qt::Horizontal,QObject::tr("MONTANT_DON"));
   model->setHeaderData(4,Qt::Horizontal,QObject::tr("QUANTITE_DON"));
   return model;


}
QSqlQueryModel * Dons::trierC( QString croissance)
{
   QSqlQueryModel* model = new QSqlQueryModel();
   model->setQuery("SELECT * FROM DONS ORDER BY ID_DON ASC ");

   return model;
}

QSqlQueryModel * Dons::trierD( QString croissance)
{
   QSqlQueryModel* model = new QSqlQueryModel();
   model->setQuery("SELECT * FROM DONS ORDER BY ID_DON DESC ");

   return model;
}

void Dons::notification(QString noti)
{
   QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

          notifyIcon->setIcon(QIcon("C:/Users/emnad/Desktop/stat/Gestion_dons - Copie/images/notif.svg"));
          QString s = noti;


           QTableView table;
             QSqlQueryModel * Mod=new  QSqlQueryModel();

                  connection c;
                  QSqlQuery qry,q2;
                  qry.prepare("select QUANTITE_DON, NOM_DON from DONS");
                  qry.exec();
                  Mod->setQuery(qry);
                  table.setModel(Mod);

                  const int rowCount = table.model()->rowCount();
                  //const int columnCount = table.model()->columnCount();

                  for(int i=0;i<rowCount;i++){
                          if(table.model()->data(table.model()->index(i, 0)).toInt()<=5){
                              QString nom=table.model()->data(table.model()->index(i, 1)).toString().simplified(); //1 :colonne 2 : nom
                                      notifyIcon->show();
                                      notifyIcon->showMessage("Gestion des Dons","Le seuil pour "+nom+" est atteint!",QSystemTrayIcon::Information,15000);
                          }
                  }





}
