#include "evenements.h"

Evenements::Evenements(int id_event,int code_postal,QString nom,QString description,QString ville,QString date_deb,QString type)
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
    QSqlQuery query;

        query.prepare("INSERT INTO EVENEMENTS(NOM,VILLE,TYPE,DATE_DEB,CODE_POSTAL,DESCRIPTION) VALUES (:nom,:ville,:type,:date,:code,:desc)");
        query.bindValue(":nom",nom);
        query.bindValue(":ville",ville);
        query.bindValue(":type",type);
        query.bindValue(":code",code_postal);
        query.bindValue(":date",date_deb);
        query.bindValue(":desc",description);



return query.exec();
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
