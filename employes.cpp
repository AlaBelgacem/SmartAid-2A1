#include "employes.h"
#include <QDebug>

bool Employes::Ajouter_em()
{
    QSqlQuery query;

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

bool Employes::Ajouter_sa_em()
{
    QSqlQuery query;
    query.exec("SELECT MAX( id_em ) FROM employes;");
    query.next();
    QString id=query.value(0).toString();

    query.prepare("insert into salaires (id_em,salaire,nb_heures,disc) values (:id,500,0,1)");
    query.bindValue(":id",id);
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

void Employes::Calculer_salaire()
{
    QSqlQuery qry,qryy;
    int id,salaire,nh,ne,disc,prime;
    float var=0;
    qry.prepare("select id,salaire,nb_heures,disc,nb_events,prime from salaires,bénévoles where salaires.id = bénévoles.id_e");
    if(qry.exec())
    {
        while(qry.next())
        {
            id=qry.value(0).toInt();
            salaire=qry.value(1).toInt();
            nh=qry.value(2).toInt();
            disc=qry.value(3).toInt();
            ne=qry.value(4).toInt();
            prime=qry.value(5).toInt();
            var = (((nh/10)*0.5) + (ne*0.5) + disc);
            prime = (salaire * var)/100;
            qDebug() << "id: " << id << " | salaire: " << salaire << " | nb heures: " << nh << " | disc : " << disc <<" | nb events: " << ne << " | prime:  " << prime << " | var:  " << var ;
            qryy.prepare("update salaires set prime=:pr where id=:id");
            qryy.bindValue(":pr",prime);
            qryy.bindValue(":id",id);
            qryy.exec();
        }
    }
}
QSqlQueryModel *Employes::Afficher_Salaire()
{

    QSqlQueryModel *modal=new QSqlQueryModel();
    modal->setQuery("select id_em,nom,prénom,nb_heures,nb_events,disc,salaire,prime from salaires,employes,bénévoles where salaires.id = employes.id_em and salaires.id = bénévoles.id_e");
    modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    return modal;
}

bool Employes::Modifier_Salaire(int id,int salaire,int nh,int disc)
{
    QSqlQuery query;
    query.prepare("update salaires set salaire=:s,nb_heures=:nh,disc=:disc where id=:id");
    query.bindValue(":id",id);
    query.bindValue(":s",salaire);
    query.bindValue(":nh",nh);
    query.bindValue(":disc",disc);
    return query.exec();
}



