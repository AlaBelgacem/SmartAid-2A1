#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"employes.h"
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include<QMessageBox>
#include <QRegExpValidator>

#define chars_rx "[A-Za-z]{3,10}"
#define tel_rx "\\+[0-9]{11}"
#define email_rx "[A-Za-z0-9]{4,15}\\@+[a-z]{4,7}\\.+[a-z]{2,3}"
#define file_rx "[A-z0-9]+(\\.(jpg|png|gif|jpeg|jfif))"
int q=0;
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
    //ajouter
    ui->Champ_Telephone->setValidator(new QRegExpValidator( QRegExp(tel_rx),this));
    ui->Champs_Nom->setValidator(new QRegExpValidator( QRegExp(chars_rx),this));
    ui->Champs_Prenom->setValidator(new QRegExpValidator( QRegExp(chars_rx),this));
    ui->Champs_Email->setValidator(new QRegExpValidator( QRegExp(email_rx),this));
    ui->Champs_Image->setValidator(new QRegExpValidator( QRegExp(file_rx),this));
    //modifier
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
    //--------------------------------------------

    //prototype login
    if(q==0)
    {
        ui->stackedWidget->hide();
        ui->listWidget->hide();
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
    //Control assure le control de saisie
    if(control())
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
        image= image + ui->Champs_Image->text();
        //recuperer donnes
        qDebug() << "1";
        Employes e(0,ui->Champs_Nom->text(),ui->Champs_Prenom->text(),ui->Champs_Date->date().toString("ddd MMM M yyyy"),ui->Champs_Email->text(),ui->Champ_Adresse->text(),ui->Champ_Telephone->text(),image,type,sexe);
        qDebug() << "2";
        bool check=e.Ajouter_em();
        qDebug() << "3";
        if(check)
        {
            //Afficher apres l'insertion
            ui->table1->setModel(e.Afficher_em());
            ui->table2->setModel(e.Afficher_em());
            clear();
            ui->ajout->setText("Ajouter Avec Success !");
        }
        else
        {
           // QMessageBox::information(nullptr,QObject::tr("Insertion"),
                     //                QObject::tr("insertion echoué."),QMessageBox::Cancel);
        }
    }
}

//Bouton Modifier
void MainWindow::on_Modifier_clicked()
{
    //recuperer donnes
    if(control_2()){
        QString sexe="";
        if(ui->hm_m->isChecked())
                sexe="Homme";
        if(ui->fm_m->isChecked())
                sexe="Femme";
        if(ui->au_m->isChecked())
                sexe="Autre";
    Employes e( ui->lineEdit_id->text().toInt(),ui->lineEdit_nom->text(),ui->lineEdit_pre->text(),ui->dateEdit_date->date().toString(),ui->lineEdit_em->text(),ui->lineEdit_ad->text(),ui->lineEdit_tele->text(),ui->lineEdit_image->text(),ui->lineEdit->text(),sexe);
    bool check=e.Modifier_em();
    if(check)
    {
        ui->table1->setModel(e.Afficher_em());
        ui->table2->setModel(e.Afficher_em());
        clear();
      ui->modifi->setText("Modifier Avec Success !");
    }
    else
    {
        QMessageBox::information(nullptr,QObject::tr("Modification"),
                                 QObject::tr("Modification echoué."),QMessageBox::Cancel);
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
        ui->suprim->setText("Supprimer Avec Success !");

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
    init_errors_2();
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

            ui->lineEdit->setText(qry.value(7).toString());

            if(qry.value(9).toString()=="Homme")
                ui->hm_m->setChecked(true);
            if(qry.value(9).toString()=="Femme")
                ui->fm_m->setChecked(true);
            if(qry.value(9).toString()=="Autre")
                ui->au_m->setChecked(true);




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
    ui->fm_m->setChecked(false);
    ui->au_m->setChecked(false);
    ui->hm_m->setChecked(false);
    ui->fm->setChecked(false);
    ui->au->setChecked(false);
    ui->hm->setChecked(false);
    ui->usr->setChecked(false);
    ui->emp->setChecked(false);

    ui->Champs_Nom->clear();
    ui->Champs_Prenom->clear();
    ui->Champs_Date->clear();
    ui->Champ_Adresse->clear();
    ui->Champ_Telephone->clear();
    ui->Champs_Email->clear();
    ui->Champs_Image->clear();

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
    ui->er_nom->setText("");
    ui->er_pr->setText("");
    ui->er_ad->setText("");
    ui->er_em->setText("");
    ui->er_tel->setText("");
    ui->er_im->setText("");
    ui->ajout->setText("");
    ui->er_t->setText("");
    ui->er_s->setText("");


    ui->er_nom->hide();
    ui->er_pr->hide();
    ui->er_ad->hide();
    ui->er_em->hide();
    ui->er_tel->hide();
    ui->er_im->hide();
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
    ui->modifi->setText("");
    ui->suprim->setText("");
    ui->erm_s->setText("");



    ui->erm_nom->hide();
    ui->erm_pr->hide();
    ui->erm_ad->hide();
    ui->erm_em->hide();
    ui->erm_tel->hide();
    ui->erm_im->hide();

}

//controle les erreurs et les affiches
bool MainWindow::control()
{
    init_errors();
    if((ui->Champs_Nom->text()=="")||(ui->Champs_Prenom->text()=="")||(ui->Champs_Image->text()=="")||(ui->Champ_Telephone->text()=="")||(ui->Champ_Adresse->text()=="")||(ui->Champs_Email->text()=="")||(!(ui->fm->isChecked())&&(!(ui->hm->isChecked()))&&(!(ui->au->isChecked()))&&(!(ui->emp->isChecked()))&&(!(ui->usr->isChecked()))))
    {
        if((ui->Champs_Nom->text()=="")){ui->er_nom->show(); ui->er_nom->setText("Champs Obligatoire !"); }

        if(ui->Champs_Prenom->text()==""){ui->er_pr->show();ui->er_pr->setText("Champs Obligatoire !");}

        if(ui->Champs_Image->text()==""){ui->er_im->show(); ui->er_im->setText("Champs Obligatoire !");}

        if(ui->Champ_Telephone->text()==""){ui->er_tel->show();ui->er_tel->setText("Champs Obligatoire !");}

        if(ui->Champ_Adresse->text()==""){ui->er_ad->show();ui->er_ad->setText("Champs Obligatoire !");}

        if(ui->Champs_Email->text()==""){ui->er_em->show(); ui->er_em->setText("Champs Obligatoire !");}

        if(!(ui->fm->isChecked())&&(!(ui->hm->isChecked()))&&(!(ui->au->isChecked()))){ui->er_s->show(); ui->er_s->setText("Choisier un Sexe!");}

        if((!(ui->emp->isChecked()))&&(!(ui->usr->isChecked()))){ui->er_t->show(); ui->er_t->setText("Choisier un Type!");}

        return 0;
    }
    else if(!(ui->Champs_Image->text().contains("."))||(ui->Champ_Telephone->text().length() < 8 )||!(ui->Champs_Email->text().contains("@"))||!(ui->Champs_Email->text().contains("."))||(ui->Champs_Nom->text().length() < 3 )||(ui->Champs_Prenom->text().length() < 2 )||(ui->Champ_Adresse->text().length() < 10 ))
    {
        if(!(ui->Champs_Image->text().contains("."))){ui->er_im->show();ui->er_im->setText("Forme Invalide ! (manque l'extension du fichier)");}

        if(ui->Champ_Telephone->text().length() < 8 ){ui->er_tel->show(); ui->er_tel->setText("Doit Contenir 8 chiffres !");}

        if(ui->Champ_Adresse->text().length() < 10 ){ui->er_ad->show(); ui->er_ad->setText("Doit Contenir 10 chiffres !");}

        if(ui->Champs_Nom->text().length() < 3 ){ui->er_nom->show(); ui->er_nom->setText("Doit Contenir 3 chiffres !");}

        if(ui->Champs_Prenom->text().length() < 3 ){ui->er_pr->show();ui->er_pr->setText("Doit Contenir 3 chiffres !");}

        if(!(ui->Champs_Email->text().contains("@"))||!(ui->Champs_Email->text().contains("."))){ui->er_em->show();ui->er_em->setText("Forme Invalide ! (manque @ ou . )");}

        return 0;
    }
    else
        return 1;
}
bool MainWindow::control_2()
{
    init_errors_2();
    if((ui->lineEdit_nom->text()=="")||(ui->lineEdit_pre->text()=="")||(ui->lineEdit_image->text()=="")||(ui->lineEdit_tele->text()=="")||(ui->lineEdit_ad->text()=="")||(ui->lineEdit_em->text()==""))
    {
        if((ui->lineEdit_nom->text()=="")){ui->erm_nom->show(); ui->erm_nom->setText("Champs Obligatoire !"); }

        if(ui->lineEdit_pre->text()==""){ui->erm_pr->show();ui->erm_pr->setText("Champs Obligatoire !");}

        if(ui->lineEdit_image->text()==""){ui->erm_im->show(); ui->erm_im->setText("Champs Obligatoire !");}

        if(ui->lineEdit_tele->text()==""){ui->erm_tel->show();ui->erm_tel->setText("Champs Obligatoire !");}

        if(ui->lineEdit_ad->text()==""){ui->erm_ad->show();ui->erm_ad->setText("Champs Obligatoire !");}

        if(ui->lineEdit_em->text()==""){ui->erm_em->show(); ui->erm_em->setText("Champs Obligatoire !");}

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
    q=1;
    ui->stackedWidget->show();
    ui->listWidget->show();
    //ui->box->move(0,-150);
    ui->box->hide();


}



void MainWindow::on_usr_clicked()
{
    ui->er_p->show();
    ui->mdp->show();
    ui->champ_mdp->show();
}
