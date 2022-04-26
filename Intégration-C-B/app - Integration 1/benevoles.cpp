#include "benevoles.h"
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>


bool benevoles::ajouter()
{
  QSqlQuery query;

  //prepare() prend la requete en paramètre à l'exécution

    query.prepare("insert into benevoles (NOM,PRENOM,DATE_NAISSANCE,ADRESSE,TELEPHONE,EMAIL) values(:NOM,:PRENOM,:DATE_NAISSANCE,:ADRESSE,:TELEPHONE,:EMAIL)");

  //Création des variables liées

    query.bindValue(":DATE_NAISSANCE",date_naissance);
    query.bindValue(":NOM",nom);
    query.bindValue(":PRENOM",prenom);
    query.bindValue(":ADRESSE",adresse);
    query.bindValue(":TELEPHONE",tel);
    query.bindValue(":EMAIL",email);

    return query.exec(); //exec envoie la requete pour l'exécuter
}


QSqlQueryModel * benevoles::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from benevoles");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_BE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TELEPHONE"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("EMAIL"));


    qDebug()<< model;

    return model;
}


bool benevoles::supprimer()
{
    QSqlQuery query;

        query.prepare("delete from benevoles where id_be=:id");
        query.bindValue(":id",id_be);

        return query.exec();
}

bool benevoles::modifier()
{
    QSqlQuery query;
    query.prepare("update benevoles set NOM=:nom,PRENOM=:prenom,DATE_NAISSANCE=:date_naissance,ADRESSE=:adresse,TELEPHONE=:tel,EMAIL=:email where id_be=:id");
      query.bindValue(":date_naissance",date_naissance);
      query.bindValue(":nom",nom);
      query.bindValue(":prenom",prenom);
      query.bindValue(":adresse",adresse);
      query.bindValue(":tel",tel);
      query.bindValue(":email",email);
      query.bindValue(":id",id_be);

      return query.exec();
  }

    QSqlQueryModel* benevoles::chercher(QString value)
    {
       QSqlQueryModel* model = new QSqlQueryModel();

        model->setQuery("SELECT * FROM BENEVOLES WHERE NOM like '%"+value+"%' or prenom like '%"+value+"%' or email like '%"+value+"%'");

        return model ;
}

    void benevoles::generer()
    {
         QSqlQuery qry;
         qry.prepare("SELECT * FROM benevoles");
         if(qry.exec())
         {
             QFile file("C:/Users/Saidi Essyl/Desktop/app - Integration 1/Fichier_Excel/Benevoles.xls");
                   file.open(QIODevice::WriteOnly | QIODevice::Text);
                   QTextStream out(&file);

             while(qry.next())
             {
                 out << qry.value(0).toInt() << "," << qry.value(1).toString()<< "," << qry.value(2).toString()<< "," << qry.value(3).toString()<< "," << qry.value(4).toString()<< "," << qry.value(5).toString()<< "," << qry.value(6).toString()<< "," << qry.value(7).toString() << "\n" ;


             }
         }


    }

    QSqlQueryModel* benevoles::trier(QString critere)
    {

        QSqlQueryModel *modal= new QSqlQueryModel();
        if (critere != "Choisir")
        {
            if(critere =="Nom")
                modal ->setQuery("select * from benevoles order by nom");
            else if (critere=="ID")
                modal ->setQuery("select * from benevoles order by id_be");
            else if (critere=="Prénom")
                modal ->setQuery("select * from benevoles order by prenom");
            return modal;
        }

    }

    bool benevoles::evaluer(int evaluation)
    {
            QSqlQuery query;
            QString res = QString::number(evaluation);
            //QString res2 = QString::number(id);
            query.prepare("update benevoles set EVALUATION = :review WHERE ID_BE = :id");
                query.bindValue(":id",id_be);
                query.bindValue(":review",evaluation);

            return  query.exec();
    }


    QChartView * benevoles::stat()
    {
        int one = 0;
        int two = 0;
        int three = 0;
        int four = 0;
        int five = 0;

        QSqlQuery query,query2,query3,query4,query5;
        query.prepare("SELECT * FROM BENEVOLES where EVALUATION=1");
        query.exec();

        query2.prepare("SELECT * FROM BENEVOLES where EVALUATION=2");
        query2.exec();

        query3.prepare("SELECT * FROM BENEVOLES where EVALUATION=3");
        query3.exec();

        query4.prepare("SELECT * FROM BENEVOLES where EVALUATION=4");
        query4.exec();

        query5.prepare("SELECT * FROM BENEVOLES where EVALUATION=5");
        query5.exec();

        while(query.next())
            one++;

        while(query2.next())
            two++;

        while(query3.next())
            three++;

        while(query4.next())
            four++;

        while(query5.next())
            five++;


        QPieSeries *series = new QPieSeries();
        series->append("1 ", one);
        series->append("2 ", two);
        series->append("3 ", three);
        series->append("4 ", four);
        series->append("5 ", five);
QPieSlice *slice = series->slices().at(0);

slice->setColor("#D46A6A");
QPieSlice *slice2 = series->slices().at(1);

slice2->setColor("#bb3636");
QPieSlice *slice3 = series->slices().at(2);

slice3->setColor("#c94242");
QPieSlice *slice4 = series->slices().at(3);

slice4->setColor("#ce5656");
QPieSlice *slice5 = series->slices().at(4);

slice5->setColor("#bb3636");

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("statistique sur les evaluations des benevoles");
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->legend()->setBackgroundVisible(true);
        chart->legend()->setBrush(QBrush(QColor(0,31,38,1)));
        chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));
        chart->legend()->setColor(QColor(212, 106, 106, 1));
        series->setLabelsVisible();

        QChartView*chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing,true);

        return chartView;
    }

