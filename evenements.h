#ifndef EVENEMENTS_H
#define EVENEMENTS_H
#include <QString>
#include<QtSql/QSqlQuery>
#include<QtSql/QSqlQueryModel>

class Evenements
{
private:
    int id_event,code_postal;
    QString nom,description,ville,date_deb,type;

public:
 //Constructeurs
    Evenements(){}
    Evenements(int id_event,int code_postal,QString nom,QString description,QString ville,QString date_deb,QString type);
//Getters
    int getId_event(){return id_event;}
    int getCode_postal(){return code_postal;}
    QString getNom(){return nom;}
    QString getdescription(){return description;}
    QString getville(){return ville;}
    QString getdate_deb(){return date_deb;}
    QString gettype(){return type;}
//Setters
    void setId_event(int id){id_event=id;}
    void setCode_postal(int cp){code_postal=cp;}
    void setNom(QString name){nom=name;}
    void setdescription(QString desc){description=desc;}
    void setville(QString vi){ville=vi;}
    void setdate_deb(QString date){date_deb=date;}
    void settype(QString ty){type=ty;}
    //Fonctions CRUD
    bool ajouter();
    bool Modifier();
    bool supprimer ();
};

#endif // EVENEMENTS_H
