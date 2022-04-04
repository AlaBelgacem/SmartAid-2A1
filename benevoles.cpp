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
             QFile file("C:/Users/salma/OneDrive/Documents/GitHub/SmartAid-2A1/BENEVOLES.xls");
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

    bool benevoles::evaluer(int evaluation, QString id)
    {
        QSqlQuery query;
            query.prepare("update BENEVOLES set EVALUATION = :review WHERE ID_BE = :id");
            query.bindValue(":ID_BE", id);
            query.bindValue(":review", evaluation);

            return  query.exec();
    }


    QChartView * benevoles::stat()
    {
        int OneStar = 0;
        int TwoStar = 0;
        int ThreeStar = 0;
        int FourStar = 0;
        int FiveStar = 0;

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
            OneStar++;

        while(query2.next())
            TwoStar++;

        while(query3.next())
            ThreeStar++;

        while(query4.next())
            FourStar++;

        while(query5.next())
            FiveStar++;


        //qDebug()<<row_count<<row_count1;
        //qDebug()<<row_count;

        QPieSeries *series = new QPieSeries();
        series->append("1 etoile", OneStar);
        series->append("2 etoile", TwoStar);
        series->append("3 etoile", ThreeStar);
        series->append("4 etoile", FourStar);
        series->append("5 etoile", FiveStar);

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("statistique sure les evaluations des benevoles");
        chart->legend()->setAlignment(Qt::AlignRight);
        chart->legend()->setBackgroundVisible(true);
        chart->legend()->setBrush(QBrush(QColor(0,31,38,1)));
        chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));
        series->setLabelsVisible();

        QChartView*chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing,true);

        return chartView;
    }

