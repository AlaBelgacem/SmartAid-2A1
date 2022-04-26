#ifndef DONNER_H
#define DONNER_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include "connection.h"
#include <QSqlQuery>
#include <QTableView>
#include <QSystemTrayIcon>
#include <QDebug>

class donner
{
private:
    int id_ne,id_don,quantite;
    float montant;


public:
    donner();
    donner(int,int,int,float);


    bool ajouter ();
   /* QSqlQueryModel * afficher();
    bool supprimer(int);*/
};

#endif // DONNER_H
