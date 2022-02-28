#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"employes.h"
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include<QMessageBox>

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
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

  /*  connection c;
    QSqlQueryModel *modal=new QSqlQueryModel();

    bool test=c.createconnection();
    if(test)
        ui->conect->setText("Connection: Connecté");
    else
         ui->conect->setText("Connection: Connection échoué");

    QSqlQuery *qry=new QSqlQuery(c.getdb());

    qry->prepare("select * from employes");

    qry->exec();

    modal->setQuery(*qry);*/
    //--------------------------------------------
    //Afficher les Employe dés que le programe commence
    connection c;

    bool test = c.createconnection();
    if (test)
    ui->conect->setText("Connection: Connecté ✓");
    else
         ui->conect->setText("Connection: Echoué X");

    Employes e;

    ui->table2->setModel(e.Afficher_em());

    ui->table1->setModel(e.Afficher_em());
     //--------------------------------------------
}

//la liste en gauche
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

//-----------------------------------------------------------------
//Bouton Ajouter
void MainWindow::on_Ajouter_clicked()
{
//recuperer donnes
    Employes e(NULL,ui->lineEdit_nom->text(),ui->lineEdit_pre->text(),ui->dateEdit_date->date().toString(),ui->lineEdit_em->text(),ui->lineEdit_ad->text(),ui->lineEdit_tele->text().toInt(),ui->lineEdit_image->text());

    bool check=e.Ajouter_em();
    if(check)
    {
        //Afficher apres l'insertion
         ui->table1->setModel(e.Afficher_em());
         ui->table2->setModel(e.Afficher_em());
         clear();
        QMessageBox::information(nullptr,QObject::tr("Insertion"),
            QObject::tr("inserer avec succes."),QMessageBox::Cancel);
    }
else {
        QMessageBox::information(nullptr,QObject::tr("Insertion"),
            QObject::tr("insertion echoué."),QMessageBox::Cancel);
    }


}

//Bouton Modifier
void MainWindow::on_Modifier_clicked()
{
    //recuperer donnes
    Employes e( ui->lineEdit_id->text().toInt(),ui->lineEdit_nom->text(),ui->lineEdit_pre->text(),ui->dateEdit_date->date().toString(),ui->lineEdit_em->text(),ui->lineEdit_ad->text(),ui->lineEdit_tele->text().toInt(),ui->lineEdit_image->text());
    bool check=e.Modifier_em();
    if(check)
    {
        ui->table1->setModel(e.Afficher_em());
        ui->table2->setModel(e.Afficher_em());
        clear();
        QMessageBox::information(nullptr,QObject::tr("Modification"),
            QObject::tr("Modification avec succes."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr,QObject::tr("Modification"),
            QObject::tr("Modification echoué."),QMessageBox::Cancel);
    }
}

//Bouton Supprimer
void MainWindow::on_Supprimer_clicked()
{
    Employes e;
    e.setID_em(ui->lineEdit_id->text().toInt());
    bool check=e.Supprimer_em();
    if(check)
    {
         ui->table1->setModel(e.Afficher_em());
         ui->table2->setModel(e.Afficher_em());
         clear();
        QMessageBox::information(nullptr,QObject::tr("Suppression"),
            QObject::tr("Suppression avec succes."),QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::information(nullptr,QObject::tr("Suppression"),
            QObject::tr("Suppression echoué."),QMessageBox::Cancel);
    }

}

//Selectioner a partir du champ ID
void MainWindow::on_table1_activated(const QModelIndex &index)
{
    QString value=ui->table1->model()->data(index).toString();
    connection c;
    c.closeconnection();
    QSqlQuery qry;

     qry.prepare("select * from employes where id_em='"+value+"'");
     if(qry.exec())
     {
          while(qry.next()){
          ui->lineEdit_id->setText(qry.value(0).toString());
          ui->lineEdit_nom->setText(qry.value(1).toString());
          ui->lineEdit_pre->setText(qry.value(2).toString());
          QString dates =qry.value(3).toString();
          //QDate date= QDate::currentDate();
          //QString date_string_on_db = "20/12/2015";
          //QDate Date = QDate::fromString(date_string_on_db,"dd/MM/yyyy");
          QDate date = QDate::fromString(dates,"ddd MMM M yyyy");
          ui->dateEdit_date->setDate(date);
          ui->lineEdit_ad->setText(qry.value(5).toString());
          ui->lineEdit_tele->setText(qry.value(4).toString());
          ui->lineEdit_em->setText(qry.value(6).toString());
          ui->lineEdit_image->setText(qry.value(8).toString());
          QPixmap pix(qry.value(8).toString());
          ui->label_pic->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));

         }
     }
}
//Bouton Actualiser
void MainWindow::on_Actualiser_clicked()
{
    Employes e;
    ui->table1->setModel(e.Afficher_em());
}

//Vidde les champs aprés les CRUD
void MainWindow::clear()
{
    ui->lineEdit_id->clear();
    ui->lineEdit_nom->clear();
    ui->lineEdit_pre->clear();
    ui->dateEdit_date->clear();
    ui->lineEdit_ad->clear();
    ui->lineEdit_tele->clear();
    ui->lineEdit_em->clear();
    ui->lineEdit_image->clear();
    ui->label_pic->clear();
}
//-----------------------------------------------------------------

//Initialiser le tab de recherche
void MainWindow::on_rechercher_returnPressed()
{
    QString value=ui->rechercher->text();
    Employes e;
    if(value!=NULL) ui->table2->setModel(e.Rechercher_em(value));
    else  ui->table2->setModel(e.Afficher_em());
}

//choisir critere de tri
void MainWindow::on_comboBox_highlighted(const QString &arg1)
{
    Employes e;
    QString type="";

    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(arg1 != "Choisir")
         ui->table2->setModel(e.Trier_em(type,arg1));

    else  ui->table2->setModel(e.Afficher_em());

}

//choisir radio button ascendant
void MainWindow::on_radioButton_clicked()
{
    Employes e;
    QString type="";

    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(ui->comboBox->currentText() != "Choisir")
         ui->table2->setModel(e.Trier_em(type,ui->comboBox->currentText()));

    else  ui->table2->setModel(e.Afficher_em());
}


//choisir radio button descendant
void MainWindow::on_radioButton_2_clicked()
{
    Employes e;
    QString type="";

    if(ui->radioButton->isChecked())
        type="ASC";
    else if(ui->radioButton_2->isChecked())
        type="DESC";

    if(ui->comboBox->currentText() != "Choisir")
         ui->table2->setModel(e.Trier_em(type,ui->comboBox->currentText()));

    else  ui->table2->setModel(e.Afficher_em());
}
