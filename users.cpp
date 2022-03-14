#include "users.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

bool users::Ajouter_user(){
    QSqlQuery query;
    query.exec("SELECT MAX( id_em ) FROM employes;");
    query.next();
    QString id=query.value(0).toString();

    query.prepare("insert into users (id_em,email,mot_de_pass) values (:id,:email,:mdp)");
    query.bindValue(":id",id);
    query.bindValue(":email",email);
    query.bindValue(":mdp",mdp);
    return query.exec();
}

bool users::Login(QString e,QString mdp)
{
    QSqlQuery query;
    query.prepare("select id_em from users where email=:email and mot_de_pass=:mdp");
    query.bindValue(":email",e);
    query.bindValue(":mdp",mdp);
    query.exec();
    query.next();
    QString id=query.value(0).toString();
    if(id=="")
        return 0;
    if(id!="")
        return 1;

}
users users::session(QString e,QString mdp)
{
    QSqlQuery query,qry;
    int ide=0;
    QString nom,prenom,tel,ad,d,emm;
    query.prepare("select id_em from users where email=:email and mot_de_pass=:mdp");
    query.bindValue(":email",e);
    query.bindValue(":mdp",mdp);
    query.exec();
    query.next();
    QString id=query.value(0).toString();
    qry.prepare("select * from employes where id_em=:id");
    qry.bindValue(":id",id);
    if(qry.exec())
    {
        while(qry.next())
        {
            //id
            ide=qry.value(0).toInt();
            //nom
            nom=qry.value(1).toString();
            //prenom
            prenom=qry.value(2).toString();
            //email
            emm=qry.value(6).toString();
            //date
            d =qry.value(3).toString();
            //ad
            ad=qry.value(5).toString();
            //tel
            tel=qry.value(4).toString();
        }

    }
    //    Employes(int id,QString nom,QString prenom,QString date,QString email,QString ad,QString telephone,QString im,QString type,QString sexe)
    Employes em(ide,nom,prenom,d,emm,ad,tel,"","","");

    users u(em,e,mdp);
    return u;
}
