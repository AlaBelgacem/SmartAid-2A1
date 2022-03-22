#include "users.h"

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

 int users::Envoyer_sms(QString num)
 {
     QSqlQuery query;
     query.prepare("select telephone from recovery where telephone=:num");
     query.bindValue(":num",num);
     query.exec();
     query.next();
     if(query.value(0).toString()=="")
     {
         srand( time(NULL) );
         int number = rand() % 100000;
         query.prepare("insert into recovery (telephone,token) values (:tel,:tok)");
         query.bindValue(":tel",num);
         query.bindValue(":tok",number);
         query.exec();
         QString token = QString::number(number);
          QProcess::startDetached("C:\\cygwin64\\bin\\mintty.exe", QStringList() << "/home/louay/sms.sh" << num << token );
         return 0 ;
     }
     else return 1 ;
 }
  int users::check_token(users u,QString tok)
  {
      QSqlQuery query;
      QString num = u.em.getTelephone();
      query.prepare("select token from recovery where telephone=:num and token=:tok");
      query.bindValue(":num",num);
      query.bindValue(":tok",tok);
      query.exec();
      query.next();
      if(query.value(0).toString()=="")
          return 0;
      else
      {   query.prepare("delete from recovery where token=:tok");
          query.bindValue(":tok",tok);
          query.exec();
          return 1;
      }
  }

  bool users::Maj_pass(users u, QString pass)
  {
      QSqlQuery query;
      QString num = u.em.getTelephone();
      query.prepare("select id_em from employes where téléphone=:num");
      query.bindValue(":num",num);
      query.exec();
      query.next();
      u.em.setID_em(query.value(0).toInt());

      query.prepare("update users set mot_de_pass=:pass where id_em=:id");
      query.bindValue(":pass",pass);
      query.bindValue(":id",u.em.getID_em());
      return query.exec();


  }

