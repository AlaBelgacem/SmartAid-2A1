#include "mainwindow.h"
#include "dons.h"
#include "categories.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPixmap>
#include <QMovie>
#include <QDebug>
#include <QMessageBox>
#include "connection.h"
#include <QPainter>
#include <QPrinter>
#include <QDir>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(Etmp.afficher());
    ui->tableView_2->setModel(Cat.afficherC());
    //controle de saisie des id montant quatite
    ui->lineEdit_id->setValidator(new QIntValidator (0,99999999,this));
    ui->lineEdit_mt->setValidator(new QDoubleValidator(0.0, 99999999.99999999, 5,this));
    ui->lineEdit_qut->setValidator(new QIntValidator (0,99999999,this));
    ui->lineEdit_id_8->setValidator(new QIntValidator (0,99999999,this));
    ui->lineEdit_mt_8->setValidator(new QDoubleValidator(0.0, 99999999.99999999, 5,this));
    ui->lineEdit_qut_8->setValidator(new QIntValidator (0,99999999,this));

    QPixmap pix(":/images/images/copy.jpg");
    //ui->user_pic->setPixmap(pix.scaled(501,451,Qt::KeepAspectRatio));
    // Load animated GIF

    QLabel label;
    QMovie *movie = new QMovie(":/images/images/646-walking-walkcycle-person-outline.gif");
    QMovie *gif_don = new QMovie(":/images/images/add don.gif");
    ui->user_pic->setMovie(movie);
    ui->gif_don->setMovie(gif_don);
    movie->start();
    gif_don->start();
   QMovie *gif_cat = new QMovie(":/images/images/12-layers-flat.gif");
   ui->gif_don_2->setMovie(gif_cat);
   gif_cat->start();

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
    ui->tableView->setModel(Etmp.afficher());
    ui->tableView_2->setModel(Cat.afficherC());
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
//Recuperration des informations saisies dans les champs

    int id=ui->lineEdit_id->text().toInt();
    int id_cat=ui->lineEdit_idCategorie->text().toInt();
    QString nom=ui->lineEdit_nom->text();
    QString description=ui->lineEdit_description->text();
    QString montant=ui->lineEdit_mt->text();
    int quantite=ui->lineEdit_qut->text().toInt();



    Dons D(id,nom,description,montant,quantite,id_cat);
    bool test=D.ajouter();


    if(nom.isEmpty() || description.isEmpty() || id==0 ){
        QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides (ID,Nom ou Description)."),QMessageBox::Cancel);

    }
    else if(test)
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                QObject::tr("Ajout effectué\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
        //clear des donnees apres ajout
        ui->lineEdit_id->clear();
        ui->lineEdit_idCategorie->clear();
        ui->lineEdit_nom->clear();
        ui->lineEdit_description->clear();
        ui->lineEdit_mt->clear();
        ui->lineEdit_qut->clear();
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                             QObject::tr("Ajout non effectué.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
}





void MainWindow::on_pushButton_supprimer_clicked()
{
    int id=ui->lineEdit_id_8->text().toInt();
        bool test=Etmp.supprimer(id);

        if(id==0 ){
            QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides (ID,Nom ou Description)."),QMessageBox::Cancel);

        }
        else if (test)
        {
            ui->tableView->setModel(Etmp.afficher());
            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject ::tr("suppression effectuée \n"
                                                  "click cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_id_8->clear();
            ui->lineEdit_id_categorie->clear();
            ui->lineEdit_nom_8->clear();
            ui->lineEdit_description_8->clear();
            ui->lineEdit_mt_8->clear();
            ui->lineEdit_qut_8->clear();

        }
        else
            QMessageBox::critical(nullptr, QObject :: tr ("Not OK"),
                                  QObject ::tr("suppression non effectuée.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);


}


void MainWindow::on_pushButton_modifier_clicked()
{
    int id=ui->lineEdit_id_8->text().toInt();
    QString nom=ui->lineEdit_nom_8->text();
    QString description=ui->lineEdit_description_8->text();
    QString montant=ui->lineEdit_mt_8->text();
    int quantite=ui->lineEdit_qut_8->text().toInt();

    bool test = Etmp.modifier(id,nom,description,montant,quantite);

    if (test)
    {
        ui->tableView->setModel(Etmp.afficher());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject ::tr("modification effectuée \n"
                                              "click cancel to exit."), QMessageBox::Cancel);
                 ui->lineEdit_id_8->clear();
                 ui->lineEdit_nom_8->clear();
                 ui->lineEdit_description_8->clear();
                 ui->lineEdit_mt_8->clear();
                 ui->lineEdit_qut_8->clear();


    }
    else
        QMessageBox::critical(nullptr, QObject :: tr ("Not OK"),
                              QObject ::tr("modification non effectuée.\n"
                                      "click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString value=ui->tableView->model()->data(index).toString();
                 connection c;
                 c.closeconnection();
                 QSqlQuery qry;

                 qry.prepare("select ID_DON , NOM_DON, DESCRIPTION_DON ,MONTANT_DON ,QUANTITE_DON   from DONS  where ID_DON='"+value+"'");
                 if(qry.exec())
                 {
                     while(qry.next()){
                        ui->lineEdit_id_8->setText(qry.value(0).toString());
                        ui->lineEdit_nom_8->setText(qry.value(1).toString());
                        ui->lineEdit_description_8->setText(qry.value(2).toString());
                        ui->lineEdit_mt_8->setText(qry.value(3).toString());
                        ui->lineEdit_qut_8->setText(qry.value(4).toString());

                     }

                 }
}

void MainWindow::on_pushButton_ajouter_c_clicked()
{
    //Recuperration des informations saisies dans les champs

        int idC=ui->lineEdit_id_ca->text().toInt();
        QString nomC=ui->lineEdit_nom_ca->text();
        QString descriptionC=ui->lineEdit_description_ca->text();



        Categories C(idC,nomC,descriptionC);
        bool test=C.ajouterC();


        if(nomC.isEmpty() || descriptionC.isEmpty() || idC==0 ){
            QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides (ID,Nom ou Description)."),QMessageBox::Cancel);

        }
        else if(test)
        {
            ui->tableView_2->setModel(Cat.afficherC());
            QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Ajout effectué\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
            //clear des donnees apres ajout
            ui->lineEdit_id_ca->clear();
            ui->lineEdit_nom_ca->clear();
            ui->lineEdit_description_ca->clear();
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                 QObject::tr("Ajout non effectué.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_modifier_c_clicked()
{
    int idC=ui->lineEdit_id_c->text().toInt();
    QString nomC=ui->lineEdit_nom_c->text();
    QString descriptionC=ui->lineEdit_description_c->text();


    bool test = Cat.modifierC(idC,nomC,descriptionC);

    if (test)
    {
        ui->tableView_2->setModel(Cat.afficherC());
        QMessageBox::information(nullptr,QObject::tr("OK"),
                                 QObject ::tr("modification effectuée \n"
                                              "click cancel to exit."), QMessageBox::Cancel);
                 ui->lineEdit_id_c->clear();
                 ui->lineEdit_nom_c->clear();
                 ui->lineEdit_description_c->clear();

    }
    else
        QMessageBox::critical(nullptr, QObject :: tr ("Not OK"),
                              QObject ::tr("modification non effectuée.\n"
                                      "click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_pushButton_supprimer_c_clicked()
{
    int idC=ui->lineEdit_id_c->text().toInt();
        bool test=Cat.supprimerC(idC);

        if(idC==0 ){
            QMessageBox::critical(0,qApp->tr("erreur"),qApp->tr("veillez remplir les champs vides (ID,Nom ou Description)."),QMessageBox::Cancel);

        }
        else if (test)
        {
            ui->tableView_2->setModel(Cat.afficherC());
            QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject ::tr("suppression effectuée \n"
                                                  "click cancel to exit."), QMessageBox::Cancel);
            ui->lineEdit_id_c->clear();
            ui->lineEdit_nom_c->clear();
            ui->lineEdit_description_c->clear();

        }
        else
            QMessageBox::critical(nullptr, QObject :: tr ("Not OK"),
                                  QObject ::tr("suppression non effectuée.\n"
                                          "click cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    QString value=ui->tableView_2->model()->data(index).toString();
                 connection c;
                 c.closeconnection();
                 QSqlQuery qry;

                 qry.prepare("select ID_CAT , NOM, DESCRIPTION  from CATEGORIES  where ID_CAT='"+value+"'");
                 if(qry.exec())
                 {
                     while(qry.next()){
                        ui->lineEdit_id_c->setText(qry.value(0).toString());
                        ui->lineEdit_nom_c->setText(qry.value(1).toString());
                        ui->lineEdit_description_c->setText(qry.value(2).toString());

                        //send the cat ID to lineedit in ajouter dons
                        ui->lineEdit_idCategorie->setText(qry.value(0).toString());

                     }

                 }
}

void MainWindow::on_lineEdit_recherche_textChanged(const QString &arg1)
{
    //QString str=ui->lineEdit_recherche->text();
    ui->tableView->setModel(Etmp.chercher(arg1));
}

void MainWindow::on_lineEdit_recherche_c_textChanged(const QString &arg1)
{
    //QString str=ui->lineEdit_recherche_c->text();
    ui->tableView_2->setModel(Cat.rechercher(arg1));
}

void MainWindow::on_radioButton_C_clicked()
{
    QString croissance=ui->radioButton_C->text();
    ui->tableView->setModel(Etmp.trierC(croissance));
}

void MainWindow::on_radioButton_D_clicked()
{
    QString croissance=ui->radioButton_D->text();
    ui->tableView->setModel(Etmp.trierD(croissance));
}

void MainWindow::on_radioButton_C_c_clicked()
{
    QString croissance=ui->radioButton_C_c->text();
    ui->tableView_2->setModel(Cat.triC(croissance));
}


void MainWindow::on_radioButton_D_c_clicked()
{
    QString croissance=ui->radioButton_C_c->text();
    ui->tableView_2->setModel(Cat.triD(croissance));
}

void MainWindow::on_pushButton_PDF_clicked()
{
    QModelIndex index = ui->tableView->currentIndex(); ;

        QString PDF=QDir::currentPath()+"/"+ui->tableView->model()->index(index.row(),0).data().toString()+"_dons.pdf";
        qDebug ()<< PDF;
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(PDF);

        QPainter painter;

        if (!painter.begin(&printer))
        {
            qDebug() << "PDF inexistant";
            return;
        }

        painter.drawPixmap(25,25,QPixmap(":/icons/icons/icone.png"));

        painter.setPen("#AB3A3A");
        painter.setFont(QFont("Lato_Bold", 25));
        painter.drawText(325,300,"Fiche De Don");

        painter.setPen("#801414");
        painter.setFont(QFont("Lato_Regular", 12));
        painter.drawText(25,500,"ID : "+ui->tableView->model()->index(index.row(),0).data().toString());
        painter.drawText(25,600,"Nom : "+ui->tableView->model()->index(index.row(),1).data().toString());
        painter.drawText(25,700,"Description : "+ui->tableView->model()->index(index.row(),2).data().toString());
        painter.drawText(25,800,"Montant : "+ui->tableView->model()->index(index.row(),3).data().toString());
        painter.drawText(25,900,"Quantite : "+ui->tableView->model()->index(index.row(),4).data().toString());
        painter.end();
}

void MainWindow::on_pushButton_PDF_c_clicked()
{
    QModelIndex index = ui->tableView_2->currentIndex(); ;

        QString PDF=QDir::currentPath()+"/"+ui->tableView_2->model()->index(index.row(),0).data().toString()+"_catégories.pdf";
        qDebug ()<< PDF;
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(PDF);

        QPainter painter;

        if (!painter.begin(&printer))
        {
            qDebug() << "PDF inexistant";
            return;
        }

        painter.drawPixmap(25,25,QPixmap(":/icons/icons/icone.png"));

        painter.setPen("#AB3A3A");
        painter.setFont(QFont("Lato_Bold", 25));
        painter.drawText(325,300,"Fiche De Catégorie");

        painter.setPen("#801414");
        painter.setFont(QFont("Lato_Regular", 12));
        painter.drawText(25,500,"ID : "+ui->tableView_2->model()->index(index.row(),0).data().toString());
        painter.drawText(25,600,"Nom : "+ui->tableView_2->model()->index(index.row(),1).data().toString());
        painter.drawText(25,700,"Description : "+ui->tableView_2->model()->index(index.row(),2).data().toString());

        painter.end();
}

void MainWindow::on_tabstat_tabBarClicked(int index)
{
    QTableView table1,table2;
       QSqlQueryModel * Mod=new  QSqlQueryModel();
       QSqlQueryModel * Mod2=new  QSqlQueryModel();
            connection c;
            QSqlQuery qry,q2;
            qry.prepare("select NOM_DON from DONS");
            qry.exec();
            Mod->setQuery(qry);
            table1.setModel(Mod);

            q2.prepare("select AVG(QUANTITE_DON) from DONS group by NOM_DON");

            q2.exec();
            Mod2->setQuery(q2);
            table2.setModel(Mod2);

            c.closeconnection();

           qDebug()<<table1.model()->data(table1.model()->index(0, 0)).toString().simplified();
           qDebug()<<table2.model()->data(table2.model()->index(0, 0)).toInt();

           const int rowCount = table1.model()->rowCount();
           const int rowCount2 = table2.model()->rowCount();

       if(index==4){

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

           besoin->setName("Nom Dons");
           besoin->setPen(QPen(QColor("#D5E7F2").lighter(130)));
           besoin->setBrush(QColor("#D5E7F2"));
           // stack bars on top of each other:


           // prepare x axis with needs' labels:
           QVector<double> ticks;
           QVector<QString> labels;

           for(int i=0; i<rowCount; ++i){
               ticks.push_back(i);
               labels.push_back(table1.model()->data(table1.model()->index(i, 0)).toString().simplified());
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
           ui->customPlot->yAxis->setLabel("Quantite\n par Dons");
           ui->customPlot->yAxis->setBasePen(QPen(Qt::black));
           ui->customPlot->yAxis->setTickPen(QPen(Qt::black));
           ui->customPlot->yAxis->setSubTickPen(QPen(Qt::black));
           ui->customPlot->yAxis->grid()->setSubGridVisible(true);
           ui->customPlot->yAxis->setTickLabelColor(Qt::black);
           ui->customPlot->yAxis->setLabelColor(Qt::black);
           ui->customPlot->yAxis->grid()->setPen(QPen(QColor("#000"), 0, Qt::SolidLine));
           ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor("#000"), 0, Qt::DotLine));

           // Add data:
           QVector<double>categData;

           for(int i=0; i<rowCount2; ++i){
               categData.push_back(table2.model()->data(table2.model()->index(i, 0)).toInt());
               qDebug()<<categData;

           }

           besoin->setData(ticks, categData);

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
