#include "mainwindow.h"
#include "ui_mainwindow.h"
//Essyl
#include "crises.h"
#include "piechart.h"
#include "arduino.h"
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

void MainWindow::on_pushButtonc_ajouter_clicked()
{
//Recuperration des informations saisies dans les champs

    QString nom=ui->lineEdit_nom->text();
    QString adresse=ui->lineEdit_Adresse->toPlainText();
    QString latitude=ui->lineEdit_la->text();
    QString longitude=ui->lineEdit_lo->text();
    QString description=ui->lineEdit_description_2->toPlainText();
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
        ui->tableViewc->setModel(Cr.afficher());
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



void MainWindow::on_tableViewc_activated(const QModelIndex &index)
{
    QString la,lo;
     QString value=ui->tableView->model()->data(index).toString();
      QQuickItem *item7 = ui->quickWidget->rootObject();
      QObject *object = item7->findChild<QObject *>("indicateurPosition");


             connection c;
             c.closeconnection();
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

void MainWindow::on_pushButton_PDFc_clicked()
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
