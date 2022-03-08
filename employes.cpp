#include "employes.h"
#include <QDebug>

bool Employes::Ajouter_em()
{
    QSqlQuery query;
qDebug() << "11";
    query.prepare("insert into employes (nom,prénom,téléphone,adresse,email,date_nai,image,type,sexe) values (:nom,:prenom,:tele,:adresse,:email,:date,:image,:type,:sexe)");

     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":date",date_nais);
     query.bindValue(":tele",telephone);
     query.bindValue(":adresse",Adresse);
     query.bindValue(":email",email);
     query.bindValue(":image",image);
     query.bindValue(":type",type);
     query.bindValue(":sexe",sexe);
     qDebug() << "22";
     return query.exec();

}

QSqlQueryModel *Employes::Afficher_em()
{
     QSqlQueryModel *modal=new QSqlQueryModel();
     modal->setQuery("select * from employes");
     modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_EM"));
     return modal;

}

bool Employes::Modifier_em()
{
    QSqlQuery query;
    query.prepare("update employes set nom=:nom,prénom=:prenom,téléphone=:tele,adresse=:ad,email=:email,date_nai=:date,image=:i,type=:t,sexe=:s where id_em=:id");
    query.bindValue(":id",id_em);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":date",date_nais);
    query.bindValue(":tele",telephone);
    query.bindValue(":ad",Adresse);
    query.bindValue(":email",email);
     query.bindValue(":i",image);
     query.bindValue(":t",type);
     query.bindValue(":s",sexe);
    return query.exec();
}

bool Employes::Supprimer_em()
{
    QSqlQuery query;
    query.prepare("delete from employes where id_em=:id");
    query.bindValue(":id",id_em);
    return query.exec();
}

QSqlQueryModel *Employes::Rechercher_em(QString value )
{
     QSqlQueryModel *modal=new QSqlQueryModel();
     modal->setQuery("select * from employes where nom='"+value+"' or prénom='"+value+"' or email='"+value+"'");
     return modal;
}

QSqlQueryModel *Employes::Trier_em(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "ID" && croissance == "ASC")
        modal->setQuery("select * from employes order by ID_EM ASC ");
    else if(critere == "ID" && croissance == "DESC")
        modal->setQuery("select * from employes order by ID_EM DESC ");

    else if(critere == "Nom" && croissance == "ASC")
        modal->setQuery("select * from employes order by NOM ASC ");
    else if(critere == "Nom" && croissance == "DESC")
        modal->setQuery("select * from employes order by NOM DESC ");

    else if(critere == "Prenom" && croissance == "ASC")
        modal->setQuery("select * from employes order by prénom ASC ");
    else if(critere == "Prenom" && croissance == "DESC")
        modal->setQuery("select * from employes order by prénom DESC ");

    else if(critere == "Adresse" && croissance == "ASC")
        modal->setQuery("select * from employes order by ADRESSE ASC ");
    else if(critere == "Adresse" && croissance == "DESC")
        modal->setQuery("select * from employes order by ADRESSE DESC ");

    else if(critere == "Email" && croissance == "ASC")
        modal->setQuery("select * from employes order by email ASC ");
    else if(critere == "Email" && croissance == "DESC")
        modal->setQuery("select * from employes order by email DESC ");

    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from employes order by prénom");
    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from employes order by prénom");

    else if(critere == "Email" && croissance == "")
        modal->setQuery("select * from employes order by email");
    else if(critere == "Email" && croissance == "")
        modal->setQuery("select * from employes order by email");

    else if(critere == "Adresse" && croissance == "")
        modal->setQuery("select * from employes order by ADRESSE");
    else if(critere == "Adresse" && croissance == "")
        modal->setQuery("select * from employes order by ADRESSE");

    else if(critere == "ID" && croissance == "")
        modal->setQuery("select * from employes order by ID_EM");
    else if(critere == "ID" && croissance == "")
        modal->setQuery("select * from employes order by ID_EM");

    else if(critere == "Nom" && croissance == "")
        modal->setQuery("select * from employes order by NOM");
    else if(critere == "Nom" && croissance == "")
        modal->setQuery("select * from employes order by NOM");

    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from employes order by prénom");
    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from employes order by prénom");

    return  modal;
}



