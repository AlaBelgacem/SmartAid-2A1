#ifndef CRISES_H
#define CRISES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include "connection.h"

class Crises
{
    QString nom, description, adresse, etat ;
    QDate date_cr;
    int id, niveau ;

public:

    //Constructeurs
    Crises(){};
    Crises ( QString,QString,int,QString,QDate , QString );

    //Getters
    QString getNom() {return nom;}
    QString getDescription() {return description;}
    QString getAdresse() {return adresse;}
    QString getEtat() {return etat;}
    QDate getDate() {return date_cr;}
    int getID() {return id;}
    int getNiveau() {return niveau;}

    //Setters
    void setNom(QString n) {nom=n;}
    void setDescription(QString desc) { description=desc;}
    void setAdresse(QString a) {adresse=a;}
    void setEtat(QString e) {etat=e;}
    void setDate(QDate d) {date_cr=d;}
    void setID(int id) {this->id=id;}
    void setNiveau(int n) {this->niveau=n;}

    //Fonctionnalités de base relatives à l'entité crise
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer (int);
    bool modifier (int, QString,QString, int ,QString ,  QDate ,QString);
  };

#endif // CRISES_H
