#include "mainwindow.h"
#include<QMessageBox>
#include "ui_mainwindow.h"
#include"evenements.h"
#include "connection.h"
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
      ui->setupUi(this);

    QPixmap pix(":/images/images/copy.jpg");
    //ui->user_pic->setPixmap(pix.scaled(501,451,Qt::KeepAspectRatio));
    // Load animated GIF

    QLabel label;
    QMovie *movie = new QMovie(":/images/images/646-walking-walkcycle-person-outline.gif");

    ui->user_pic->setMovie(movie);
    movie->start();

    QListWidgetItem *item0= new QListWidgetItem(QIcon(":/icons/icons/identity-card.png"),"Profil");
    ui->listWidget->addItem(item0);

    QListWidgetItem *item= new QListWidgetItem(QIcon(":/icons/icons/employe128.png"),"Gestion Employés");
    ui->listWidget->addItem(item);

    QListWidgetItem *item4= new QListWidgetItem(QIcon(":/icons/icons/don128.png"),"Gestion Dons");
    ui->listWidget->addItem(item4);

    QListWidgetItem *item5= new QListWidgetItem(QIcon(":/icons/icons/evenement128.png"),"Gestion Evenements");
    ui->listWidget->addItem(item5);


    QListWidgetItem *item2= new QListWidgetItem(QIcon(":/icons/icons/necessiteux128.png"),"Gestion Nécessiteux");
    ui->listWidget->addItem(item2);

    QListWidgetItem *item3= new QListWidgetItem(QIcon(":/icons/icons/crises128.png"),"Gestion Crises");
    ui->listWidget->addItem(item3);

    QListWidgetItem *item6= new QListWidgetItem(QIcon(":/icons/icons/benevoles128.png"),"Gestion Bénévoles");
    ui->listWidget->addItem(item6);


    ui->listWidget->setCurrentItem(item0);
    Connection c;
        QSqlQueryModel *modal=new QSqlQueryModel();
        c.createconnect();
        QSqlQuery *query=new QSqlQuery(c.getDB());
        query->prepare("select * from evenements");
        query->exec();
        modal->setQuery(*query);
        ui->tableView->setModel(modal);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString selectedvalue= ui->listWidget->currentItem()->text();

    if (selectedvalue == "Profil"){
        ui->stackedWidget->setCurrentIndex(0);
    }
    if (selectedvalue == "Gestion Employés"){
        ui->stackedWidget->setCurrentIndex(1);
    }
    if (selectedvalue == "Gestion Dons"){
        ui->stackedWidget->setCurrentIndex(2);
    }
    if (selectedvalue == "Gestion Evenements"){
        ui->stackedWidget->setCurrentIndex(3);
    }
    if (selectedvalue == "Gestion Nécessiteux"){
        ui->stackedWidget->setCurrentIndex(4);
    }
    if (selectedvalue == "Gestion Crises"){
        ui->stackedWidget->setCurrentIndex(5);
    }
    if (selectedvalue == "Gestion Bénévoles"){
        ui->stackedWidget->setCurrentIndex(6);
    }

}

void MainWindow::on_pushButton_clicked()
{


}

void MainWindow::on_Ajouter_event_3_clicked()
{
    Connection c;
        QSqlQueryModel *modal=new QSqlQueryModel();
        c.createconnect();
        QSqlQuery *query=new QSqlQuery(c.getDB());
        query->prepare("select * from evenements");
        query->exec();
        modal->setQuery(*query);
        ui->tableView->setModel(modal);
}

void MainWindow::on_Ajouter_event_clicked()
{
    Evenements Event;

        Event.setNom(ui->Nom->text());
        Event.settype(ui->Type->text());
        Event.setdate_deb(ui->Date->text());
        Event.setville(ui->Ville->text());
        Event.setCode_postal(ui->Code_Postal->value());
        Event.setdescription(ui->Description->toPlainText());
        bool resultat=Event.ajouter();
        if (resultat==true)
            QMessageBox::information(this,"Ajout Event","Ajout Effectué Avec Sucess.");
        else
            QMessageBox::information(this,"Ajout Event","Echec De L'ajout.");
}

void MainWindow::on_Ajouter_event_2_clicked()
{
Evenements e;
e.setId_event(ui->line_id->text().toInt());
e.setNom(ui->Nom_2->text());
e.settype(ui->Type_2->text());
e.setville(ui->Ville_2->text());
e.setdate_deb(ui->Date_2->text());
e.setdescription(ui->Description_2->toPlainText());
e.setCode_postal(ui->Code_Postal_2->text().toInt());
 bool resultat=e.Modifier();
 if (resultat==true)
     QMessageBox::information(this,"Modifie Event","Modification Effectué Avec Sucess.");
 else
     QMessageBox::information(this,"Modifie Event","Echec De La Modification.");

}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString value=ui->tableView->model()->data(index).toString();
         Connection c;
         c.closeconnection();
         QSqlQuery qry;

         qry.prepare("select * from evenements where id_ev='"+value+"'");
         if(qry.exec())
         {
             while(qry.next()){
                  ui->line_id->setText(qry.value(0).toString());
                ui->Nom_2->setText(qry.value(1).toString());
             ui->Type_2->setText(qry.value(4).toString());
              ui->Date_2->setText(qry.value(5).toString());
              ui->Ville_2->setText(qry.value(2).toString());
              ui->Code_Postal_2->setValue(qry.value(6).toInt());
               ui->Description_2->setText(qry.value(3).toString());

             }}
}

void MainWindow::on_Ajouter_event_4_clicked()
{
    Evenements Event;

        Event.setId_event(ui->line_id->text().toInt());
        bool resultat=Event.supprimer();
        if (resultat==true)
            QMessageBox::information(this,"Supprimer Event","Suppression Effectué Avec Sucess.");
        else
            QMessageBox::information(this,"Supprimer Event","Echec De La Suppression.");

}
