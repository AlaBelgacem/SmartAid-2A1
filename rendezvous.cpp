#include "rendezvous.h"

rendezvous::rendezvous()
{

}


rendezvous::rendezvous(int id_re, QString adresse, QString date, int id_ne){
    this->id_re=id_re;
    this->adresse=adresse;
    this->date=date;
    this->id_ne=id_ne;
}

void rendezvous::setID_Re(int id_re){
    this->id_re=id_re;
}

void rendezvous::setID_Ne(int id_ne){
    this->id_ne=id_ne;
}

void rendezvous::setAdresse(QString adresse){
    this->adresse=adresse;
}

void rendezvous::setDate(QString date){
    this->date=date;
}


int rendezvous::getID_Re(){
   return this->id_re;
}

int rendezvous::getID_Ne(){
   return this->id_ne;
}

QString rendezvous::getAdresse(){
   return this->adresse;
}

QString rendezvous::getDate(){
    return this->date;
}



void rendezvous::ajouter(){
    QSqlQuery query;

    QString res1 = QString::number(id_re);
    QString res2 = QString::number(id_ne);

    query.prepare("INSERT INTO RENDEZ_VOUS (ID_RE,ADRESSE,DATE_RE,ID_NE)"
                  "VALUES(:id_re,:adresse,:date,:id_ne)");

    query.bindValue(":id_re",res1);
    query.bindValue(":adresse",adresse);
    query.bindValue(":date",date);
    query.bindValue(":id_ne",res2);


    if(query.exec()){qDebug()<<"saved\n";}

       else{qDebug()<<"not saved!!!\n";}
}


QSqlQueryModel * rendezvous::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("SELECT r.ID_RE, r.ADRESSE, r.DATE_RE, n.NOM,n.PRENOM,n.DATE_NAI,n.EMAIL,n.TELEPHONE,n.ADRESSE,n.BESOIN FROM RENDEZ_VOUS r "
                    "INNER JOIN NÉCESSITEUX n ON r.ID_NE=n.ID_NE ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID Rendez vous"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Date de naissance"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Telephone"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("Besoin"));


    return model;

}


bool rendezvous::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Delete from RENDEZ_VOUS where ID_RE = :id ");
query.bindValue(":id", res);
return    query.exec();
}


bool rendezvous::modifier(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("UPDATE RENDEZ_VOUS SET ID_RE=:id,ADRESSE=:adresse,DATE_RE=:date  WHERE ID_RE=:id");
    query.bindValue(":id",res);
    query.bindValue(":adresse",adresse);
    query.bindValue(":date",date);

    return    query.exec();

}


QSqlQueryModel * rendezvous::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString recher="select * FROM RENDEZ_VOUS r"
                   "INNER JOIN NÉCESSITEUX n ON r.ID_NE=n.ID_NE"
                   "where ADRESSE like '%"+rech+"%' ";
    model->setQuery(recher);
    return model;
}

