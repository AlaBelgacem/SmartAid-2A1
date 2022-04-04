#include "evenements.h"
#include <QDate>
Evenements::Evenements(int id_event,int code_postal,QString nom,QString description,QString ville, QDateTime date_deb,QString type)
{
    this->id_event=id_event;
    this->id_event=id_event;
    this->code_postal=code_postal;
    this->nom=nom;
    this->description=description;
    this->ville=ville;
    this->date_deb=date_deb;
    this->type=type;

}

bool Evenements::ajouter()
{
    QSqlQuery query;//QSql query est une classe qui permet d'utiliser et de manipuler des instructions SQL
    //Inserer dans la base de données Concernée les données de l'instance (Commandes SQL)
    query.prepare("INSERT INTO EVENEMENTS(NOM,VILLE,TYPE,DATE_DEB,CODE_POSTAL,DESCRIPTION) VALUES (:nom,:ville,:type,:date,:code,:desc)");

    query.bindValue(":nom",nom);
    query.bindValue(":ville",ville);
    query.bindValue(":type",type);
    query.bindValue(":code",code_postal);
    query.bindValue(":date",date_deb);
    query.bindValue(":desc",description);
    //  BIND VALUE permet d'identifier des paramètres,Pour une requête préparée utilisant des marqueurs


    return query.exec();
}
QSqlQueryModel*Evenements:: afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from EVENEMENTS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("VILLE"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DATE_DEB"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE_POSTAL"));
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    return model;
}


bool Evenements::Modifier()
{
    QSqlQuery query;

    query.prepare("UPDATE EVENEMENTS SET NOM=:nom,VILLE=:ville,TYPE=:type,DATE_DEB=:date,CODE_POSTAL=:code,DESCRIPTION=:desc WHERE ID_EV=:id ");
    query.bindValue(":id",id_event);
    query.bindValue(":nom",nom);
    query.bindValue(":ville",ville);
    query.bindValue(":type",type);
    query.bindValue(":code",code_postal);
    query.bindValue(":date",date_deb);
    query.bindValue(":desc",description);
    return query.exec();
}

bool Evenements::supprimer ()
{
    QSqlQuery query;

    query.prepare("DELETE FROM EVENEMENTS WHERE ID_EV=:id");
    query.bindValue(":id",id_event);
    return query.exec();
}


QSqlQueryModel* Evenements::afficher_Tri(int ordre)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    if (ordre==0)
        model->setQuery("select * from EVENEMENTS ORDER BY ID_EV ASC");
    else
       model->setQuery("select * from EVENEMENTS ORDER BY ID_EV DESC");


    return model;
}

QSqlQueryModel* Evenements::afficher_Tri2(int ordre)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    if (ordre==0)
        model->setQuery("select * from EVENEMENTS ORDER BY NOM ASC");
    else
        model->setQuery("select * from EVENEMENTS ORDER BY NOM DESC");


    return model;
}
QSqlQueryModel* Evenements::afficher_Tri3(int ordre)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    if (ordre==0)
        model->setQuery("select * from EVENEMENTS ORDER BY DATE_DEB  ASC");
    else
        model->setQuery("select * from EVENEMENTS ORDER BY DATE_DEB  DESC");


    return model;
}
