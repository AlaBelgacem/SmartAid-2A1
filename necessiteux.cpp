#include "necessiteux.h"
#include "qrcodegen.hpp"
necessiteux::necessiteux()
{

}


necessiteux::necessiteux(int id,QString nom,QString prenom,QString email,QString telephone,QString adresse,QString date_naissance,QString besoin){
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->email=email;
    this->telephone=telephone;
    this->adresse=adresse;
    this->date_naissance=date_naissance;
    this->besoin=besoin;
}

void necessiteux::setID(int id){
    this->id=id;
}

void necessiteux::setNom(QString nom){
    this->nom=nom;
}

void necessiteux::setPrenom(QString prenom){
    this->prenom=prenom;
}

void necessiteux::setEmail(QString email){
    this->email=email;
}

void necessiteux::setTelephone(QString telephone){
    this->telephone=telephone;
}

void necessiteux::setAdresse(QString adresse){
    this->adresse=adresse;
}

void necessiteux::setDateNai(QString date_naissance){
    this->date_naissance=date_naissance;
}

void necessiteux::setBesoin(QString besoin){
    this->besoin=besoin;
}



int necessiteux::getID(){
    return id;
}

QString necessiteux::getNom(){
    return nom;
}

QString necessiteux::getPrenom(){
    return prenom;
}

QString necessiteux::getEmail(){
    return email;
}

QString necessiteux::getTelephone(){
    return telephone;
}

QString necessiteux::getAdresse(){
    return adresse;
}

QString necessiteux::getDateNai(){
    return date_naissance;
}

QString necessiteux::getBesoin(){
    return besoin;
}


void necessiteux::ajouterNecessiteux(){
    QSqlQuery query;

    QString res = QString::number(id);

    query.prepare("INSERT INTO NÉCESSITEUX (ID_NE,NOM,PRENOM,EMAIL,TELEPHONE,ADRESSE,DATE_NAI,BESOIN)"
                  "VALUES(:id,:nom,:prenom,:email,:telephone,:adresse,:date_naissance,:besoin)");

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":telephone",telephone);
    query.bindValue(":adresse",adresse);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":besoin",besoin);


    if(query.exec()){qDebug()<<"saved\n";}

       else{qDebug()<<"not saved!!!\n";}
}


QSqlQueryModel * necessiteux::afficher(){
    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM NÉCESSITEUX");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));

    return model;

}



bool necessiteux::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Delete from NÉCESSITEUX where ID_NE = :id ");
query.bindValue(":id", res);
return    query.exec();
}


bool necessiteux::modifier(int id)
{
    QSqlQuery query;
    QString res= QString::number(id);
    query.prepare("UPDATE NÉCESSITEUX SET ID_NE=:id,NOM=:nom,PRENOM=:prenom,EMAIL=:email,TELEPHONE=:telephone,ADRESSE=:adresse,"
                  "DATE_NAI=:date_naissance,BESOIN=:besoin WHERE ID_NE=:id");
    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":telephone",telephone);
    query.bindValue(":adresse",adresse);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":besoin",besoin);
    return    query.exec();

}


QSqlQueryModel * necessiteux::rechercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    QString recher="select * from NÉCESSITEUX where nom like '%"+rech+"%' or prenom like '%"+rech+"%' or email like '%"+rech+"%' or besoin like '%"+rech+"%' ";
    model->setQuery(recher);
    return model;
}



QSqlQueryModel * necessiteux::trier(QString x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    qDebug()<<x<<endl;
    if (x=="Défault")
        model->setQuery("select * from NÉCESSITEUX");
    else if(x=="Nom")
        model->setQuery("select * from NÉCESSITEUX order by NOM");
    else if(x=="Prénom")
        model->setQuery("select * from NÉCESSITEUX order by PRENOM");
    else if (x=="Age")
        model->setQuery("select * from NÉCESSITEUX order by DATE_NAI DESC");


        return model;
}
