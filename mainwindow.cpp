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

#define chars_rx "[A-Za-z]{3,10}"
#define tel_rx "\\+[0-9]{11}"
#define email_rx "[A-Za-z0-9]{4,15}\\@+[a-z]{4,7}\\.+[a-z]{2,3}"
#define file_rx "[A-z0-9]+(\\.(jpg|png|gif|jpeg|jfif))"
int q=0;
int s=0;
int sms=0;
users session;
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

    ui->er_p->hide();
    ui->mdp->hide();
    ui->champ_mdp->hide();
    //ui->lineEdit->hide();
    //controle de saisie en temp reel
    ui->lineEdit_tele->setValidator(new QRegExpValidator( QRegExp(tel_rx),this));
    ui->lineEdit_nom->setValidator(new QRegExpValidator( QRegExp(chars_rx),this));
    ui->lineEdit_pre->setValidator(new QRegExpValidator( QRegExp(chars_rx),this));
    ui->lineEdit_em->setValidator(new QRegExpValidator( QRegExp(email_rx),this));
    ui->lineEdit_image->setValidator(new QRegExpValidator( QRegExp(file_rx),this));

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
    ui->table2->setModel(e.Afficher_em());
    ui->table1->setModel(e.Afficher_em());
    ui->table3->setModel(e.Afficher_Salaire());
    //--------------------------------------------

    //prototype login
    if(q==0)
    {
        ui->stackedWidget->hide();
        ui->listWidget->hide();
        ui->er_log->hide();
    }
    if(s==0)
    {
        ui->mdp_b->hide();
        ui->mdp_o->hide();
        ui->new_mdp->hide();
        ui->er_mdp->hide();
    }
}

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
    if(control_2())
    {
        QString type="";
        QString sexe="";
        if(ui->emp->isChecked())
                type="Employe";
        if(ui->usr->isChecked())
                type="User";
        if(ui->hm->isChecked())
                sexe="Homme";
        if(ui->fm->isChecked())
                sexe="Femme";
        if(ui->au->isChecked())
                sexe="Autre";
        QString image="C:/Users/louay/Desktop/smart_aid/images/";
        image= image + ui->lineEdit_image->text();
        if(ui->emp->isChecked())
        {
        Employes e(0,ui->lineEdit_nom->text(),ui->lineEdit_pre->text(),ui->dateEdit_date->date().toString(),ui->lineEdit_em->text(),ui->lineEdit_ad->text(),ui->lineEdit_tele->text(),ui->lineEdit_image->text(),type,sexe);
        check=e.Ajouter_em();
        check2=e.Ajouter_sa_em();
        if(check)
        {
            //Afficher apres l'insertion
            ui->table1->setModel(e.Afficher_em());
            ui->table2->setModel(e.Afficher_em());
            clear();
            ui->status->setText("Ajouter Avec\nSuccess !");
        }
        }
        if(ui->usr->isChecked())
        {
            //Employes e(0,ui->Champs_Nom->text(),ui->Champs_Prenom->text(),ui->Champs_Date->date().toString("ddd MMM M yyyy"),ui->Champs_Email->text(),ui->Champ_Adresse->text(),ui->Champ_Telephone->text(),image,type,sexe);
              Employes e(0,ui->lineEdit_nom->text(),ui->lineEdit_pre->text(),ui->dateEdit_date->date().toString(),ui->lineEdit_em->text(),ui->lineEdit_ad->text(),ui->lineEdit_tele->text(),ui->lineEdit_image->text(),type,sexe);
            check=e.Ajouter_em();
            users u(e,ui->lineEdit_em->text(),ui->champ_mdp->text());
            check=u.Ajouter_user();
            check2=e.Ajouter_sa_em();
            if(check)
            {
                //Afficher apres l'insertion
                ui->table1->setModel(e.Afficher_em());
                ui->table2->setModel(e.Afficher_em());
                clear();
                ui->status->setText("Ajouter Avec\nSuccess !");
            }
        }


        else
        {
          ui->status->setText("Erreur Ajout !");
        }
    }
}

//Bouton Modifier
void MainWindow::on_Modifier_clicked()
{
    //recuperer donnes
    if(control_2()){
        QString type="";
        QString sexe="";
        if(ui->emp->isChecked())
                type="Employe";
        if(ui->usr->isChecked())
                type="User";
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
        ui->table1->setModel(e.Afficher_em());
        ui->table2->setModel(e.Afficher_em());
        clear();
      ui->status->setText("Modifier Avec\nSuccess !");
    }
    else
    {
          ui->status->setText("Erreur Modification !");
    }
    }
}

//Bouton Supprimer
void MainWindow::on_Supprimer_clicked()
{
    init_errors_2();
    Employes e;
    e.setID_em(ui->lineEdit_id->text().toInt());
    bool check=e.Supprimer_em();
    if(check)
    {
        ui->table1->setModel(e.Afficher_em());
        ui->table2->setModel(e.Afficher_em());
        clear();
        ui->status->setText("Supprimer Avec\nSuccess !");

    }
    else
    {
         ui->status->setText("Erreur Suppression !");
    }

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

            if(qry.value(7).toString()=="Employe")
                ui->emp->setChecked(true);
            if(qry.value(7).toString()=="User")
                ui->usr->setChecked(true);




        }
    }
}

//Bouton Actualiser
void MainWindow::on_Actualiser_clicked()
{
    Employes e;
    ui->table1->setModel(e.Afficher_em());
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
    ui->fm->setChecked(false);
    ui->au->setChecked(false);
    ui->hm->setChecked(false);
    ui->fm->setChecked(false);
    ui->au->setChecked(false);
    ui->hm->setChecked(false);
    ui->usr->setChecked(false);
    ui->emp->setChecked(false);

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
    ui->er_p->setText("");



    ui->erm_nom->hide();
    ui->er_p->hide();
    ui->erm_pr->hide();
    ui->erm_ad->hide();
    ui->erm_em->hide();
    ui->erm_tel->hide();
    ui->erm_im->hide();

}

//controle les erreurs et les affiches
bool MainWindow::control()
{
   return 0;
}
bool MainWindow::control_2()
{
    init_errors_2();
    if((ui->lineEdit_nom->text()=="")||(ui->lineEdit_pre->text()=="")||(ui->lineEdit_image->text()=="")||(ui->lineEdit_tele->text()=="")||(ui->lineEdit_ad->text()=="")||(ui->lineEdit_em->text()=="")||(!(ui->fm->isChecked())&&(!(ui->hm->isChecked()))&&(!(ui->au->isChecked()))&&(!(ui->emp->isChecked()))&&(!(ui->usr->isChecked()))))
    {
        if((ui->lineEdit_nom->text()=="")){ui->erm_nom->show(); ui->erm_nom->setText("Champs Obligatoire !"); }

        if(ui->lineEdit_pre->text()==""){ui->erm_pr->show();ui->erm_pr->setText("Champs Obligatoire !");}

        if(ui->lineEdit_image->text()==""){ui->erm_im->show(); ui->erm_im->setText("Champs Obligatoire !");}

        if(ui->lineEdit_tele->text()==""){ui->erm_tel->show();ui->erm_tel->setText("Champs Obligatoire !");}

        if(ui->lineEdit_ad->text()==""){ui->erm_ad->show();ui->erm_ad->setText("Champs Obligatoire !");}

        if(ui->lineEdit_em->text()==""){ui->erm_em->show(); ui->erm_em->setText("Champs Obligatoire !");}

        if(!(ui->fm->isChecked())&&(!(ui->hm->isChecked()))&&(!(ui->au->isChecked()))){ui->erm_s->show(); ui->erm_s->setText("Choisier un Sexe!");}

        if((!(ui->emp->isChecked()))&&(!(ui->usr->isChecked()))){ui->er_t->show(); ui->er_t->setText("Choisier un Type!");}

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
    qDebug() << "22";
    users u;
    bool check=u.Login(email,pass);
    if(check)
    {
        q=1;
        ui->er_log->setText("");
        ui->stackedWidget->show();
        ui->listWidget->show();
        //ui->box->move(0,-150);
        ui->box->hide();
        ui->er_log->hide();
        session=u.session(email,pass);
        profil();
    }
    else if(!check)
    {
        //QMessageBox::information(nullptr,QObject::tr("Echec"),QObject::tr("Mot de passe ou Email est incorrecte."),QMessageBox::Cancel);
        ui->er_log->show();
        ui->er_log->setText("Incorrect !");
    }





}


void MainWindow::on_usr_clicked()
{
    ui->er_p->show();
    ui->mdp->show();
    ui->champ_mdp->show();
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
    ui->table3->setModel(e.Afficher_Salaire());
    ui->sa->setText("");
    ui->sa_hr->setText("");
    ui->disc->setCurrentIndex(0);
}

void MainWindow::on_table3_activated(const QModelIndex &index)
{
    QString value=ui->table3->model()->data(index).toString();
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
    ui->mdp_b->show();
    ui->mdp_o->show();
    ui->new_mdp->show();
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
        if(result==1)
        {
            ui->new_mdp->setText("");
            ui->mdp_o->setText("nouveau mot de pass: ");
            sms=2;
        }
        else if(result == 0)
            ui->er_mdp->setText("Code Incorrecte !");
    }
    else if(sms==2)
    {
        QString pass=ui->new_mdp->text();
        bool result = session.Maj_pass(session,pass);
        if(result)
        {
            sms=0; 

        }
        else
            ui->er_mdp->setText("Error !!");
    }
}

void MainWindow::on_pushButton_9_clicked()
{
    init_errors_2();
    clear();
    ui->champ_mdp->hide();
    ui->mdp->hide();
}
