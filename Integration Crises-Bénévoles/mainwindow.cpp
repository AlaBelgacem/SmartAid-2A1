#include "mainwindow.h"
#include "ui_mainwindow.h"
//Essyl
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
//Salma
#include "benevoles.h"
#include "connection.h"
#include <fstream>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include "messenger.h"
#include <QTcpSocket>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent) :
      QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //controle saisie salma
    ui->tel->setValidator(new QIntValidator (0,99999999,this));
    ui->nom->setValidator(new QRegExpValidator(  QRegExp("[A-z]*")  ));
    ui->prenom->setValidator(new QRegExpValidator(  QRegExp("[A-z]*")  ));
    ui->email->setValidator(new QRegExpValidator(  QRegExp("[a-z]{1,10}@[a-z]{1,4}\\.[a-z]{1,4}")  ));


    int ret=A.connect_arduino();
    switch(ret){
    case(0):qDebug() <<"arduino is available and connected to:" <<A.getarduino_port_name();
        break;
    case(1):qDebug() <<"arduino is available but not connected to:" <<A.getarduino_port_name();
    break;
    case(-1):qDebug() <<"arduino is not available";
    }

    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));



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
    ui->tableView_2->setModel(Be.afficher());

    ui->verticalLayout->addWidget(Be.stat());

        mSocket=new QTcpSocket(this);
        connect(mSocket,&QTcpSocket::readyRead,[&]()
        { QTextStream T(mSocket);
           auto text = T.readAll();
           ui->textEdit->append(text);});

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

    setWindowTitle("Géolocaliser Crises");
    show();
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


//Essyl

void MainWindow::on_pushButton_ajouter_clicked()
{
//Recuperration des informations saisies dans les champs

    QString nom=ui->lineEdit_nom->text();
    QString adresse=ui->lineEdit_Adresse->toPlainText();
    QString latitude=ui->lineEdit_la->text();
    QString longitude=ui->lineEdit_lo->text();
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

    Crises C(nom,adresse,niveau,description,date_cr,etat,latitude,longitude);


    if(nom.isEmpty() || adresse.isEmpty() || description.isEmpty()|| date_cr.isEmpty() || etat.isEmpty() || latitude.isEmpty() ||longitude.isEmpty())
    {
    QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("Veuillez remplir les champs vides"),QMessageBox::Cancel);
    }
   else {
        C.ajouter();
        //refresh
        ui->tableView->setModel(Cr.afficher());
        ui->statlabel->setText(QString::number(Cr.etatT()));
        ui->statlabel_2->setText(QString::number(Cr.etatEC()));
        ui->statlabel_3->setText(QString::number(Cr.etatNT()));
        QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

        ui->lineEdit_nom->clear();
        ui->lineEdit_Adresse->clear();
        ui->lineEdit_lo->clear();
        ui->lineEdit_la->clear();
        ui->lineEdit_description->clear();
        ui->dateEdit_datec->clear();
        ui->lineEdit_la->clear();
        ui->lineEdit_lo->clear();
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
         ui->statlabel->setText(QString::number(Cr.etatT()));
         ui->statlabel_2->setText(QString::number(Cr.etatEC()));
         ui->statlabel_3->setText(QString::number(Cr.etatNT()));
         QMessageBox::information(nullptr, QObject::tr("OK"),
                 QObject::tr("Suppression effectuée\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);


         ui->lineEdit_ID_mod->clear();
         ui->lineEdit_nom_mod->clear();
         ui->lineEdit_Adresse_mod->clear();
         ui->lineEdit_description_mod->clear();
         ui->dateEdit_datec_mod->clear();
         ui->lineEdit_etat->clear();
         ui->lineEdit_la_mod->clear();
         ui->lineEdit_lo_mod->clear();
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
    QString latitude=ui->lineEdit_la_mod->text();
    QString longitude=ui->lineEdit_lo_mod->text();

   bool test =Cr.modifier(id,nom,adresse,niveau,description,date_cr,etat,latitude,longitude);

    if(test)
    {

        //refresh
        ui->tableView->setModel(Cr.afficher());
        ui->statlabel->setText(QString::number(Cr.etatT()));
        ui->statlabel_2->setText(QString::number(Cr.etatEC()));
        ui->statlabel_3->setText(QString::number(Cr.etatNT()));
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
        ui->lineEdit_la_mod->clear();
        ui->lineEdit_lo_mod->clear();

    }
    else         QMessageBox::critical  (nullptr, QObject::tr("not OK"),
                 QObject::tr("update non effectué\n"
                             "Click to Cancel."), QMessageBox::Cancel);
}



void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString la,lo;
     QString value=ui->tableView->model()->data(index).toString();
      QQuickItem *item7 = ui->quickWidget->rootObject();
      QObject *object = item7->findChild<QObject *>("indicateurPosition");


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
                    ui->lineEdit_la_mod->setText(qry.value(7).toString());
                    ui->lineEdit_lo_mod->setText(qry.value(8).toString());
                    la = qry.value(7).toString();
                    lo = qry.value(8).toString();


                 }

             }

             afficherPosition(la,lo);
             QVariant latitude = la;
             QVariant longitude = lo;
             QMetaObject::invokeMethod(object, "aller", Q_ARG(QVariant, latitude), Q_ARG(QVariant, longitude));

}


void MainWindow::on_lineEditRecherche_textChanged(const QString &arg1)
{
    QString str=ui->lineEditRecherche->text();
    ui->tableView->setModel(Cr.rechercher(str));
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

void MainWindow::on_pushButton_PDF_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();

    //QString PDF=QDir::currentPath()+"/"+ui->tableView->model()->index(index.row(),0).data().toString()+"_crise.pdf";

    const QString PDF="C:/Users/Saidi Essyl/Desktop/app/Fiche_Crises/"+ui->tableView->model()->index(index.row(),0).data().toString()+"_crise.pdf";
    //QPdfWriter pdfwriter(PDF);
    //pdfwriter.setPageSize(QPageSize(QPageSize::A4));
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(PDF);
    qDebug() << PDF;
    QPainter painter;

    if (!painter.begin(&printer))
    {
        qDebug() << "Impossible d'ouvrir le fichier PDF";
        return;
    }


    painter.setPen("#550000");
    painter.drawRect(0, 0, 955, 1365);

    painter.drawPixmap(25,25,QPixmap(":/icons/icons/icone.png"));

    painter.setPen("#AB3A3A");
    painter.setFont(QFont("Lato_Bold", 25));
    painter.drawText(325,300,"Fiche De Crise");

    painter.setPen("#801414");
    painter.setFont(QFont("Lato_Regular", 12));
    painter.drawText(25,500,"ID : "+ui->tableView->model()->index(index.row(),0).data().toString());
    painter.drawText(25,600,"Nom : "+ui->tableView->model()->index(index.row(),1).data().toString());
    painter.drawText(25,700,"Adresse : "+ui->tableView->model()->index(index.row(),2).data().toString());
    painter.drawText(25,800,"Niveau : "+ui->tableView->model()->index(index.row(),3).data().toString());
    painter.drawText(25,900,"Description : "+ui->tableView->model()->index(index.row(),4).data().toString());
    painter.drawText(25,1000,"Date : "+ui->tableView->model()->index(index.row(),5).data().toString());
    painter.drawText(25,1100,"Etat : "+ui->tableView->model()->index(index.row(),6).data().toString());

    painter.setPen("#AB3A3A");
    painter.setFont(QFont("Lato_Light", 10));
    painter.drawText(25,1350,"Smart_Aid_Association");
    painter.drawText(925,1350,"1");

    qDebug() << "Le fichier PDF a été créer avec succés";

    painter.end();

}


void MainWindow::on_browseBtn_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );
}

void MainWindow::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message envoyé avec succès!\n\n" ) );
}


void MainWindow::on_boutonAller_clicked()
{
    QQuickItem *item7 = ui->quickWidget->rootObject();
    QObject *object = item7->findChild<QObject *>("indicateurPosition");
    QVariant latitude = ui->editLatitude->text();
    QVariant longitude = ui->editLongitude->text();

    if(object != nullptr)
    {
        qDebug() << Q_FUNC_INFO << latitude << longitude;
        QMetaObject::invokeMethod(object, "aller", Q_ARG(QVariant, latitude), Q_ARG(QVariant, longitude));
    }
}

void MainWindow::afficherPosition(QString latitude, QString longitude)
{
    qDebug() << Q_FUNC_INFO << latitude << longitude;
    ui->positionLatitude->setText(QString::fromUtf8("%1").arg(latitude.toDouble(), 0, 'f', 5));
    ui->positionLongitude->setText(QString::fromUtf8("%1").arg(longitude.toDouble(), 0, 'f', 5));
    ui->editLatitude->setText(QString::fromUtf8("%1").arg(latitude.toDouble(), 0, 'f', 5));
    ui->editLongitude->setText(QString::fromUtf8("%1").arg(longitude.toDouble(), 0, 'f', 5));
}

void MainWindow::afficherInformations(QString adresse, QString coordonnee)
{
    qDebug() << Q_FUNC_INFO << adresse << coordonnee;
    ui->labelInformations->setText("Informations : " + adresse);
}


//Salma

void MainWindow::on_pushButton_ajouter_2_clicked()
{
    benevoles b;//Instancier un objet de la classe benevoles

    //Récupération des informations saisies dans les 6 champs
    b.setNom(ui->nom->text());
    b.setPrenom(ui->prenom->text());
    b.setDateNaissance(ui->daten->text());
    b.setEmail(ui->email->text());
    b.setTel(ui->tel->text());
    b.setAdresse(ui->adresse->text());

    bool check=b.ajouter();//Insérer l'objet benevoles instancié dans la table benevoles
                           //et récupérer la valeur de retour de query.exec()
ui->tableView_2->setModel(b.afficher());
    if (check)//Si requete executée ==> QMessageBox::information
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else//Si requete non executée ==> QMessageBox::critical
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                     QObject::tr("Ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_actualiser_clicked()
{
     connection c;
        QSqlQueryModel *modal=new QSqlQueryModel();

        QSqlQuery *qry=new QSqlQuery(c.getdb());

        qry->prepare("select * from benevoles");

        qry->exec();

        modal->setQuery(*qry);

        ui->tableView_2->setModel(modal);
}

void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    QString value=ui->tableView_2->model()->data(index).toString();
          connection c;
         c.closeConnection();
         QSqlQuery qry;

         qry.prepare("select * from benevoles where id_be='"+value+"'");
         if(qry.exec())
         {
             while(qry.next())
             {
              ui->lineEdit_id->setText(qry.value(0).toString());
              ui->lineEdit_nom_2->setText(qry.value(1).toString());
              ui->lineEdit_prenom->setText(qry.value(2).toString());
              ui->lineEdit_date->setText(qry.value(3).toString());
              ui->lineEdit_ad->setText(qry.value(4).toString());
              ui->lineEdit_tel->setText(qry.value(5).toString());
              ui->lineEdit_email->setText(qry.value(6).toString());

             }

         }


}

void MainWindow::on_pushButton_supprimer_clicked()
{
    int id=ui->lineEdit_id->text().toInt();

        benevoles e;
        e.setId(id);
        bool check=e.supprimer();
        if(check)
        {
            QMessageBox::information(nullptr,QObject::tr("OK"),
                         QObject::tr("Suppression effectuée\n"
                                     "Click Cancel to exit ."),QMessageBox::Cancel);
        }
    else
        {
            QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                         QObject::tr("Suppression non effectué\n"
                                     "Click Cancel to exit."),QMessageBox::Cancel);
        }


}

void MainWindow::on_pushButton_modifier_clicked()
{
    benevoles b;
    b.setNom(ui->lineEdit_nom_2->text());
    b.setPrenom(ui->lineEdit_prenom->text());
    b.setDateNaissance(ui->lineEdit_date->text());
    b.setEmail(ui->lineEdit_email->text());
    b.setTel(ui->lineEdit_tel->text());
    b.setAdresse(ui->lineEdit_ad->text());
    b.setId(ui->lineEdit_id->text().toInt());

    bool check=b.modifier();
    ui->tableView_2->setModel(b.afficher());

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




void MainWindow::on_pushButton_3_clicked()
{
    QString nom = ui->lineEdit_chercher->text();
        ui->tableView_2->setModel(Be.chercher(nom));
}

void MainWindow::on_pushButton_clicked()
{
//using namespace std;
  //  ofstream Excel ;
    //Excel.open("test.csv");

    //Excel << "fdfgf" << endl ;
  benevoles Be ;
  Be.generer();
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    benevoles Be;

            ui->tableView_2->setModel(Be.trier(ui->comboBox->currentText()));
}

void MainWindow::on_evaluer_clicked()
{
    benevoles b;
     b.setId(ui->lineEdit_id->text().toInt());
    int evaluer = ui->comboBox_2->currentText().toInt();
    int id = ui->lineEdit_id->text().toInt();
    b.evaluer(evaluer);
    ui->tableView_2->setModel(b.afficher());
    qDebug()<<id<<evaluer;
}

void MainWindow::on_pb_envoyer_clicked()
{
    QTextStream T(mSocket);
    T<<ui->lineEdit_surnom->text()<<": "<<ui->lineEdit_mssage_2->text();
    mSocket->flush();
    ui->lineEdit_mssage_2->clear();
}

void MainWindow::on_pb_connecter_clicked()
{
    qDebug()<<"connecting to server ...";
    messenger D(this);

    if(D.exec() == QDialog::Rejected)
    {
        return;
    }
    mSocket->connectToHost(D.hostname(), D.port());
}





