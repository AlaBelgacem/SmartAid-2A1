#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include "necessiteux.h"
#include <QListView>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     ui->tableN->setModel(N.afficher());
     ui->telephoneN->setValidator(new QIntValidator (0,99999999,this));
     ui->id_Necessiteux->setValidator(new QIntValidator (0,99999999,this));
     ui->emailN->setValidator(new QRegExpValidator(  QRegExp("[a-z]{1,20}@[a-z]{1,8}.[a-z]{1,8}")));
     ui->nomN->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
     ui->prenomN->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));


    QPixmap pix(":/images/images/copy.jpg");
    //ui->user_pic->setPixmap(pix.scaled(501,451,Qt::KeepAspectRatio));
    // Load animated GIF

    QLabel label;
    QMovie *user_pic = new QMovie(":/images/images/646-walking-walkcycle-person-outline.gif");
    QMovie *gif_necessiteux = new QMovie(":/images/images/20-love-heart-flat.gif");

    ui->user_pic->setMovie(user_pic);
    ui->gif_necessiteux->setMovie(gif_necessiteux);
    user_pic->start();
    gif_necessiteux->start();
//SIDE MENU
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



    //MENU AJOUTER/AFFICHER...
    /*QListWidgetItem *afficher= new QListWidgetItem(QIcon(":/icons/icons/identity-card.png"),"Profil");

    ui->listWidget->addItem(afficher);

    QListWidgetItem *ajouter= new QListWidgetItem(QIcon(":/icons/icons/employe128.png"),"Gestion Employés");
    ui->listWidget->addItem(ajouter);

    QListWidgetItem *supprimer= new QListWidgetItem(QIcon(":/icons/icons/don128.png"),"Gestion Dons");
    ui->listWidget->addItem(supprimer);*/





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

void MainWindow::on_ajouterNecessiteux_clicked()
{

    int id = ui->id_Necessiteux->text().toInt();
    QString nom = ui->nomN->text();
    QString prenom = ui->prenomN->text();
    QString email = ui->emailN->text();
    QString telephone = ui->telephoneN->text();
    QString adresse = ui->adresseN->text();
    QString date_naissance = ui->dateNecessiteux->date().toString("ddd MMM M yyyy");
    //QString date_naissance = ui->calendarWidget->selectedDate().toString("dd/mm/yy");
    QString besoin = ui->besoinN->text();


    necessiteux N(id,nom,prenom,email,telephone,adresse,date_naissance,besoin);



    if(nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || telephone.isEmpty() || adresse.isEmpty() ||
            date_naissance.isEmpty() || besoin.isEmpty()){
        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides."),QMessageBox::Cancel);

    }
    else{
        /*QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectué\n"
                                 "Click cancel to exit."),QMessageBox::Cancel);*/
        //refresh

        N.ajouterNecessiteux();
        ui->tableN->setModel(N.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                 "Click cancel to exit."),QMessageBox::Cancel);
        ui->id_Necessiteux->clear();
        ui->nomN->clear();
        ui->prenomN->clear();
        ui->emailN->clear();
        ui->telephoneN->clear();
        ui->adresseN->clear();
        ui->dateNecessiteux->clear();
        ui->besoinN->clear();



    }
}

void MainWindow::on_tableN_activated(const QModelIndex &index)
{
    QString value=ui->tableN->model()->data(index).toString();
         connection c;
         c.closeconnection();
         QSqlQuery qry;

         qry.prepare("select * from NÉCESSITEUX where ID_NE='"+value+"'");
         if(qry.exec())
         {
             while(qry.next()){
                ui->id_Necessiteux->setText(qry.value(0).toString());
             ui->nomN->setText(qry.value(1).toString());
              ui->prenomN->setText(qry.value(2).toString());
              ui->emailN->setText(qry.value(3).toString());
              ui->telephoneN->setText(qry.value(4).toString());
              ui->adresseN->setText(qry.value(5).toString());
             // ui->dateNecessiteux->setText(qry.value(2).toString());
              QString dates =qry.value(6).toString();
              QDate date = QDate::fromString(dates,"ddd MMM M yyyy");
                ui->dateNecessiteux->setDate(date);
              ui->besoinN->setText(qry.value(7).toString());


             }

         }
}

void MainWindow::on_supprimerNecessiteux_clicked()
{
    int id = ui->id_Necessiteux->text().toInt();
    bool test =N.supprimer(id);

    if(test){
        ui->tableN->setModel(N.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
        ui->id_Necessiteux->clear();
        ui->nomN->clear();
        ui->prenomN->clear();
        ui->emailN->clear();
        ui->telephoneN->clear();
        ui->adresseN->clear();
        ui->dateNecessiteux->clear();
        ui->besoinN->clear();
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Suppression non effectuée\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_modifier_Necessiteux_clicked()
{
    int id = ui->id_Necessiteux->text().toInt();
    QString nom = ui->nomN->text();
    QString prenom = ui->prenomN->text();
    QString email = ui->emailN->text();
    QString telephone = ui->telephoneN->text();
    QString adresse = ui->adresseN->text();
    QString date_naissance = ui->dateNecessiteux->date().toString();
    QString besoin = ui->besoinN->text();

    necessiteux N1(id,nom,prenom,email,telephone,adresse,date_naissance,besoin);

    bool test = N1.modifier(id);

    if(test){
        ui->tableN->setModel(N.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
        ui->id_Necessiteux->clear();
        ui->nomN->clear();
        ui->prenomN->clear();
        ui->emailN->clear();
        ui->telephoneN->clear();
        ui->adresseN->clear();
        ui->dateNecessiteux->clear();
        ui->besoinN->clear();
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Modification non effectuée\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QString search=ui->lineEdit->text();
        ui->tableN->setModel(N.rechercher(search));
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString search=ui->lineEdit->text();
        ui->tableN->setModel(N.rechercher(search));
}
