#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"employes.h"
#include"users.h"
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include<QMessageBox>
#include <QRegExpValidator>
#include <QPainter>
#include <QPdfWriter>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QLineEdit>
#include "windows.h"
#include <QTimer>
#include "crises.h"
#include "piechart.h"
#include "arduino.h"
#include <QQmlEngine>
#include <QQuickItem>
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include "donner.h"




void MainWindow::on_ajouter_donner_clicked()
{
    int id_ne=ui->id_donner1->text().toInt();
    int id_don=ui->id_donner2->text().toInt();

    int quantite=ui->quantite_donner->text().toInt();

    float montant=ui->montant_donner->text().toFloat();



    donner D(id_ne,id_don,quantite,montant);
    bool test=D.ajouter();

    if(test){
        ui->tableView_3->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
        ui->id_donner1->clear();
        ui->id_donner2->clear();
        ui->quantite_donner->clear();
        ui->montant_donner->clear();
    }
}
