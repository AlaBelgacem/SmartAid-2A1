#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"connection.h"
#include"benevoles.h"
#include<QMessageBox>
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

void MainWindow::on_pushButton_5_clicked()
{
    benevoles b;
    b.setNom(ui->nom->text());
    b.setPrenom(ui->prenom->text());
    b.setDateNaissance(ui->daten->text());
    b.setEmail(ui->email->text());
    b.setTel(ui->tel->text());
    b.setAdresse(ui->adresse->text());

    bool check=b.ajouter();

    if (check)
    {
        QMessageBox::information(nullptr, QObject::tr("Ajout"),
        QObject::tr("ajout avec succés.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::information(nullptr, QObject::tr("Ajout"),
        QObject::tr("Ajout échoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    Connection c;
        QSqlQueryModel *modal=new QSqlQueryModel();

        QSqlQuery *qry=new QSqlQuery(c.getdb());

        qry->prepare("select * from benevoles");

        qry->exec();

        modal->setQuery(*qry);

        ui->tableView->setModel(modal);
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString value=ui->tableView->model()->data(index).toString();
         Connection c;
         c.closeConnection();
         QSqlQuery qry;

         qry.prepare("select * from benevoles where id_be='"+value+"'");
         if(qry.exec())
         {
             while(qry.next()){
                ui->lineEdit_id->setText(qry.value(0).toString());
             ui->lineEdit_nom->setText(qry.value(1).toString());
              ui->lineEdit_prenom->setText(qry.value(2).toString());
              ui->lineEdit_date->setText(qry.value(3).toString());
              ui->lineEdit_ad->setText(qry.value(4).toString());
              ui->lineEdit_tel->setText(qry.value(5).toString());
              ui->lineEdit_email->setText(qry.value(6).toString());


             }

         }


}

void MainWindow::on_pushButton_4_clicked()
{
    int id=ui->lineEdit_id->text().toInt();
        benevoles e;
        e.setId(id);
        bool check=e.supprimer();
        if(check)
        {
            QMessageBox::information(nullptr,QObject::tr("Suppression"),
                QObject::tr("Suppression avec succes."),QMessageBox::Cancel);
        }
    else {
            QMessageBox::information(nullptr,QObject::tr("Suppression"),
                QObject::tr("Suppression echoué."),QMessageBox::Cancel);
        }


}

void MainWindow::on_pushButton_3_clicked()
{
    benevoles b;
    b.setNom(ui->lineEdit_nom->text());
    b.setPrenom(ui->lineEdit_prenom->text());
    b.setDateNaissance(ui->lineEdit_date->text());
    b.setEmail(ui->lineEdit_email->text());
    b.setTel(ui->lineEdit_tel->text());
    b.setAdresse(ui->lineEdit_ad->text());
    b.setId(ui->lineEdit_id->text().toInt());

    bool check=b.modifier();

    if (check)
    {
        QMessageBox::information(nullptr, QObject::tr("Modification"),
        QObject::tr("Modification avec succés.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::information(nullptr, QObject::tr("Modification"),
        QObject::tr("Modification échoué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}
