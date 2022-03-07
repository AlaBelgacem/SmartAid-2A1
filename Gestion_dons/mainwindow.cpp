#include "mainwindow.h"
#include "dons.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include <QMessageBox>
#include "connection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());

    ui->lineEdit_id->setValidator(new QIntValidator (0,99999999,this));
    ui->lineEdit_mt->setValidator(new QDoubleValidator(0.0, 99999999.99999999, 5,this));
    ui->lineEdit_qut->setValidator(new QIntValidator (0,99999999,this));
    ui->lineEdit_id_8->setValidator(new QIntValidator (0,99999999,this));
    ui->lineEdit_mt_8->setValidator(new QDoubleValidator(0.0, 99999999.99999999, 5,this));
    ui->lineEdit_qut_8->setValidator(new QIntValidator (0,99999999,this));

    QPixmap pix(":/images/images/copy.jpg");
    //ui->user_pic->setPixmap(pix.scaled(501,451,Qt::KeepAspectRatio));
    // Load animated GIF

    QLabel label;
    QMovie *movie = new QMovie(":/images/images/646-walking-walkcycle-person-outline.gif");
    QMovie *gif_don = new QMovie(":/images/images/add don.gif");
    ui->user_pic->setMovie(movie);
    ui->gif_don->setMovie(gif_don);
    movie->start();
    gif_don->start();

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
    ui->tableView->setModel(Etmp.afficher());
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


void MainWindow::on_pushButton_ajouter_clicked()
{
//Recuperration des informations saisies dans les 3 champs

    int id=ui->lineEdit_id->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString description=ui->lineEdit_description->text();
    QString montant=ui->lineEdit_mt->text();
    int quantite=ui->lineEdit_qut->text().toInt();



    Dons D(id,nom,description,montant,quantite);
    bool test=D.ajouter();


    if(nom.isEmpty() || description.isEmpty() || id==NULL ){
        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides (ID,Nom ou Description)."),QMessageBox::Cancel);

    }
    else if(test)
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
        ui->lineEdit_id->clear();
        ui->lineEdit_nom->clear();
        ui->lineEdit_description->clear();
        ui->lineEdit_mt->clear();
        ui->lineEdit_qut->clear();
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                             QObject::tr("Ajout non effectué.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
}





void MainWindow::on_pushButton_supprimer_clicked()
{
    int id=ui->lineEdit_id_8->text().toInt();
        bool test=Etmp.supprimer(id);

        if(id==NULL ){
            QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides (ID,Nom ou Description)."),QMessageBox::Cancel);

        }
        else if (test)
        {
            ui->tableView->setModel(Etmp.afficher());
            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject ::tr("suppression effectuée \n"
                                                  "click cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_id_8->clear();
            ui->lineEdit_nom_8->clear();
            ui->lineEdit_description_8->clear();
            ui->lineEdit_mt_8->clear();
            ui->lineEdit_qut_8->clear();

        }
        else
            QMessageBox::critical(nullptr, QObject :: tr ("Not OK"),
                                  QObject ::tr("suppression non effectuée.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);


}


void MainWindow::on_pushButton_modifier_clicked()
{
    int id=ui->lineEdit_id_8->text().toInt();
    QString nom=ui->lineEdit_nom_8->text();
    QString description=ui->lineEdit_description_8->text();
    QString montant=ui->lineEdit_mt_8->text();
    int quantite=ui->lineEdit_qut_8->text().toInt();

    bool test = Etmp.modifier(id,nom,description,montant,quantite);

    if (test)
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject ::tr("modification effectuée \n"
                                              "click cancel to exit."), QMessageBox::Cancel);
                 ui->lineEdit_id_8->clear();
                 ui->lineEdit_nom_8->clear();
                 ui->lineEdit_description_8->clear();
                 ui->lineEdit_mt_8->clear();
                 ui->lineEdit_qut_8->clear();


    }
    else
        QMessageBox::critical(nullptr, QObject :: tr ("Not OK"),
                              QObject ::tr("modification non effectuée.\n"
                                      "click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString value=ui->tableView->model()->data(index).toString();
                 connection c;
                 c.closeconnection();
                 QSqlQuery qry;

                 qry.prepare("select ID_DON , NOM_DON, DESCRIPTION_DON ,MONTANT_DON ,QUANTITE_DON   from DONS  where ID_DON='"+value+"'");
                 if(qry.exec())
                 {
                     while(qry.next()){
                        ui->lineEdit_id_8->setText(qry.value(0).toString());
                        ui->lineEdit_nom_8->setText(qry.value(1).toString());
                        ui->lineEdit_description_8->setText(qry.value(2).toString());
                        ui->lineEdit_mt_8->setText(qry.value(3).toString());
                        ui->lineEdit_qut_8->setText(qry.value(4).toString());

                     }

                 }
}
