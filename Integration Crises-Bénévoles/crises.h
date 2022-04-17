#ifndef CRISES_H
#define CRISES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include "connection.h"

class Crises
{
    QString nom, description, adresse, etat, date_cr,latitude,longitude;
    int id, niveau ;

public:

    //Constructeurs pour allouer la mémoire nécessaire aux attributs
    Crises(){};
    Crises ( QString,QString,int,QString,QString , QString, QString, QString );

    //Getters
    QString getNom() {return nom;}
    QString getDescription() {return description;}
    QString getAdresse() {return adresse;}
    QString getEtat() {return etat;}
    QString getDate() {return date_cr;}
    int getID() {return id;}
    int getNiveau() {return niveau;}
    QString getLa() {return latitude;}
    QString getLo() {return longitude;}
    //Setters
    void setNom(QString n) {nom=n;}
    void setDescription(QString desc) { description=desc;}
    void setAdresse(QString a) {adresse=a;}
    void setLa(QString la) {latitude=la;}
    void setLo(QString lo) {longitude=lo;}
    void setEtat(QString e) {etat=e;}
    void setDate(QString d) {date_cr=d;}
    void setID(int id) {this->id=id;}  //this pour differencier le paramétre de l'attribut
    void setNiveau(int n) {this->niveau=n;}

    //Fonctionnalités de base relatives à l'entité crise
    bool ajouter();
    QSqlQueryModel * afficher(); //La classe QSqlQueryModel fournit un modèle de données en lecture seule pour les ensembles de résultats SQL.
    bool supprimer (int);
    bool modifier (int, QString,QString, int ,QString ,  QString ,QString, QString, QString);

    //Fonctionnalités avancée relatives à l'entité crise
    QSqlQueryModel *rechercher(const QString &);    //La classe QSqlQueryModel fournit un modèle de données en lecture seule pour les ensembles de résultats SQL.
    QSqlQueryModel *trierC(QString );               //La classe QSqlQueryModel fournit un modèle de données en lecture seule pour les ensembles de résultats SQL.
    QSqlQueryModel *trierD(QString );               //La classe QSqlQueryModel fournit un modèle de données en lecture seule pour les ensembles de résultats SQL.
    void stat(QString *x1,QString *x2,QString *x3); //statistiques
    float etatT(); //pourcentage statistiques lorsque etat est traiter
    float etatEC(); //pourcentage statistiques lorsque etat est en cours
    float etatNT(); //pourcentage statistiques lorsque etat est non traiter

  };

#endif // CRISES_H
