#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include "necessiteux.h"
#include <QListView>
#include "qrcodegen.hpp"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     ui->tableN->setModel(N.afficher());
     ui->tableRdv->setModel(rdv.afficher());

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
    QString selectedvalue= item->text();

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
