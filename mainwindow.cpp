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
#include "PieChart.h"
#include "Arduino.h"
#include <QQmlEngine>
#include <QQuickItem>
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QPdfWriter>
#include <QDir>
#include "smtp.h"


#define chars_rx "[A-Za-z]{3,10}"
#define tel_rx "\\+[0-9]{11}"
#define email_rx "[A-Za-z0-9]{4,15}\\@+[a-z]{4,7}\\.+[a-z]{2,3}"
#define file_rx "[A-z0-9]+(\\.(jpg|png|gif|jpeg|jfif))"
int q=2;
int s=0;
int sms=0;
int coffre=0;
users session;
MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Initialisation du code postal
    ui->Code_Postal_3->setValue(1000);
    ui->Code_Postal_4->setValue(1000);

    QPixmap pix(":/images/images/copy.jpg");
    //ui->user_pic->setPixmap(pix.scaled(501,451,Qt::KeepAspectRatio));
    // Load animated GIF

    QLabel label;
   // QMovie *movie = new QMovie(":/images/images/avatar rose.gif");
    // QMovie *movie2 = new QMovie(":/images/images/id.gif");


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

    //Mise En Date la date d'aujourdh'ui pour le champs date_deb dans ajouter
      QDateTime cdt = QDateTime::currentDateTime();
    ui->Date_4->setDateTime(cdt);

    //Style Du Calendrier
    QTextCharFormat format = ui->calendarWidgett->weekdayTextFormat(Qt::Saturday);
    format.setForeground(QBrush(Qt::black, Qt::SolidPattern));
    ui->calendarWidgett->setWeekdayTextFormat(Qt::Saturday, format);
    ui->calendarWidgett->setWeekdayTextFormat(Qt::Sunday, format);
    ui->calendarWidgett->setWeekdayTextFormat(Qt::Monday, format);
    ui->calendarWidgett->setWeekdayTextFormat(Qt::Tuesday, format);
    ui->calendarWidgett->setWeekdayTextFormat(Qt::Wednesday, format);
    ui->calendarWidgett->setWeekdayTextFormat(Qt::Thursday, format);
    ui->calendarWidgett->setWeekdayTextFormat(Qt::Friday, format);
    ui->calendarWidgett->setStyleSheet("background-color :rgb(255, 167, 167);");

    //ui->lineEdit->hide();
    //controle de saisie en temp reel
    ui->lineEdit_tele->setValidator(new QRegExpValidator( QRegExp(tel_rx),this));
    ui->lineEdit_nom->setValidator(new QRegExpValidator( QRegExp(chars_rx),this));
    ui->lineEdit_pre->setValidator(new QRegExpValidator( QRegExp(chars_rx),this));
    ui->lineEdit_em->setValidator(new QRegExpValidator( QRegExp(email_rx),this));
    ui->lineEdit_image->setValidator(new QRegExpValidator( QRegExp(file_rx),this));

    ui->lineEdit_tele_2->setValidator(new QRegExpValidator( QRegExp(tel_rx),this));
    ui->lineEdit_nom_2->setValidator(new QRegExpValidator( QRegExp(chars_rx),this));
    ui->lineEdit_pre_2->setValidator(new QRegExpValidator( QRegExp(chars_rx),this));
    ui->lineEdit_em_2->setValidator(new QRegExpValidator( QRegExp(email_rx),this));
    ui->lineEdit_image_2->setValidator(new QRegExpValidator( QRegExp(file_rx),this));

    //inti les champs des erreurs
    init_errors();
    init_errors_2();

    //verifi la conection avec db
    connection c;
    bool test = c.createconnection();
    if (test)
        ui->conect->setText("Connecté ✓");
    else
        ui->conect->setText("Echec X");
    //--------------------------------------------
    //Afficher les Employe dés que le programe commence
    Employes e;
    ui->table2->setModel(e.Afficher(3));
    ui->table1->setModel(e.Afficher(1));
    ui->table3->setModel(e.Afficher(2));

    //--------------------------------------------

    //prototype login
    if(q==0)
    {
        ui->stackedWidget->hide();
        ui->listWidget->hide();
        ui->er_log->hide();
    }
    if(q==2)
    {
        ui->stackedWidget->show();
        ui->listWidget->show();
        //ui->box->move(0,-150);
        ui->box->hide();
        ui->er_log->hide();

        ui->table4->setModel(e.Afficher_Salaire(q));
    }
    if(s==0)
    {
        ui->bull_code->hide();
         ui->bull_mdp->hide();
    }
    ui->stat->addWidget(e.stat_gender(), 0, 0);
    ui->stat->addWidget(e.stat_age(), 0, 1);
    ui->stat->addWidget(e.stat_age_gender(), 1, 0);
    ui->stat->addWidget(e.stat_money_age(), 1, 1);

    ui->listWidget->setCurrentItem(item0);
    //Affichage
    ui->tableView->setModel(E.afficher());
    //To Do list
    load();

    ui->listWidget->setCurrentItem(item0);
      ui->tableView->setModel(Etmp.afficher());
      ui->tableView_2->setModel(Cat.afficherC());

      QString noti="";
      Etmp.notification(noti); //appel pour la fonction notification
 ui->tableViewc->setModel(Cr.afficher());
 ui->statlabel->setText(QString::number(Cr.etatT()));
 ui->statlabel_2->setText(QString::number(Cr.etatEC()));
 ui->statlabel_3->setText(QString::number(Cr.etatNT()));

 connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));


 qDebug() << Q_FUNC_INFO;

 QQuickItem *item7 = ui->quickWidget->rootObject();

 QObject *objectMouseArea = item7->findChild<QObject *>("mouseArea");
 if(objectMouseArea != nullptr)
 {
     connect(objectMouseArea, SIGNAL(afficherPosition(QString,QString)), this, SLOT(afficherPosition(QString,QString)));
 }
 QObject *objectGeocodage = item7->findChild<QObject *>("geocodage");
 if(objectGeocodage != nullptr)
 {
     connect(objectGeocodage, SIGNAL(afficherInformations(QString,QString)), this, SLOT(afficherInformations(QString,QString)));
 }


//arduino
    int ret=A.connect_arduino();

        switch (ret) {
        case 0 :
            qDebug()<<"Arduino is available and connected to : "<<A.get_port_name();
            break;

        case 1 :
            qDebug()<<"Arduino is available but not connected to : "<<A.get_port_name();
            break;
        case -1 :
            qDebug()<<"Arduino is not available ";
            break;
        }

        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(test()));



        //// NECESSITEUX ////
        ///
        ///

        ui->tableN->setModel(N.afficher());
        ui->tableRdv->setModel(rdv.afficher());
        ui->customPlot->replot();

        ui->telephoneN->setValidator(new QIntValidator (0,99999999,this));
        ui->id_Necessiteux->setValidator(new QIntValidator (0,99999999,this));
        ui->emailN->setValidator(new QRegExpValidator(  QRegExp("[a-z]{1,20}@[a-z]{1,8}.[a-z]{1,8}")));
        ui->nomN->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));
        ui->prenomN->setValidator(new QRegExpValidator(QRegExp("[A-z]*")));

        /////////////////////////////////////////////////////////// TAB NECE ///////////////////////////////////////////////////
            QListWidgetItem *consulter= new QListWidgetItem(QIcon(":/icons/icons/crises128.png"),"Consulter");
            ui->listWidget_Ne->setFlow(QListWidget::LeftToRight);

            ui->listWidget_Ne->addItem(consulter);

            QListWidgetItem *rdv= new QListWidgetItem(QIcon(":/icons/icons/benevoles128.png"),"Rendez-Vous");
            ui->listWidget_Ne->addItem(rdv);

            QListWidgetItem *stat= new QListWidgetItem(QIcon(":/icons/icons/benevoles128.png"),"QrCode");
            ui->listWidget_Ne->addItem(stat);

            QListWidgetItem *qr= new QListWidgetItem(QIcon(":/icons/icons/benevoles128.png"),"Statistiques");
            ui->listWidget_Ne->addItem(qr);

            ui->listWidget_Ne->setCurrentItem(consulter);


            QMovie *user_pic = new QMovie(":/images/images/646-walking-walkcycle-person-outline.gif");
            QMovie *gif_necessiteux = new QMovie(":/images/images/20-love-heart-flat.gif");
            QMovie *gif_rdv = new QMovie(":/images/images/rendez_vous.gif");
            QMovie *gif_qrcode = new QMovie(":/images/images/qrcode300px.gif");

            ui->user_pic->setMovie(user_pic);
            ui->gif_necessiteux->setMovie(gif_necessiteux);
            ui->gif_rdv->setMovie(gif_rdv);
            ui->gif_rdv->setMovie(gif_rdv);
            ui->qrcode->setMovie(gif_qrcode);

            user_pic->start();
            gif_necessiteux->start();
            gif_rdv->start();
            gif_qrcode->start();


            /*QTimer *timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(UserIsIdle()));
                timer->start(1000);
*/
}

/*
void MainWindow::UserIsIdle(){
    DWORD dwTickCount=GetTickCount();
    LASTINPUTINFO liiInfo;
    liiInfo.cbSize=sizeof(LASTINPUTINFO);
    GetLastInputInfo(&liiInfo);
    int idletime = (dwTickCount-liiInfo.dwTime)/1000;
    qDebug()<<idletime;

    bool datasent=false;



    if(idletime>=10){
        //ui->listWidget->hide();
        A.write_to_arduino("1");
        datasent=true;
    }
    if(datasent){
       QByteArray datareceived= A.read_from_arduino();
        if(datareceived=="1"){
        ui->listWidget->hide();
        ui->stackedWidget->hide();
        ui->box->show();
        qDebug()<<datareceived;
        }
    }


}

*/








//la liste en gauche
void MainWindow::on_listWidget_itemClicked()
{
    QString selectedvalue= ui->listWidget->currentItem()->text();

    if (selectedvalue == "Profil")
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    if (selectedvalue == "Gestion Employés")
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    if (selectedvalue == "Gestion Dons")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    if (selectedvalue == "Gestion Evenements")
    {
        ui->stackedWidget->setCurrentIndex(3);
    }
    if (selectedvalue == "Gestion Nécessiteux")
    {
        ui->stackedWidget->setCurrentIndex(4);
    }
    if (selectedvalue == "Gestion Crises")
    {
        ui->stackedWidget->setCurrentIndex(5);
    }
    if (selectedvalue == "Gestion Bénévoles")
    {
        ui->stackedWidget->setCurrentIndex(6);
    }
}

//-----------------------------------------------------------------
//Bouton Ajouter
void MainWindow::on_Ajouter_clicked()
{
    bool check,check2;
    //Control assure le control de saisie
    if(control(1))
    {
        QString type="Employe";
        QString sexe="";
        if(ui->hm->isChecked())
                sexe="Homme";
        if(ui->fm->isChecked())
                sexe="Femme";
        if(ui->au->isChecked())
                sexe="Autre";
        QString image="C:/Users/louay/Desktop/smart_aid/images/";
        image= image + ui->lineEdit_image->text();


        Employes e(0,ui->lineEdit_nom->text(),ui->lineEdit_pre->text(),ui->dateEdit_date->date().toString(),ui->lineEdit_em->text(),ui->lineEdit_ad->text(),ui->lineEdit_tele->text(),ui->lineEdit_image->text(),type,sexe);
        //if(e.check_existance(ui->lineEdit_em->text(),ui->lineEdit_tele->text()))
        check=e.Ajouter_em();
        check2=e.Ajouter_sa_em();
        e.add_be();
        if(check)
        {
            //Afficher apres l'insertion
            ui->table1->setModel(e.Afficher(1));
            ui->table2->setModel(e.Afficher(3));
            clear();
            e.Calculer_salaire();
            ui->table4->setModel(e.Afficher_Salaire(q));
            ui->status->setText("Ajouter Avec\nSuccess !");
        }
        else
        {
          ui->status->setText("Erreur Ajout !");
        }
    }
    update_stat();
}

//Bouton Modifier
void MainWindow::on_Modifier_clicked()
{
    //recuperer donnes
    if(control(1)){
        QString type="Employe";
        QString sexe="";
        if(ui->hm->isChecked())
                sexe="Homme";
        if(ui->fm->isChecked())
                sexe="Femme";
        if(ui->au->isChecked())
                sexe="Autre";
    Employes e( ui->lineEdit_id->text().toInt(),ui->lineEdit_nom->text(),ui->lineEdit_pre->text(),ui->dateEdit_date->date().toString(),ui->lineEdit_em->text(),ui->lineEdit_ad->text(),ui->lineEdit_tele->text(),ui->lineEdit_image->text(),type,sexe);
    bool check=e.Modifier_em();
    if(check)
    {
        ui->table1->setModel(e.Afficher(1));
        ui->table2->setModel(e.Afficher(3));
        clear();
      ui->status->setText("Modifier Avec\nSuccess !");
    }
    else
    {
          ui->status->setText("Erreur Modification !");
    }
    }
    update_stat();
}

//Bouton Supprimer
void MainWindow::on_Supprimer_clicked()
{
    init_errors_2();
    Employes e;
    e.setID_em(ui->lineEdit_id->text().toInt());
    qDebug() << ui->lineEdit_id->text().toInt();
    bool check=e.Supprimer_em();
    if(check)
    {
        ui->table1->setModel(e.Afficher(1));
        ui->table2->setModel(e.Afficher(3));
        clear();
        ui->status->setText("Supprimer Avec\nSuccess !");

    }
    else
    {
         ui->status->setText("Erreur Suppression !");
    }
    update_stat();

}

//Selectioner a partir du champ ID
void MainWindow::on_table1_activated(const QModelIndex &index)
{
    init_errors_2();
    clear();
    QString value=ui->table1->model()->data(index).toString();
    connection c;
    c.closeconnection();
    QSqlQuery qry;

    qry.prepare("select * from employes where id_em='"+value+"'");
    if(qry.exec())
    {
        while(qry.next())
        {

            ui->lineEdit_id->setText(qry.value(0).toString());
            ui->lineEdit_nom->setText(qry.value(1).toString());
            ui->lineEdit_pre->setText(qry.value(2).toString());

            QString dates =qry.value(3).toString();
            QDate date = QDate::fromString(dates,"ddd MMM M yyyy");
            ui->dateEdit_date->setDate(date);

            ui->lineEdit_ad->setText(qry.value(5).toString());

            ui->lineEdit_tele->setText(qry.value(4).toString());
            ui->lineEdit_em->setText(qry.value(6).toString());
            ui->lineEdit_image->setText(qry.value(8).toString());

            QPixmap pix(qry.value(8).toString());
            ui->label_pic->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));

            if(qry.value(9).toString()=="Homme")
                ui->hm->setChecked(true);
            if(qry.value(9).toString()=="Femme")
                ui->fm->setChecked(true);
            if(qry.value(9).toString()=="Autre")
                ui->au->setChecked(true);





        }
    }
}

//Bouton Actualiser
void MainWindow::on_Actualiser_clicked()
{
    Employes e;
    ui->table1->setModel(e.Afficher(1));
}

//Vide les champs aprés les CRUD
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
    ui->lineEdit_id_2->clear();
    ui->lineEdit_nom_2->clear();
    ui->lineEdit_pre_2->clear();
    ui->dateEdit_date_2->clear();
    ui->lineEdit_ad_2->clear();
    ui->lineEdit_tele_2->clear();
    ui->lineEdit_em_2->clear();
    ui->lineEdit_image_2->clear();
    ui->label_pic_2->clear();

    ui->fm->setChecked(false);
    ui->au->setChecked(false);
    ui->hm->setChecked(false);

    ui->fm_2->setChecked(false);
    ui->au_2->setChecked(false);
    ui->hm_2->setChecked(false);


}
//-----------------------------------------------------------------

//Initialiser le tab de recherche
void MainWindow::on_rechercher_textChanged(const QString &arg1)
{
    QString value=ui->rechercher->text();
    Employes e;
    if(value!=NULL) ui->table2->setModel(e.Rechercher_em(value));
    else  ui->table2->setModel(e.Afficher(3));
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

    else  ui->table2->setModel(e.Afficher(3));

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

    else  ui->table2->setModel(e.Afficher(3));
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


    else  ui->table2->setModel(e.Afficher(3));
}

//initialise les champs des erreurs
void MainWindow::init_errors()
{

    //ui->er_p->hide();
   // ui->mdp->hide();
   // ui->champ_mdp->hide();
}
void MainWindow::init_errors_2()
{
    ui->erm_nom->setText("");
    ui->erm_pr->setText("");
    ui->erm_ad->setText("");
    ui->erm_em->setText("");
    ui->erm_tel->setText("");
    ui->erm_im->setText("");
    ui->status->setText("");
    ui->erm_s->setText("");
    ui->er_p_2->setText("");

    ui->erm_nom_2->setText("");
    ui->erm_pr_2->setText("");
    ui->erm_ad_2->setText("");
    ui->erm_em_2->setText("");
    ui->erm_tel_2->setText("");
    ui->erm_im_2->setText("");
    ui->status_2->setText("");
    ui->erm_s_2->setText("");
    ui->er_p_2->setText("");



    ui->erm_nom->hide();
    ui->er_p_2->hide();
    ui->erm_pr->hide();
    ui->erm_ad->hide();
    ui->erm_em->hide();
    ui->erm_tel->hide();
    ui->erm_im->hide();

    ui->erm_nom_2->hide();
    ui->er_p_2->hide();
    ui->erm_pr_2->hide();
    ui->erm_ad_2->hide();
    ui->erm_em_2->hide();
    ui->erm_tel_2->hide();
    ui->erm_im_2->hide();

}

//controle les erreurs et les affiches
bool MainWindow::control(int n)
{
    init_errors_2();
    if(n==1)
    {
        if((ui->lineEdit_nom->text()=="")||(ui->lineEdit_pre->text()=="")||(ui->lineEdit_image->text()=="")||(ui->lineEdit_tele->text()=="")||(ui->lineEdit_ad->text()=="")||(ui->lineEdit_em->text()=="")||(!(ui->fm->isChecked())&&(!(ui->hm->isChecked()))&&(!(ui->au->isChecked()))))
        {
            if((ui->lineEdit_nom->text()=="")){ui->erm_nom->show(); ui->erm_nom->setText("Champs Obligatoire !"); }

            if(ui->lineEdit_pre->text()==""){ui->erm_pr->show();ui->erm_pr->setText("Champs Obligatoire !");}

            if(ui->lineEdit_image->text()==""){ui->erm_im->show(); ui->erm_im->setText("Champs Obligatoire !");}

            if(ui->lineEdit_tele->text()==""){ui->erm_tel->show();ui->erm_tel->setText("Champs Obligatoire !");}

            if(ui->lineEdit_ad->text()==""){ui->erm_ad->show();ui->erm_ad->setText("Champs Obligatoire !");}

            if(ui->lineEdit_em->text()==""){ui->erm_em->show(); ui->erm_em->setText("Champs Obligatoire !");}

            if(!(ui->fm->isChecked())&&(!(ui->hm->isChecked()))&&(!(ui->au->isChecked()))){ui->erm_s->show(); ui->erm_s->setText("Choisier un Sexe!");}


            return 0;
        }
        else if(!(ui->lineEdit_image->text().contains("."))||(ui->lineEdit_tele->text().length() < 8 )||!(ui->lineEdit_em->text().contains("@"))||!(ui->lineEdit_em->text().contains("."))||(ui->lineEdit_nom->text().length() < 3 )||(ui->lineEdit_pre->text().length() < 2 )||(ui->lineEdit_ad->text().length() < 10 ))
        {
            if(!(ui->lineEdit_image->text().contains("."))){ui->erm_im->show();ui->erm_im->setText("Forme Invalide ! (manque l'extension du fichier)");}

            if(ui->lineEdit_tele->text().length() < 8 ){ui->erm_tel->show(); ui->erm_tel->setText("Doit Contenir 8 chiffres !");}

            if(ui->lineEdit_ad->text().length() < 10 ){ui->erm_ad->show(); ui->erm_ad->setText("Doit Contenir 10 chiffres !");}

            if(ui->lineEdit_nom->text().length() < 3 ){ui->erm_nom->show(); ui->erm_nom->setText("Doit Contenir 3 chiffres !");}

            if(ui->lineEdit_pre->text().length() < 3 ){ui->erm_pr->show();ui->erm_pr->setText("Doit Contenir 3 chiffres !");}

            if(!(ui->lineEdit_em->text().contains("@"))||!(ui->lineEdit_em->text().contains("."))){ui->erm_em->show();ui->erm_em->setText("Forme Invalide ! (manque @ ou . )");}

            return 0;
        }
        else
            return 1;
    }
    if(n==2)
    {
        if((ui->lineEdit_nom_2->text()=="")||(ui->lineEdit_pre_2->text()=="")||(ui->lineEdit_image_2->text()=="")||(ui->lineEdit_tele_2->text()=="")||(ui->lineEdit_ad_2->text()=="")||(ui->lineEdit_em_2->text()=="")||(ui->champ_mdp_2->text()=="")||(!(ui->fm_2->isChecked())&&(!(ui->hm_2->isChecked()))&&(!(ui->au_2->isChecked()))))
        {
            if((ui->lineEdit_nom_2->text()=="")){ui->erm_nom_2->show(); ui->erm_nom_2->setText("Champs Obligatoire !"); }

            if(ui->lineEdit_pre_2->text()==""){ui->erm_pr_2->show();ui->erm_pr_2->setText("Champs Obligatoire !");}

            if(ui->lineEdit_image_2->text()==""){ui->erm_im_2->show(); ui->erm_im_2->setText("Champs Obligatoire !");}

            if(ui->lineEdit_tele_2->text()==""){ui->erm_tel_2->show();ui->erm_tel_2->setText("Champs Obligatoire !");}

            if(ui->lineEdit_ad_2->text()==""){ui->erm_ad_2->show();ui->erm_ad_2->setText("Champs Obligatoire !");}

            if(ui->lineEdit_em_2->text()==""){ui->erm_em_2->show(); ui->erm_em_2->setText("Champs Obligatoire !");}

             if(ui->champ_mdp_2->text()==""){ui->er_p_2->show(); ui->er_p_2->setText("Champs Obligatoire !");}

            if(!(ui->fm_2->isChecked())&&(!(ui->hm_2->isChecked()))&&(!(ui->au_2->isChecked()))){ui->erm_s_2->show(); ui->erm_s_2->setText("Choisier un Sexe!");}


            return 0;
        }
        else if(!(ui->lineEdit_image_2->text().contains("."))||(ui->lineEdit_tele_2->text().length() < 8 )||!(ui->lineEdit_em_2->text().contains("@"))||!(ui->lineEdit_em_2->text().contains("."))||(ui->lineEdit_nom_2->text().length() < 3 )||(ui->lineEdit_pre_2->text().length() < 2 )||(ui->lineEdit_ad_2->text().length() < 10 )||(ui->champ_mdp_2->text().length() < 8 )||(!(ui->champ_mdp_2->text().contains("."))&&!(ui->champ_mdp_2->text().contains("@"))&!(ui->champ_mdp_2->text().contains("#"))&&!(ui->champ_mdp_2->text().contains("%"))&&!(ui->champ_mdp_2->text().contains("?"))))
        {
            if(!(ui->lineEdit_image_2->text().contains("."))){ui->erm_im_2->show();ui->erm_im_2->setText("Forme Invalide ! (manque l'extension du fichier)");}

            if(ui->lineEdit_tele_2->text().length() < 8 ){ui->erm_tel_2->show(); ui->erm_tel_2->setText("Doit Contenir 8 chiffres !");}

            if(ui->lineEdit_ad_2->text().length() < 10 ){ui->erm_ad_2->show(); ui->erm_ad_2->setText("Doit Contenir 10 chiffres !");}

            if(ui->lineEdit_nom_2->text().length() < 3 ){ui->erm_nom_2->show(); ui->erm_nom_2->setText("Doit Contenir 3 chiffres !");}

            if(ui->lineEdit_pre_2->text().length() < 3 ){ui->erm_pr_2->show();ui->erm_pr_2->setText("Doit Contenir 3 chiffres !");}

            if(ui->champ_mdp_2->text().length() < 3 ){ui->er_p_2->show();ui->er_p_2->setText("Doit Contenir 8 chiffres !");}

            if((ui->champ_mdp_2->text().length() < 8 )||(!(ui->champ_mdp_2->text().contains("@"))&&!(ui->champ_mdp_2->text().contains("."))&&!(ui->champ_mdp_2->text().contains("?"))&&!(ui->champ_mdp_2->text().contains("%"))&!(ui->champ_mdp_2->text().contains("#")))){

                if(ui->champ_mdp_2->text().length() < 8 ){ui->er_p_2->show();ui->er_p_2->setText("Doit Contenir 8 chiffres !");}

                if (!(ui->champ_mdp_2->text().contains("@"))&&!(ui->champ_mdp_2->text().contains("."))&&!(ui->champ_mdp_2->text().contains("?"))&&!(ui->champ_mdp_2->text().contains("%"))&!(ui->champ_mdp_2->text().contains("#"))){
                ui->er_p_2->show();ui->er_p_2->setText("Doit Contenir un/ou Caracters speciales (@?#.%)");}

                 }


            if(!(ui->lineEdit_em_2->text().contains("@"))||!(ui->lineEdit_em_2->text().contains("."))){ui->erm_em_2->show();ui->erm_em_2->setText("Forme Invalide ! (manque @ ou . )");}

            return 0;
        }
        else
            return 1;
    }
}


//Les Boutons Menu
void MainWindow::on_Menu_modi_supp_employe_clicked()
{
    ui->tab_ge->setCurrentIndex (ui->tab_ge->currentIndex()+2);
}

void MainWindow::on_Menu_afficher_employe_clicked()
{
    ui->tab_ge->setCurrentIndex (ui->tab_ge->currentIndex()+3);
}

void MainWindow::on_Menu_ajouter_employe_clicked()
{
    ui->tab_ge->setCurrentIndex (ui->tab_ge->currentIndex()+1);
}
//Les Boutons Home
void MainWindow::on_Ajouter_Emp_HOME_clicked()
{

    ui->tab_ge->setCurrentIndex (ui->tab_ge->currentIndex()-1);
}

void MainWindow::on_modifier_Emp_HOME_clicked()
{
    ui->tab_ge->setCurrentIndex (ui->tab_ge->currentIndex()-2);
}

void MainWindow::on_Afficher_Emp_HOME_clicked()
{
    ui->tab_ge->setCurrentIndex (ui->tab_ge->currentIndex()-3);
}

void MainWindow::on_bo_3_clicked()
{

    QString email=ui->login->text();
    QString pass=ui->pass->text();
    Employes e;
    users u;
    int check=u.Login(email,pass);
    if(check!=0)
    {

            q=1;
        qDebug() << q;
        ui->er_log->setText("");
        ui->stackedWidget->show();
        ui->listWidget->show();
        //ui->box->move(0,-150);
        ui->box->hide();
        ui->er_log->hide();


    }
    else if(!check)
    {
        //QMessageBox::information(nullptr,QObject::tr("Echec"),QObject::tr("Mot de passe ou Email est incorrecte."),QMessageBox::Cancel);
        ui->er_log->show();
        ui->er_log->setText("Incorrect !");
    }





}

void MainWindow::on_pdf_clicked()
{
    const QString filename("C:/Users/louay/Desktop/smart_aid/test2.pdf");
    QString testData = "test";
    QPdfWriter pdfwriter(filename);
    pdfwriter.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&pdfwriter);
    painter.drawText(0,0, testData);
}

void MainWindow::profil()
{
    Employes e=session.getEm();
    ui->profil_nom->setText(e.getNom());
    ui->profil_pre->setText(e.getPrenom());
    ui->profil_em->setText(e.getEmail());
    ui->profil_ad->setText(e.getAdresse());
    ui->profil_tele->setText(e.getTelephone());
    QString dates =e.getDate_nais();
    QDate date = QDate::fromString(dates,"ddd MMM M yyyy");
    ui->profil_date->setDate(date);
}

void MainWindow::on_pushButton_2_clicked()
{
    Employes e;
    e.Modifier_Salaire( ui->id_sa->text().toInt(), ui->sa->text().toInt(), ui->sa_hr->text().toInt(), ui->disc->currentIndex());
    e.Calculer_salaire();
    ui->table4->setModel(e.Afficher_Salaire(q));
    ui->sa->setText("");
    ui->sa_hr->setText("");
    ui->disc->setCurrentIndex(0);
}

void MainWindow::on_table4_activated(const QModelIndex &index)
{
    QString value=ui->table4->model()->data(index).toString();
    connection c;
    c.closeconnection();
    QSqlQuery qry;

    qry.prepare("select salaire,nb_heures,disc from salaires where id='"+value+"'");
    if(qry.exec())
    {
        while(qry.next())
        {

            ui->sa->setText(qry.value(0).toString());
            ui->sa_hr->setText(qry.value(1).toString());
            ui->disc->setCurrentIndex(qry.value(2).toInt());
            ui->id_sa->setText(value);
        }
    }
}


void MainWindow::on_mdp_oub_clicked()
{
    s=1;
    ui->mdp_o->setText("Votre téléphone: ");
    ui->er_mdp->setText("");
    ui->bull_code->show();
}

void MainWindow::on_mdp_b_clicked()
{
    if(sms==0)
    {
        QString numero=ui->new_mdp->text();
        Employes e;
        int check=e.check_phone(numero);
        qDebug() << check;
        if(check==1)
        {
            int result = session.Envoyer_sms(numero);
            //int result = 0;
            if(result==0)
                ui->er_mdp->setText("Code Envoyer !");

            else  if(result==1)
                ui->er_mdp->setText("Code deja Envoyer !");

            ui->er_mdp->show();
            ui->new_mdp->setText("");
            ui->mdp_o->setText("Votre Code: ");
            ui->mdp_b->setText("Envoyer");
            e.setTelephone(numero);
            session.setEm(e);
            sms=1;
        }
        else if(check==0)
            ui->er_mdp->setText("Téléphone n'existe pas !");
    }
    else if(sms==1)
    {
        QString token=ui->new_mdp->text();
        int result = session.check_token(session,token);
        //int result = 1;
        if(result==1)
        {
            //ui->new_mdp->setText("");
            //ui->mdp_o->setText("nouveau mot de pass: ");
            sms=2;
            ui->bull_code->hide();
            ui->bull_mdp->move(580,420);
            ui->bull_mdp->show();
        }
        else if(result == 0)
            ui->er_mdp->setText("Code Incorrecte !");
    }

}

void MainWindow::on_pushButton_9_clicked()
{
    init_errors_2();
    clear();
}

void MainWindow::on_mdp_b_2_clicked()
{
        if(sms==2)
        {
            QString pass=ui->mdp1->text();
            QString pass2=ui->mdp2->text();
            if((pass==pass2)&&(pass.length()>=8))
            {
                bool result = session.Maj_pass(session,pass);
                if(result)
                {
                    ui->bull_mdp->hide();
                    ui->mdp1->setText("");
                    ui->mdp2->setText("");
                    ui->ermdp->setText("Utilisez au moins huit caractères !");
                    ui->bull_mdp->move(40,680);
                    sms=0;

                }
                else
                    ui->ermdp->setText("Error !!");
            }
            else if(pass!=pass2)  ui->ermdp->setText("Les mots de passe\nne correspondent pas !");
            else if(pass.length()<8) ui->ermdp->setText("Utilisez 8 caractères ou plus !");


        }
}

void MainWindow::on_Ajouter_2_clicked()
{
    bool check,check2;
    if(control(2))
    {
        QString type="User";
        QString sexe="";
        if(ui->hm_2->isChecked())
                sexe="Homme";
        if(ui->fm_2->isChecked())
                sexe="Femme";
        if(ui->au_2->isChecked())
                sexe="Autre";
        QString image="C:/Users/louay/Desktop/smart_aid/images/";
        image= image + ui->lineEdit_image_2->text();


        Employes e(0,ui->lineEdit_nom_2->text(),ui->lineEdit_pre_2->text(),ui->dateEdit_date_2->date().toString(),ui->lineEdit_em_2->text(),ui->lineEdit_ad_2->text(),ui->lineEdit_tele_2->text(),ui->lineEdit_image_2->text(),type,sexe);
        check=e.Ajouter_em();
        users u(e,ui->lineEdit_em_2->text(),ui->champ_mdp_2->text());
        check=u.Ajouter_user();
        check2=e.Ajouter_sa_em();
        e.add_be();
        if(check)
        {
            //Afficher apres l'insertion
            ui->table3->setModel(e.Afficher(2));
            ui->table2->setModel(e.Afficher(3));
            e.Calculer_salaire();
            ui->table4->setModel(e.Afficher_Salaire(q));
            clear();
            ui->status_2->setText("Ajouter Avec\nSuccess !");
        }
        else
        {
          ui->status_2->setText("Erreur Ajout !");
        }
    }
    update_stat();

}

void MainWindow::on_table3_activated(const QModelIndex &index)
{
    init_errors_2();
    clear();
    QString value=ui->table3->model()->data(index).toString();
    connection c;
    c.closeconnection();
    QSqlQuery qry;

    qry.prepare("select * from employes where id_em='"+value+"'");
    if(qry.exec())
    {
        while(qry.next())
        {

            ui->lineEdit_id_2->setText(qry.value(0).toString());
            ui->lineEdit_nom_2->setText(qry.value(1).toString());
            ui->lineEdit_pre_2->setText(qry.value(2).toString());

            QString dates =qry.value(3).toString();
            QDate date = QDate::fromString(dates,"ddd MMM M yyyy");
            ui->dateEdit_date_2->setDate(date);

            ui->lineEdit_ad_2->setText(qry.value(5).toString());

            ui->lineEdit_tele_2->setText(qry.value(4).toString());
            ui->lineEdit_em_2->setText(qry.value(6).toString());
            ui->lineEdit_image_2->setText(qry.value(8).toString());

            QPixmap pix(qry.value(8).toString());
            ui->label_pic_2->setPixmap(pix.scaled(100,100,Qt::KeepAspectRatio));

            if(qry.value(9).toString()=="Homme")
                ui->hm_2->setChecked(true);
            if(qry.value(9).toString()=="Femme")
                ui->fm_2->setChecked(true);
            if(qry.value(9).toString()=="Autre")
                ui->au_2->setChecked(true);





        }
    }
}

void MainWindow::on_Modifier_2_clicked()
{
    if(control(2)){
        QString type="User";
        QString sexe="";
        if(ui->hm_2->isChecked())
                sexe="Homme";
        if(ui->fm_2->isChecked())
                sexe="Femme";
        if(ui->au_2->isChecked())
                sexe="Autre";
    Employes e( ui->lineEdit_id_2->text().toInt(),ui->lineEdit_nom_2->text(),ui->lineEdit_pre_2->text(),ui->dateEdit_date_2->date().toString(),ui->lineEdit_em_2->text(),ui->lineEdit_ad_2->text(),ui->lineEdit_tele_2->text(),ui->lineEdit_image_2->text(),type,sexe);
    bool check=e.Modifier_em();
    if(check)
    {
        ui->table3->setModel(e.Afficher(2));
        ui->table2->setModel(e.Afficher(3));
        clear();
      ui->status_2->setText("Modifier Avec\nSuccess !");
    }
    else
    {
          ui->status_2->setText("Erreur Modification !");
    }
    }
    update_stat();
}

void MainWindow::on_Supprimer_2_clicked()
{
    init_errors_2();
    Employes e;
    e.setID_em(ui->lineEdit_id_2->text().toInt());
    bool check=e.Supprimer_em();
    if(check)
    {
        ui->table3->setModel(e.Afficher(2));
        ui->table2->setModel(e.Afficher(3));
        clear();
        ui->status->setText("Supprimer Avec\nSuccess !");

    }
    else
    {
         ui->status->setText("Erreur Suppression !");
    }
    update_stat();
}

void MainWindow::on_tab_ge_currentChanged(int index)
{
    if(index == 5)
    update_stat();



}

void MainWindow::update_stat()
{
    Employes e;
    ui->stat->addWidget(e.stat_gender(), 0, 0);
    ui->stat->addWidget(e.stat_age(), 0, 1);
    ui->stat->addWidget(e.stat_age_gender(), 1, 0);
    ui->stat->addWidget(e.stat_money_age(), 1, 1);
}

//test arduino
void MainWindow::on_pushButton_13_clicked()
{
 A.write_to_arduino("1");
  ui->label_35->setText("Etat: Ouvert");
     coffre=1;
}


void MainWindow::on_pushButton_14_clicked()
{
 A.write_to_arduino("2");
 ui->label_35->setText("Etat: Fermer");
    coffre=0;
}

void MainWindow::on_logout_clicked()
{
    ui->stackedWidget->hide();
    ui->listWidget->hide();
    ui->er_log->hide();
    ui->box->show();
    ui->login->setText("");
    ui->pass->setText("");
}
void MainWindow::test()
{
    data=A.read_from_arduino();
    QSqlQuery query;
    query.prepare("select CODE from users where id_user=49");
    query.exec();
    query.next();
    QString code=query.value(0).toString();
     QString code2="2";
     QString code3="3";
    const char* c= code.toStdString().c_str();
    const char* c2= code2.toStdString().c_str();
    const char* c4= code3.toStdString().c_str();
if(coffre==0)
    ui->label_35->setText("Etat: Fermer");
if(coffre==1)
    ui->label_35->setText("Etat: Ouvert");

        if(data.contains(c))
        {
            A.write_to_arduino("1");
            ui->CODE->setText(data);
            coffre=1;

        }
        else if(data.contains(c2))
        {
            query.prepare("select * from tresor");
            query.exec();
            query.next();
            QString flous=query.value(0).toString();
             const char* c3= flous.toStdString().c_str();
             qDebug() << c3;
             A.write_to_arduino(c3);
             ui->CODE->setText(data);

        }
        else if(data.contains(c4))
        {
           ui->label_35->setText("Etat: Fermer");
           coffre=0;
        }
        else {
            A.write_to_arduino("0");
            ui->CODE->setText(data);
        }
       /* else if(data.contains("2"))
        {
             A.write_to_arduino("2");
             ui->CODE->setText(data);
             ui->BOX->setText(data);
        }
        else if(data.contains("3"))
        {
            QSqlQuery query;
            query.prepare("select * from TRESOR");
            query.exec();
            query.next();
            QString montant=query.value(0).toString();

            QByteArray br = montant.toUtf8();
            A.write_to_arduino(br);

        }*/

}
void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    qDebug() <<position;
}








///////////////  NECESSITEUX //////////////////




void MainWindow::on_listWidget_Ne_itemClicked(QListWidgetItem *item)
{
    QString selectedvalue= item->text();

    if (selectedvalue == "Consulter"){
        ui->stackedWidget_Ne->setCurrentIndex(0);
    }
    if (selectedvalue == "Rendez-Vous"){
        ui->stackedWidget_Ne->setCurrentIndex(1);
    }
    if (selectedvalue == "QrCode"){
        ui->stackedWidget_Ne->setCurrentIndex(2);
    }
    if (selectedvalue == "Statistiques"){
        ui->stackedWidget_Ne->setCurrentIndex(3);
    }
    /*if (selectedvalue == "Gestion Nécessiteux"){
        ui->stackedWidget->setCurrentIndex(4);
    }
    if (selectedvalue == "Gestion Crises"){
        ui->stackedWidget->setCurrentIndex(5);
    }
    if (selectedvalue == "Gestion Bénévoles"){
        ui->stackedWidget->setCurrentIndex(6);
    }*/
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
        ui->customPlot->replot();
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
                ui->id_Ne->setText(qry.value(0).toString());
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

              /////////////// SEND TO LABEL /////////////
              QString nom = qry.value(1).toString();
              QString prenom = qry.value(2).toString();
              QString fullname = nom+" "+prenom;
              ui->namelabel->setText(fullname);
              ui->id_label->setText(qry.value(0).toString());
              ui->email_label->setText(qry.value(3).toString());
              ui->date_nai_label->setText(qry.value(6).toString());
              ui->telephone_label->setText(qry.value(4).toString());
              ui->besoin_label->setText(qry.value(7).toString());

             }

         }
}

void MainWindow::on_supprimerNecessiteux_clicked()
{
    int id = ui->id_Necessiteux->text().toInt();
    bool test =N.supprimer(id);

    if(test){
        ui->tableN->setModel(N.afficher());
        ui->tableRdv->setModel(rdv.afficher());
        ui->customPlot->replot();
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
        ui->tableRdv->setModel(rdv.afficher());
        ui->customPlot->replot();
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
    QString search=arg1;
        ui->tableN->setModel(N.rechercher(search));
}

void MainWindow::on_lineEdit_returnPressed()
{
    QString search=ui->lineEdit->text();
        ui->tableN->setModel(N.rechercher(search));
}

void MainWindow::on_qrcode_button_clicked()
{
    using namespace qrcodegen;

    ///////////////// FETCH DATA FROM DATABASE ////////////////////////
    QTableView table_necessiteux;
    QSqlQueryModel * Mod=new  QSqlQueryModel();
    QString value=ui->id_label->text();
         connection c;

         QSqlQuery qry;




         qry.prepare("select * from NÉCESSITEUX where ID_NE='"+value+"'");
         qry.exec();
         Mod->setQuery(qry);
         table_necessiteux.setModel(Mod);
         c.closeconnection();

        ///////////////// SAVING DATA ///////////
        QString ID = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 0)).toString().simplified();
        QString nom = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 1)).toString().simplified();
        QString prenom = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 2)).toString().simplified();
        QString email = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 3)).toString().simplified();
        QString telephone = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 4)).toString().simplified();
        QString adresse = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 5)).toString().simplified();
        QString date_nai = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 6)).toString().simplified();
        QString besoin = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 7)).toString().simplified();


    QString text = ID+"\n"+nom+"\n"+prenom+"\n"+email+"\n"+telephone+"\n"+adresse+"\n"+date_nai+"\n"+besoin+"\n";
      // Create the QR Code object
      QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );

      qint32 sz = qr.getSize();
      QImage im(sz,sz, QImage::Format_RGB32);
        QRgb black = qRgb( 191,112,105 );
        QRgb white = qRgb(255,255,255);
      for (int y = 0; y < sz; y++)
        for (int x = 0; x < sz; x++)
          im.setPixel(x,y,qr.getModule(x, y) ? black : white );
      ui->qrcode->setPixmap( QPixmap::fromImage(im.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}


void MainWindow::on_comboBox_Ne_currentTextChanged(const QString &arg1)
{
    ui->tableN->setModel(N.trier(arg1));
}

void MainWindow::on_ajouterRdv_clicked()
{
    int id_ne= ui->id_Ne->text().toInt();
    int id_re= ui->id_Re->text().toInt();
    QString adresse = ui->AdresseRdv->text();
    QString date = ui->date_Rdv->dateTime().toString("ddd MMM M yyyy hh:mm");
    //QString date_naissance = ui->calendarWidget->selectedDate().toString("dd/mm/yy");
    //QDate date = QDate::fromString(dates,"ddd MMM M yyyy");

    qDebug()<<date;

    rendezvous rdv(id_re,adresse,date,id_ne);



    if( date.isEmpty() || adresse.isEmpty()){
        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides."),QMessageBox::Cancel);

    }
    else{
        /*QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectué\n"
                                 "Click cancel to exit."),QMessageBox::Cancel);*/
        //refresh

        rdv.ajouter();
        ui->tableRdv->setModel(rdv.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Ajout effectué\n"
                                 "Click cancel to exit."),QMessageBox::Cancel);
        ui->id_Ne->clear();
        ui->AdresseRdv->clear();
        ui->date_Rdv->clear();
        ui->id_Re->clear();



    }
}

void MainWindow::on_tableRdv_activated(const QModelIndex &index)
{
    QString value=ui->tableRdv->model()->data(index).toString();
         connection c;
         c.closeconnection();
         QSqlQuery qry;

         qry.prepare("select * from RENDEZ_VOUS where ID_RE='"+value+"'");
         if(qry.exec())
         {
             while(qry.next()){
                ui->id_Re->setText(qry.value(0).toString());
                ui->id_Ne->setText(qry.value(3).toString());
             ui->AdresseRdv->setText(qry.value(1).toString());

              QString dates =qry.value(2).toString();
              QDate date = QDate::fromString(dates,"ddd MMM M yyyy hh:mm");
                ui->date_Rdv->setDate(date);
             }

         }
}

void MainWindow::on_modifierRdv_clicked()
{
    int id_re = ui->id_Re->text().toInt();
    int id_ne = ui->id_Re->text().toInt();
    QString adresse = ui->AdresseRdv->text();
    QString date = ui->date_Rdv->dateTime().toString("ddd MMM M yyyy hh:mm");


    rendezvous R(id_re,adresse,date,id_ne);

    bool test = R.modifier(id_re);

    if(test){

        ui->tableRdv->setModel(rdv.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
        ui->id_Ne->clear();
        ui->AdresseRdv->clear();
        ui->date_Rdv->clear();
        ui->id_Re->clear();
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Modification non effectuée\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_supprimerrDV_clicked()
{
    int id = ui->id_Re->text().toInt();
    bool test =rdv.supprimer(id);

    if(test){
        ui->tableRdv->setModel(rdv.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject::tr("Suppression effectuée\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
        ui->id_Ne->clear();
        ui->AdresseRdv->clear();
        ui->date_Rdv->clear();
        ui->id_Re->clear();
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                 QObject::tr("Suppression non effectuée\n"
                                             "Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_recherche_rdv_textChanged(const QString &arg1)
{
    QString search=arg1;
    ui->tableRdv->setModel(rdv.rechercher(search));
}

void MainWindow::on_comboBox_Rdv_currentTextChanged(const QString &arg1)
{
    ui->tableRdv->setModel(rdv.trier(arg1));
}

void MainWindow::on_generatepdf_clicked()
{
    QTableView table_necessiteux;
    QSqlQueryModel * Mod=new  QSqlQueryModel();
    QString value=ui->id_label->text();
         connection c;

         QSqlQuery qry;




         qry.prepare("select * from NÉCESSITEUX where ID_NE='"+value+"'");
         qry.exec();
         Mod->setQuery(qry);
         table_necessiteux.setModel(Mod);
         c.closeconnection();

         QString strStream;
         QTextStream out(&strStream);

       /*  const int rowCount = table_necessiteux.model()->rowCount();
         const int columnCount =  table_necessiteux.model()->columnCount();*/

         const QString strTitle ="Document";



         out <<  "<html>\n"
                               "<img src='C:/Users/alabe/Desktop/GUI/gestion necessiteux/icons/icone.png'/>"
                              "<head>\n"
                                  "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                              <<  QString("<title>%1</title>\n").arg(strTitle)
                              <<  "</head>\n"
                                  "<style> h3{"
                                  "font-family: Century Gothic; color: #333; font-weight: lighter;"
                                  "}\n"
                                  "</style>\n"
                              "<body bgcolor=#ffffff link=#5000A0>\n"
                             << QString("<h1 style=\" font-size: 40px; font-family: Century Gothic; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h1>\n").arg("Fiche Nécessiteux")
                             <<"<br>";

                            QString ID = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 0)).toString().simplified();
                            qDebug()<<ID;
                            out << QString("<h3>ID : %1</h3>").arg((!ID.isEmpty()) ? ID : QString("&nbsp;"));
                            QString nom = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 1)).toString().simplified();
                            out << QString("<h3>Nom : %1</h3>").arg((!nom.isEmpty()) ? nom : QString("&nbsp;"));
                            QString prenom = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 2)).toString().simplified();
                            out << QString("<h3>Prénom : %1</h3>").arg((!prenom.isEmpty()) ? prenom : QString("&nbsp;"));
                            QString email = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 3)).toString().simplified();
                            out << QString("<h3 bkcolor=0>Email : %1</h3>").arg((!email.isEmpty()) ? email : QString("&nbsp;"));
                            QString telephone = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 4)).toString().simplified();
                            out << QString("<h3 bkcolor=0>Telephone : %1</h3>").arg((!telephone.isEmpty()) ? telephone : QString("&nbsp;"));
                            QString adresse = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 5)).toString().simplified();
                            out << QString("<h3 bkcolor=0>Adresse : %1</h3>").arg((!adresse.isEmpty()) ? adresse : QString("&nbsp;"));
                            QString date_nai = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 6)).toString().simplified();
                            out << QString("<h3 bkcolor=0>Date de Naissance : %1</h3>").arg((!date_nai.isEmpty()) ? date_nai : QString("&nbsp;"));
                            QString besoin = table_necessiteux.model()->data(table_necessiteux.model()->index(0, 7)).toString().simplified();
                            out << QString("<h3 bkcolor=0>Besoin : %1</h3>").arg((!besoin.isEmpty()) ? besoin : QString("&nbsp;"));
                            out<<
                              "</body>\n"
                              "</html>\n";

                                  QTextDocument *document = new QTextDocument();
                                                  document->setHtml(strStream);

                                                  QPrinter printer;
                                                  QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                                                  if (dialog->exec() == QDialog::Accepted) {

                                                      document->print(&printer);
                                                  }

                                                  printer.setOutputFormat(QPrinter::PdfFormat);
                                                  printer.setPaperSize(QPrinter::A4);
                                                  printer.setOutputFileName("/tmp/necessiteux.pdf");
                                                  printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                                                  delete document;


}

void MainWindow::on_stackedWidget_Ne_currentChanged(int arg1)
{
    QTableView table_necessiteux,table_n2;
    QSqlQueryModel * Mod=new  QSqlQueryModel();
    QSqlQueryModel * Mod2=new  QSqlQueryModel();
         connection c;
         QSqlQuery qry,q2;
         qry.prepare("select BESOIN from NÉCESSITEUX group by BESOIN");
         qry.exec();
         Mod->setQuery(qry);
         table_necessiteux.setModel(Mod);

         q2.prepare("select count(*) from NÉCESSITEUX group by BESOIN");
         q2.exec();
         Mod2->setQuery(q2);
         table_n2.setModel(Mod2);

         c.closeconnection();

        qDebug()<<table_necessiteux.model()->data(table_necessiteux.model()->index(0, 0)).toString().simplified();
        qDebug()<<table_n2.model()->data(table_n2.model()->index(0, 0)).toInt();

        const int rowCount = table_necessiteux.model()->rowCount();
        const int rowCount2 = table_n2.model()->rowCount();

    if(arg1==3){

       // set dark background gradient:
        QLinearGradient gradient(0, 0, 0, 400);
        gradient.setColorAt(0, QColor(90, 90, 90));
        gradient.setColorAt(0.38, QColor(105, 105, 105));
        gradient.setColorAt(1, QColor(70, 70, 70));
        ui->customPlot->setBackground(QBrush("#fff"));

        // create empty bar chart objects:
        QCPBars *besoin = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);

        besoin->setAntialiased(false); // gives more crisp, pixel aligned bar borders

        besoin->setStackingGap(1);

        // set names and colors:

        besoin->setName("Besoin");
        besoin->setPen(QPen(QColor("#D5E7F2").lighter(130)));
        besoin->setBrush(QColor("#D5E7F2"));
        // stack bars on top of each other:


        // prepare x axis with needs' labels:
        QVector<double> ticks;
        QVector<QString> labels;

        for(int i=0; i<rowCount; ++i){
            ticks.push_back(i);
            labels.push_back(table_necessiteux.model()->data(table_necessiteux.model()->index(i, 0)).toString().simplified());
            qDebug()<<ticks[i];
            qDebug()<<labels[i];
        }
        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
        textTicker->addTicks(ticks, labels);
        ui->customPlot->xAxis->setTicker(textTicker);
        ui->customPlot->xAxis->setTickLabelRotation(60);
        ui->customPlot->xAxis->setSubTicks(false);
        ui->customPlot->xAxis->setTickLength(0, 4);
        ui->customPlot->xAxis->setRange(0, 8);
        ui->customPlot->xAxis->setBasePen(QPen(Qt::black));
        ui->customPlot->xAxis->setTickPen(QPen(Qt::black));
        ui->customPlot->xAxis->grid()->setVisible(true);
        ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        ui->customPlot->xAxis->setTickLabelColor(Qt::black);
        ui->customPlot->xAxis->setLabelColor(Qt::black);

        // prepare y axis:
        ui->customPlot->yAxis->setRange(0, 12.1);
        ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
        ui->customPlot->yAxis->setLabel("Nombre de nécessiteux\n par Besoin");
        ui->customPlot->yAxis->setBasePen(QPen(Qt::black));
        ui->customPlot->yAxis->setTickPen(QPen(Qt::black));
        ui->customPlot->yAxis->setSubTickPen(QPen(Qt::black));
        ui->customPlot->yAxis->grid()->setSubGridVisible(true);
        ui->customPlot->yAxis->setTickLabelColor(Qt::black);
        ui->customPlot->yAxis->setLabelColor(Qt::black);
        ui->customPlot->yAxis->grid()->setPen(QPen(QColor("#000"), 0, Qt::SolidLine));
        ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor("#000"), 0, Qt::DotLine));

        // Add data:
        QVector<double>besoinData;

        for(int i=0; i<rowCount2; ++i){
            besoinData.push_back(table_n2.model()->data(table_n2.model()->index(i, 0)).toInt());
            qDebug()<<besoinData;

        }

        besoin->setData(ticks, besoinData);

        // setup legend:
        ui->customPlot->legend->setVisible(true);
        ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
        ui->customPlot->legend->setBrush(QColor("#fff"));
        ui->customPlot->legend->setBorderPen(Qt::NoPen);
        QFont legendFont = font();
        legendFont.setPointSize(15);
        ui->customPlot->legend->setFont(legendFont);
        ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        ui->customPlot->replot();
    }
    ui->customPlot->replot();
}





