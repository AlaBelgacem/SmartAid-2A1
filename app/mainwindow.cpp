#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "crises.h"
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent) :
      QMainWindow(parent),
      ui(new Ui::MainWindow)
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

    ui->tableView->setModel(Cr.afficher());
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

    QString nom=ui->lineEdit_nom->text();
    QString adresse=ui->lineEdit_Adresse->toPlainText();
    QString description=ui->lineEdit_description->toPlainText();
    int niveau=ui->comboBox_niveau->currentText().toInt();
    QString date_cr=ui->dateEdit_datec->date().toString("dd/MM/yyyy");
    QString etat;
    if (ui->radioButton->isChecked())
    {
        etat="Traiter";
    }
    else if (ui->radioButton_2->isChecked())
    {
        etat="En cours";
    }
    else
    {
        etat="Non traiter";
    }

    Crises C(nom,adresse,niveau,description,date_cr,etat);


    if(nom.isEmpty() || adresse.isEmpty() || description.isEmpty()|| date_cr.isEmpty() || etat.isEmpty())
    {
    QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides"),QMessageBox::Cancel);
    }
   else {
        C.ajouter();
        //refresh
        ui->tableView->setModel(Cr.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

        ui->lineEdit_nom->clear();
        ui->lineEdit_Adresse->clear();
        ui->lineEdit_description->clear();
        ui->dateEdit_datec->clear();
    }

}


void MainWindow::on_pushButton_supp_clicked()
{
     int id=ui->lineEdit_ID_mod->text().toInt();
     bool test=Cr.supprimer(id);
     //qDebug()<< id ;
     if(test)
     {
         //refresh
         ui->tableView->setModel(Cr.afficher());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                 QObject::tr("Suppression effectuée\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);


         ui->lineEdit_ID_mod->clear();
         ui->lineEdit_nom_mod->clear();
         ui->lineEdit_Adresse_mod->clear();
         ui->lineEdit_description_mod->clear();
         ui->dateEdit_datec_mod->clear();
         ui->lineEdit_etat->clear();

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Suppression non effectuée.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_pushButton_modif_clicked()
{
    //qDebug()<< id ;
    int id=ui->lineEdit_ID_mod->text().toInt();
    QString nom=ui->lineEdit_nom_mod->text();
    QString adresse=ui->lineEdit_Adresse_mod->toPlainText();
    QString description=ui->lineEdit_description_mod->toPlainText();
    int niveau=ui->comboBox_niveau_mod->currentText().toInt();
    QString date_cr=ui->dateEdit_datec_mod->date().toString("dd/MM/yyyy");
    QString etat=ui->lineEdit_etat->text();


   bool test =Cr.modifier(id,nom,adresse,niveau,description,date_cr,etat);

    if(test)
    {

        //refresh
        ui->tableView->setModel(Cr.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
        QObject::tr("update effectué\n"
                    "Click to Cancel."),
                                 QMessageBox::Cancel);

        ui->lineEdit_ID_mod->clear();
        ui->lineEdit_nom_mod->clear();
        ui->lineEdit_Adresse_mod->clear();
        ui->lineEdit_description_mod->clear();
        ui->dateEdit_datec_mod->clear();
        ui->lineEdit_etat->clear();


    }
    else         QMessageBox::critical  (nullptr, QObject::tr("not OK"),
                 QObject::tr("update non effectué\n"
                             "Click to Cancel."), QMessageBox::Cancel);
}


void MainWindow::on_lineEditRecherche_textChanged(const QString &arg1)
{
    QString str=ui->lineEditRecherche->text();
    ui->tableView->setModel(Cr.rechercher(str));
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
     QString value=ui->tableView->model()->data(index).toString();
             connection c;
             c.closeConnection();
             QSqlQuery qry;

             qry.prepare("select * from crises where ID_CR='"+value+"'");
             if(qry.exec())
             {
                 while(qry.next()){
                    ui->lineEdit_ID_mod->setText(qry.value(0).toString());
                    ui->lineEdit_nom_mod->setText(qry.value(1).toString());
                    ui->lineEdit_Adresse_mod->setPlainText(qry.value(2).toString());
                    ui->comboBox_niveau_mod->setCurrentText(qry.value(3).toString());
                    ui->lineEdit_description_mod->setPlainText(qry.value(4).toString());
                    QString dates =qry.value(5).toString();
                    QDate date = QDate::fromString(dates,"dd/MM/yyyy");
                    ui->dateEdit_datec_mod->setDate(date);
                    ui->lineEdit_etat->setText(qry.value(6).toString());


                 }

             }
}



void MainWindow::on_radioButton_4_clicked()
{
    QString croissance=ui->radioButton_4->text();
    ui->tableView->setModel(Cr.trierC(croissance));
}

void MainWindow::on_radioButton_5_clicked()
{
    QString croissance=ui->radioButton_5->text();
    ui->tableView->setModel(Cr.trierD(croissance));
}
