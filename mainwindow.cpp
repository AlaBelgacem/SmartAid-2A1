#include "mainwindow.h"
#include<QMessageBox>
#include "ui_mainwindow.h"
#include"evenements.h"
#include "connection.h"
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include <QDateTime>
#include <QDate>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QtPrintSupport>
#include <QFile>
#include <QPainter>
#include <QPdfWriter>
#include <QProcess>

//setWindowIcon(QIcon(":/icons/icons/icone.png"));

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    //Initialisation du code postal
    ui->Code_Postal_3->setValue(1000);
    ui->Code_Postal_4->setValue(1000);
    //Affichage status
    Connection c;
    bool test=c.createconnect();
    if(test==true)
        ui->status->setText("Connecte ✓");
    else
        ui->status->setText("Echec x");
    //******************Style De L'interface ***************************//
    //Affichage gif page 1
    QPixmap pix(":/images/images/copy.jpg");
    QLabel label;
    QMovie *movie = new QMovie(":/images/images/646-walking-walkcycle-person-outline.gif");
    ui->user_pic->setMovie(movie);
    movie->start();
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
    //Mise En Date la date d'aujourdh'ui pour le champs date_deb dans ajouter
      QDateTime cdt = QDateTime::currentDateTime();
    ui->Date_4->setDateTime(cdt);
    //Style De La Liste Droite
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
    //Affichage
    ui->tableView->setModel(E.afficher());
    //To Do list
    load();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//Navigation Dans le menu gauche
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
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



//*************************Boutons Menu Evenements Page 1****************************//

//Bouton Numero 1 Ajouter Evenement
void MainWindow::on_Bouton_Ajouter_Event_Menu_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()+1);
}
//Bouton Numero 2 Afficher Evenements

void MainWindow::on_Bouton_Afficher_Event_Menu_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()+2);
}
//Bouton Numero 3 Modifier Ou Supprimer Evenements
void MainWindow::on_Bouton_Modif_Supp_Event_Menu_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()+3);
}
//Bouton Numero 4 Afficher Le Calendrier
void MainWindow::on_Bouton_Calendrier_Menu_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()+4);
}

//Bonton Numero 6 Documents Administratifs (Travail En Cours)
void MainWindow::on_Bouton_Documents_Administratifs_Menu_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()+5);
}
//Bonton Numero 7 Affiche De L'evenement (Travail En Cours)

void MainWindow::on_Bouton_Affiche_Menu_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()+6);
}

//*************************Boutons Home De Chaque Page ****************************//
//Home de la page Ajouter Event
void MainWindow::on_Ajouter_Event_HOME_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()-1);
}
//Home de la page Afficher Event
void MainWindow::on_Afficher_Event_HOME_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()-2);
}
//Home de la page Modifier_Supprimer Event
void MainWindow::on_Modifier_Supprimer_Event_HOME_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()-3);
}
//Home de la page Calendrier

void MainWindow::on_Calendrier_HOME_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()-4);
}
void MainWindow::on_ToDoList_HOME_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()-5);
}
void MainWindow::on_Affiche_Home_clicked()
{
    ui->tabWidget->setCurrentIndex (ui->tabWidget->currentIndex()-6);
}

//********************************Quelques Boutons*********************//
//Bouton Vider Les Champs
void MainWindow::on_Bouton_Vider_Champs_Page1_clicked()
{
    ui->Nom_4->setText("");
    ui->Type_4->setText("");
    QDateTime date = QDateTime::currentDateTime();
    ui->Date_4->setDateTime(date);
    ui->Ville_4->setText("");
    ui->Code_Postal_4->setValue(0);
    ui->Description_4->setText("");
}
//******************************** CRUD  *******************************//

//Fonction Ajouter Page 1


void MainWindow::on_Ajouter_event_clicked()
{
   QSqlQuery qry;
   int controle=0;
    ui->erreur_nom->setText("");
    ui->erreur_prenom->setText("");
    ui->erreur_ville->setText("");
    ui->erreur_code->setText("");
    ui->erreur_date->setText("");
    ui->erreur_description->setText("");
    qry.prepare("select * from evenements ");            //Selectionner L'event avec le même ID
    if(qry.exec())
    {
        while(qry.next())
        {   if(qry.value(5).toDate()==ui->Date_4->date())
          {ui->erreur_date->setText("Veuillez Saisir Une Date Disponible.");
              controle=1;}
        }
    }

    Evenements Event; //Creation De L'instance Event

    //Controle De saisie
    if(ui->Nom_4->text() == "")
    {
        ui->erreur_nom->setText("Champ Obligatoire*");
        controle=1;
    }
    if(ui->Type_4->text() == "")
    {
        ui->erreur_prenom->setText("Champ Obligatoire*");
        controle=1;
    }
    if(ui->Ville_4->text()== "")
    {
        ui->erreur_ville->setText("Champ Obligatoire*");
        controle=1;
    }
    if((ui->Code_Postal_4->value() <= 0)||(ui->Code_Postal_4->value() < 999))
    {
        ui->erreur_code->setText("Veuillez Saisir Un Code Postal Valide.");
        controle=1;
    }
    if(ui->Date_4->dateTime()<  QDateTime::currentDateTime())
    {
        ui->erreur_date->setText("Veuillez Saisir Une Date Valide.");
        controle=1;
    }
    if(ui->Description_4->toPlainText()== "")
    {
        ui->erreur_description->setText("Champ Obligatoire*");
        controle=1;
    }

    if(controle ==0)

    {
        Event.setNom(ui->Nom_4->text());
        Event.settype(ui->Type_4->text());
        Event.setdate_deb(ui->Date_4->dateTime());
        Event.setville(ui->Ville_4->text());
        Event.setCode_postal(ui->Code_Postal_4->value());
        Event.setdescription(ui->Description_4->toPlainText());
        bool resultat=Event.ajouter();                             //Appel de la fonction Ajouter (a voir dans evenements.cpp)
        if (resultat==true)
        {
            QMessageBox::information(this,"Ajout Event","Ajout Effectué Avec Sucess.");    //Si l'ajout se fait avec sucess un message de sucess s'affiche
            ui->tableView->setModel(Event.afficher());
        }
        else
            QMessageBox::information(this,"Ajout Event","Echec De L'ajout.");
    }//Si l'ajout echoue un message d'erreur s'affiche
}

//Fonction Modifier Ou Supprimer Page 3
//Cette Fonction permet de remplir tous les champs suite a la saisie de l'id
void MainWindow::on_line_id_returnPressed()
{

    QString value=ui->line_id->text(); //Declaration de la variable qui va contenir l'id saisi
    QSqlQuery qry;

    qry.prepare("select * from evenements where id_ev='"+value+"'");            //Selectionner L'event avec le même ID
    if(qry.exec())
    {
        while(qry.next())
        {
            //Remplir tous les champs par les données concernées

            ui->Nom_3->setText(qry.value(1).toString());
            ui->Type_3->setText(qry.value(4).toString());
            ui->Date_3->setDateTime(qry.value(5).toDateTime());
            ui->Ville_3->setText(qry.value(2).toString());
            ui->Code_Postal_3->setValue(qry.value(6).toInt());
            ui->Description_3->setText(qry.value(3).toString());

        }
    }
}
//Fonction Modifier
void MainWindow::on_Bouton_Modifier_Page3_clicked()
{
    QString value=ui->line_id->text(); //Declaration de la variable qui va contenir l'id saisi
    QSqlQuery qry;
    QDate datet;
    QTextCharFormat formattt ;
    formattt.setForeground(QBrush(Qt::black, Qt::SolidPattern));
    qry.prepare("select * from evenements where id_ev='"+value+"'");            //Selectionner L'event avec le même ID
    if(qry.exec())
    {
        while(qry.next())
        {

            datet=qry.value(5).toDate();
        }
    }

    ui->erreur_nom2->setText("");
    ui->erreur_prenom2->setText("");
    ui->erreur_ville2->setText("");
    ui->erreur_code2->setText("");
    ui->erreur_date2->setText("");
    ui->erreur_description2->setText("");
    int controle=0;
    //Controle De saisie
    if(ui->Nom_3->text() == "")
    {
        ui->erreur_nom2->setText("Champ Obligatoire*");
        controle=1;
    }
    if(ui->Type_3->text() == "")
    {
        ui->erreur_prenom2->setText("Champ Obligatoire*");
        controle=1;
    }
    if(ui->Ville_3->text()== "")
    {
        ui->erreur_ville2->setText("Champ Obligatoire*");
        controle=1;
    }
    if((ui->Code_Postal_3->value() <= 0)||(ui->Code_Postal_3->value() < 999))
    {
        ui->erreur_code2->setText("Veuillez Saisir Un Code Postal Valide.");
        controle=1;
    }
    if(ui->Date_3->dateTime()< QDateTime::currentDateTime())
    {
        ui->erreur_date2->setText("Veuillez Saisir Une Date Valide.");
        controle=1;
    }
    if(ui->Description_3->toPlainText()== "")
    {
        ui->erreur_description2->setText("Champ Obligatoire*");
        controle=1;
    }

    if(controle ==0)

    {
        Evenements e;      //Declaration De L'instance
        e.setId_event(ui->line_id->text().toInt());
        e.setNom(ui->Nom_3->text());
        e.settype(ui->Type_3->text());
        e.setville(ui->Ville_3->text());
        e.setdate_deb(ui->Date_3->dateTime());
        e.setdescription(ui->Description_3->toPlainText());
        e.setCode_postal(ui->Code_Postal_3->text().toInt());
        bool resultat=e.Modifier();
        if (resultat==true)
        {
            QMessageBox::information(this,"Modifier Event","Modification Effectuée Avec Sucess.");
            ui->calendarWidgett->setDateTextFormat(datet, formattt);
            ui->tableView->setModel(e.afficher());
        }
        else
            QMessageBox::information(this,"Modifier Event","Echec De La Modification.");
    }
}

//Fonction Supprimer
void MainWindow::on_Bouton_Supprimer_Page3_clicked()
{
    QTextCharFormat formattt ;
    QDate datet;
    formattt.setForeground(QBrush(Qt::black, Qt::SolidPattern));
    QString value=ui->line_id->text(); //Declaration de la variable qui va contenir l'id saisi
    QSqlQuery qry;
    qry.prepare("select * from evenements where id_ev='"+value+"'");            //Selectionner L'event avec le même ID
    if(qry.exec())
    {
        while(qry.next())
        {

            datet=qry.value(5).toDate();
        }
    }
    Evenements Event;
    Event.setId_event(ui->line_id->text().toInt());
    bool resultat=Event.supprimer();
    if (resultat==true)
    {
        QMessageBox::information(this,"Supprimer Event","Suppression Effectué Avec Sucess.");
        ui->tableView->setModel(Event.afficher());
        ui->calendarWidgett->setDateTextFormat(datet, formattt);
    }
    else
        QMessageBox::information(this,"Supprimer Event","Echec De La Suppression.");
}

//********************************Les Metiers **************************//


//Fonction De Recherche Page 2
void MainWindow::on_search_bar_textChanged(const QString &arg1)
{
    Evenements E;
    if (ui->search_bar->text()=="")
        ui->tableView->setModel(E.afficher());
    else
    {
        //Declaration de l'instance E
        Connection c;                                                            //Creation D'une connection avec la db
        QSqlQueryModel *modal=new QSqlQueryModel();
        c.createconnect();
        QSqlQuery *qry=new QSqlQuery(c.getDB());
        QString value= ui->search_bar->text();                                   //Affecter a value le nom saisi dans la barre de recherche
        qry->prepare("select * from evenements where NOM like '%"+value+"%'");          //Selectionner l'event avec ce nom de la db
        qry->exec();
        modal->setQuery(*qry);
        ui->tableView->setModel(modal);
    }
}
//Fonctions Tri Page 2









void MainWindow::on_Bouton_Certifications_Menu_clicked()
{
    QString html =
        "<div style='border: 10px solid #787878;width:100px; height:100px; padding:10px; text-align:center; '>"
        " <div style='width:750px; height:550px; padding:20px; text-align:center; border: 5px solid #787878'>"
        "<span style='font-size:70px;font-family:Monotype Corsiva,serif; font-weight:bold'>Certificat De Formation</span>"
        "<br><br><br><br>"
        "<span style='font-size:40px;font-family:Monotype Corsiva,serif;color:grey;'><i>Toutes Nos Félicitations à</i></span>"
        "<br><br><br><br><br><br>"

        "<span style='font-size:15px'><i> Monsieur/Madame.....................</i></span>"
        "<span style='font-size:15px'><i> qui a participé(e) activement a notre formation.</i></span>"
        "<span style='font-size:15px'><i> En reconaissance à .............. accomplie avec succés, et qui s'est tenue à .................... Ce certificat est fiérement décerné par l'association smart-aid.</i></span> <br><br><br><br><br><br><br><br/><br/><br/>"
        "<div align =left>"
        "<span  style='font-size:30px;font-family:Monotype Corsiva,serif;'><i>Signature Du Formateur</i></span>"
        " </div>"
        "<div align =right>"
        "<span  style='font-size:15px'>............... Le ..../..../....</span>"
        " </div>"
        " </div>"
        "</div>";

    QTextDocument document;
    document.setHtml(html);
    const QString filename("D:/2A1/Projet C++/app/certification.pdf");



    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOrientation(QPrinter::Landscape);

    printer.setOutputFileName(filename);
    printer.setPageMargins(QMarginsF(15, 15, 15, 15));

    document.print(&printer);
    QDesktopServices::openUrl(QUrl::fromLocalFile(filename));







}






void MainWindow::on_Design1_clicked()
{
    Evenements E;
    QString value=ui->line_id_2->text(); //Declaration de la variable qui va contenir l'id saisi
    if (ui->line_id_2->text().isEmpty())
    {
        ui->erreur_nom_2->setText("Champ Obligatoire*");
    }
    else
    {
        ui->erreur_nom_2->setText("");
        QSqlQuery qry;
        qry.prepare("select * from evenements where id_ev='"+value+"'");            //Selectionner L'event avec le même ID
        if(qry.exec())
        {
            while(qry.next())
            {




                QString html =

                    "<body background=':/images/images/Design1.png' style='height:300px'>"
                    "<br><br><br><br><br><br><br><br><br>"
                    "<div align =right>"
                    "<span style='font-size:20px;font-family:Monotype Corsiva,serif;color:white; margin-right:100px;font-weight:bold' >"+qry.value(1).toString()+"</span>"
                    "</div>"
                    "<br><br>"
                    "<div align =right>"
                    "<span style='font-size:20px;font-family:Monotype Corsiva,serif;color:white; margin-right:100px;font-weight:bold'>"+qry.value(5).toString()+"</span>"
                    "</div>"
                    "<br><br><br><br><br><br><br><br><br><br><br><br>"
                    "<span style='font-size:40px;font-family:Monotype Corsiva,serif;color:black;'><i>"+qry.value(4).toString()+"</i></span>"
                    "<br><br><br><br><br><br>"

                    "<span style='font-size:15px'><i>"+qry.value(3).toString()+"</i></span>"
                    "<br><br><br>"
                    "<div align =right>"
                    "<span  style='font-size:15px'>"+qry.value(2).toString()+"</span>"
                    "<span  style='font-size:15px'>, "+qry.value(6).toString()+"</span>"
                    " </div>"
                    "<br><br><br>"
                    "<div align =left>"
                    "<img src =':/images/images/sante.jpg'>"
                    " </div>"



                    "<body>";

                QTextDocument document;
                document.setHtml(html);
                const QString filename("C:/cygwin64/home/cyrin/Design.pdf");
                const QString filename2("C:/cygwin64/home/cyrin/Affiche-1.png");



                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                //printer.setOrientation(QPrinter::Landscape);

                printer.setOutputFileName(filename);
                printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                document.print(&printer);

//#pdftoppm -png c.pdf test.png

                QProcess::startDetached("C:\\cygwin64\\bin\\mintty.exe",QStringList() << "/home/cyrin/convrt.sh");

                QDesktopServices::openUrl(QUrl::fromLocalFile(filename2));

            }
        }
    }
}




//***********************************************************************************
void MainWindow::on_Design2_clicked()
{
    Evenements E;
    QString value=ui->line_id_2->text(); //Declaration de la variable qui va contenir l'id saisi
    if (ui->line_id_2->text().isEmpty())
    {
        ui->erreur_nom_2->setText("Champ Obligatoire*");
    }
    else
    {
        ui->erreur_nom_2->setText("");
        QSqlQuery qry;
        qry.prepare("select * from evenements where id_ev='"+value+"'");            //Selectionner L'event avec le même ID
        if(qry.exec())
        {
            while(qry.next())
            {




                QString html =

                    "<body background=':/images/images/Design_second.png'>"
                    "<br><br><br><br><br><br><br><br><br>"
                    "<div align =right>"
                    "<span style='font-size:25px;font-family:Monotype Corsiva,serif;color:white; margin-right:100px;font-weight:bold' >"+qry.value(4).toString()+"</span>"
                    "</div>"
                    "<br><br><br><br><br>"
                    "<div align =right>"
                    "<span style='font-size:20px;font-family:Monotype Corsiva,serif;color:white; margin-right:100px;font-weight:bold'>"+qry.value(5).toString()+"</span>"
                    "</div>"
                    "<br><br><br><br><br><br><br><br><br><br><br><br><br>"
                    "<span style='font-size:42px;font-family:Monotype Corsiva,serif;color:black;'><i>"+qry.value(1).toString()+"</i></span>"
                    "<br><br><br><br><br><br><br><br>"

                    "<span style='font-size:15px;color:white;'><i>"+qry.value(3).toString()+"</i></span>"
                    "<br><br><br><br><br><br>"
                    "<div align =right>"
                    "<span  style='font-size:15px;color:white;'>"+qry.value(2).toString()+"</span>"
                    "<span  style='font-size:15px;color:white;'>, "+qry.value(6).toString()+"</span>"
                    " </div>"
                    "<br><br><br>"




                    "<body>";

                QTextDocument document;
                document.setHtml(html);
                const QString filename("C:/cygwin64/home/cyrin/Design.pdf");
                const QString filename2("C:/cygwin64/home/cyrin/Affiche-1.png");



                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                //printer.setOrientation(QPrinter::Landscape);

                printer.setOutputFileName(filename);
                printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                document.print(&printer);

                //#pdftoppm -png c.pdf test.png

                QProcess::startDetached("C:\\cygwin64\\bin\\mintty.exe",QStringList() << "/home/cyrin/convrt.sh");

                QDesktopServices::openUrl(QUrl::fromLocalFile(filename2));

            }
        }
    }
}

void MainWindow::on_Design3_clicked()
{
    Evenements E;
    QString value=ui->line_id_2->text(); //Declaration de la variable qui va contenir l'id saisi
    if (ui->line_id_2->text().isEmpty())
    {
        ui->erreur_nom_2->setText("Champ Obligatoire*");
    }
    else
    {
        ui->erreur_nom_2->setText("");
        QSqlQuery qry;
        qry.prepare("select * from evenements where id_ev='"+value+"'");            //Selectionner L'event avec le même ID
        if(qry.exec())
        {
            while(qry.next())
            {




                QString html =

                    "<body background=':/images/images/Design33.png'style=' background-repeat: no-repeat;'>"

                    "<br><br><br><br><br><br>"
                    "<div align =right>"
                    "<span style='font-size:25px;font-family:Monotype Corsiva,serif;color:white; margin-right:100px;font-weight:bold' >"+qry.value(4).toString()+"</span>"
                    "</div>"
                    "<br><br><br>"
                    "<div align =right>"
                    "<span style='font-size:20px;font-family:Monotype Corsiva,serif;color:white; margin-right:100px;font-weight:bold'>"+qry.value(5).toString()+"</span>"
                    "</div>"
                    "<br><br><br><br>"

                    "<span style='font-size:28px;font-family:Monotype Corsiva,serif;color:black;'><i>"+qry.value(1).toString()+"</i></span>"

                    "<br><br><br><br><br><br><br><br>"

                    "<span style='font-size:15px;color:white;'><i>"+qry.value(3).toString()+"</i></span>"
                    "<br><br><br><br><br><br><br><br><br>"
                    "<div align =right>"
                    "<span  style='font-size:15px;color:black;'>"+qry.value(2).toString()+"</span>"
                    "<span  style='font-size:15px;color:black;'>, "+qry.value(6).toString()+"</span>"
                    " </div>"
                    "<br><br><br>"
                    "<div align =left>"
                    "<img src =':/images/images/sante.jpg'>"
                    " </div>"




                    "<body>";

                QTextDocument document;
                document.setHtml(html);
                const QString filename("C:/cygwin64/home/cyrin/Design.pdf");




                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                //printer.setOrientation(QPrinter::Landscape);

                printer.setOutputFileName(filename);
                printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                document.print(&printer);



                QProcess::startDetached("C:\\cygwin64\\bin\\mintty.exe",QStringList() << "/home/cyrin/convrt.sh");
                const QString filename2("C:/cygwin64/home/cyrin/Affiche-1.png");
                QDesktopServices::openUrl(QUrl::fromLocalFile(filename2));

            }
        }
    }
}




void MainWindow::on_calendarWidgett_clicked(const QDate &date)
{

    QDate datet;
    datet=date;

    QSqlQuery qry;

    //qry.prepare("select * from evenements where DATE_DEB= ? ");
    qry.prepare("select * from evenements ");
    //qry.addBindValue(datet);
    if(qry.exec())
    {
        while(qry.next())
        {
            //Remplir tous les champs par les données concernées
datet=date;
if(qry.value(5).toDate()==datet)
{
            ui->nom_cal->setText(qry.value(1).toString());
            ui->type_cal->setText(qry.value(4).toString());
            ui->date_cal->setText(qry.value(5).toString());
            ui->ville_cal->setText(qry.value(2).toString());
            ui->code_cal->setText(qry.value(6).toString());
            ui->desc_cal->setText(qry.value(3).toString());
}//fin if
}//fin while
}//fin if qry
}//fin fnt



void MainWindow::on_tabWidget_currentChanged(int index)
{
    QDate datet;
    QSqlQuery qry;
    QTextCharFormat formattt ;
    formattt.setForeground(QBrush(Qt::white, Qt::SolidPattern));

    qry.prepare("select * from evenements");
    if(qry.exec())
    {
        while(qry.next())
        {
            datet=qry.value(5).toDate();
            ui->calendarWidgett->setDateTextFormat(datet, formattt);


        }
    }
}

void MainWindow::done2()

{

    QPushButton* button = qobject_cast<QPushButton*>(sender());

    QSqlQuery query;

    query.prepare("delete from todo where content=:c");

    query.bindValue(":c",button->text());

    query.exec();

    delete button;



}



void MainWindow::done()

{

    QPushButton* button = qobject_cast<QPushButton*>(sender());

    ui->v3->addWidget(button);

    QObject::connect( button, &QPushButton::clicked,this, &MainWindow::done2);

    QSqlQuery query;

    query.prepare("update todo set type=2 where content=:c");

    query.bindValue(":c",button->text());

    query.exec();

}

void MainWindow::inprogress()
{

    QPushButton* button = qobject_cast<QPushButton*>(sender());

    ui->v2->addWidget(button);

    QObject::connect( button, &QPushButton::clicked,this, &MainWindow::done);

    QSqlQuery query;

    query.prepare("update todo set type=1 where content=:c");

    query.bindValue(":c",button->text());

    query.exec();

}



void MainWindow::ajouttodo()

{

    QPushButton *b = new QPushButton(ui->L1->text());

    b->setStyleSheet("QPushButton {background-color:rgb(255, 167, 167);font-size: 14px;font: 12pt 'Century Gothic';border: 1px solid grey; }");

    ui->v1->addWidget(b);

    QObject::connect( b, &QPushButton::clicked,this, &MainWindow::inprogress);

    QSqlQuery query;

    query.prepare("insert into todo (content,type) values (:c,0)");

    query.bindValue(":c",ui->L1->text());

    query.exec();

}



void MainWindow::load()

{

    QSqlQuery query;

    query.prepare("select * from todo");

    if(query.exec())

    {

        while(query.next())

        {

            if(query.value(1).toInt()==0)

            {

                QPushButton *b = new QPushButton(query.value(0).toString());

                b->setStyleSheet("QPushButton {background-color:rgb(255, 167, 167);font-size: 14px;font: 12pt 'Century Gothic';border: 1px solid grey; }");

                ui->v1->addWidget(b);

                QObject::connect( b, &QPushButton::clicked,this, &MainWindow::inprogress);

            }

            if(query.value(1).toInt()==1)

            {

                QPushButton *b = new QPushButton(query.value(0).toString());

                b->setStyleSheet("QPushButton {background-color:rgb(255, 167, 167);font-size: 14px;font: 12pt 'Century Gothic';border: 1px solid grey; }");
                ui->v2->addWidget(b);

                QObject::connect( b, &QPushButton::clicked,this, &MainWindow::done);

            }

            if(query.value(1).toInt()==2)

            {

                QPushButton *b = new QPushButton(query.value(0).toString());

                b->setStyleSheet("QPushButton {background-color:rgb(255, 167, 167);font-size: 14px;font: 12pt 'Century Gothic';border: 1px solid grey; }");

                ui->v3->addWidget(b);

                QObject::connect( b, &QPushButton::clicked,this, &MainWindow::done2);

            }



        }

    }

}





void MainWindow::on_b1_clicked()
{
    ajouttodo();
}

void MainWindow::on_tri_id_clicked()
{
    Evenements E;
    if(ui->Tri_Croissant->isChecked())
   { ui->tableView->setModel(E.afficher_Tri(0));}
    else if(ui->Tri_Decroissant->isChecked())
    { ui->tableView->setModel(E.afficher_Tri(1));}
}

void MainWindow::on_Nom_id_clicked()
{
    Evenements E;
    if(ui->Tri_Croissant->isChecked())

    ui->tableView->setModel(E.afficher_Tri2(0));

    else if(ui->Tri_Decroissant->isChecked())

    { ui->tableView->setModel(E.afficher_Tri2(1));}
}

void MainWindow::on_Date_tri_clicked()
{
    Evenements E;
    if(ui->Tri_Croissant->isChecked())

    ui->tableView->setModel(E.afficher_Tri3(0));

    else if(ui->Tri_Decroissant->isChecked())

    { ui->tableView->setModel(E.afficher_Tri3(1));}
}
