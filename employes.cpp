#include "employes.h"
#include <QDebug>

bool Employes::Ajouter_em()
{
    QSqlQuery query;

    query.prepare("insert into employes (nom,prénom,téléphone,adresse,email,date_nai,image,type,sexe) values (:nom,:prenom,:tele,:adresse,:email,:date,:image,:type,:sexe)");

     query.bindValue(":nom",nom);
     query.bindValue(":prenom",prenom);
     query.bindValue(":date",date_nais);
     query.bindValue(":tele",telephone);
     query.bindValue(":adresse",Adresse);
     query.bindValue(":email",email);
     query.bindValue(":image",image);
     query.bindValue(":type",type);
     query.bindValue(":sexe",sexe);
     qDebug() << "22";
     return query.exec();

}

bool Employes::Ajouter_sa_em()
{
    QSqlQuery query;
    query.exec("SELECT MAX( id_em ) FROM employes;");
    query.next();
    QString id=query.value(0).toString();

    query.prepare("insert into salaires (id,salaire,nb_heures,disc,prime) values (:id,500,0,1,7)");
    query.bindValue(":id",id);
    return query.exec();
}

QSqlQueryModel *Employes::Afficher(int set)
{
     QSqlQueryModel *modal=new QSqlQueryModel();
     if(set == 1)
     {
         modal->setQuery("select * from employes where type='Employe'");
         modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_EM"));
         return modal;
     }
     if(set == 2)
     {
         modal->setQuery("select * from employes where type='User'");
         modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_EM"));
         return modal;
     }
     if(set == 3)
     {
         modal->setQuery("select * from employes");
         modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_EM"));
         return modal;
     }

}

bool Employes::Modifier_em()
{
    QSqlQuery query;
    query.prepare("update employes set nom=:nom,prénom=:prenom,téléphone=:tele,adresse=:ad,email=:email,date_nai=:date,image=:i,type=:t,sexe=:s where id_em=:id");
    query.bindValue(":id",id_em);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":date",date_nais);
    query.bindValue(":tele",telephone);
    query.bindValue(":ad",Adresse);
    query.bindValue(":email",email);
     query.bindValue(":i",image);
     query.bindValue(":t",type);
     query.bindValue(":s",sexe);
    return query.exec();
}

bool Employes::Supprimer_em()
{
    QSqlQuery query;
    query.prepare("delete from employes where id_em=:id");
    query.bindValue(":id",id_em);
    return query.exec();
}

QSqlQueryModel *Employes::Rechercher_em(QString value )
{
     QSqlQueryModel *modal=new QSqlQueryModel();
     modal->setQuery("select * from employes where nom like '%"+value+"%' or prénom like '%"+value+"%' or email like '%"+value+"%'");
     return modal;
}

QSqlQueryModel *Employes::Trier_em(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "ID" && croissance == "ASC")
        modal->setQuery("select * from employes order by ID_EM ASC ");
    else if(critere == "ID" && croissance == "DESC")
        modal->setQuery("select * from employes order by ID_EM DESC ");

    else if(critere == "Nom" && croissance == "ASC")
        modal->setQuery("select * from employes order by NOM ASC ");
    else if(critere == "Nom" && croissance == "DESC")
        modal->setQuery("select * from employes order by NOM DESC ");

    else if(critere == "Prenom" && croissance == "ASC")
        modal->setQuery("select * from employes order by prénom ASC ");
    else if(critere == "Prenom" && croissance == "DESC")
        modal->setQuery("select * from employes order by prénom DESC ");

    else if(critere == "Adresse" && croissance == "ASC")
        modal->setQuery("select * from employes order by ADRESSE ASC ");
    else if(critere == "Adresse" && croissance == "DESC")
        modal->setQuery("select * from employes order by ADRESSE DESC ");

    else if(critere == "Email" && croissance == "ASC")
        modal->setQuery("select * from employes order by email ASC ");
    else if(critere == "Email" && croissance == "DESC")
        modal->setQuery("select * from employes order by email DESC ");

    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from employes order by prénom");
    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from employes order by prénom");

    else if(critere == "Email" && croissance == "")
        modal->setQuery("select * from employes order by email");
    else if(critere == "Email" && croissance == "")
        modal->setQuery("select * from employes order by email");

    else if(critere == "Adresse" && croissance == "")
        modal->setQuery("select * from employes order by ADRESSE");
    else if(critere == "Adresse" && croissance == "")
        modal->setQuery("select * from employes order by ADRESSE");

    else if(critere == "ID" && croissance == "")
        modal->setQuery("select * from employes order by ID_EM");
    else if(critere == "ID" && croissance == "")
        modal->setQuery("select * from employes order by ID_EM");

    else if(critere == "Nom" && croissance == "")
        modal->setQuery("select * from employes order by NOM");
    else if(critere == "Nom" && croissance == "")
        modal->setQuery("select * from employes order by NOM");

    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from employes order by prénom");
    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from employes order by prénom");


    return  modal;
}

void Employes::Calculer_salaire()
{
    QSqlQuery qry,qryy;
    int id,salaire,nh,ne,disc,prime;
    float var=0;
    qry.prepare("select id,salaire,nb_heures,disc,nb_events,prime from salaires,bénévoles where salaires.id = bénévoles.id_e");
    if(qry.exec())
    {
        while(qry.next())
        {
            id=qry.value(0).toInt();
            salaire=qry.value(1).toInt();
            nh=qry.value(2).toInt();
            disc=qry.value(3).toInt();
            ne=qry.value(4).toInt();
            prime=qry.value(5).toInt();
            var = (((nh/10)*0.5) + (ne*0.5) + disc);
            prime = (salaire * var)/100;
            qDebug() << "id: " << id << " | salaire: " << salaire << " | nb heures: " << nh << " | disc : " << disc <<" | nb events: " << ne << " | prime:  " << prime << " | var:  " << var ;
            qryy.prepare("update salaires set prime=:pr where id=:id");
            qryy.bindValue(":pr",prime);
            qryy.bindValue(":id",id);
            qryy.exec();
        }
    }
}
QSqlQueryModel *Employes::Afficher_Salaire(int q)
{

    QSqlQueryModel *modal=new QSqlQueryModel();
    Calculer_salaire();
    if(q==1)
    modal->setQuery("select id_em,nom,prénom,nb_heures,nb_events,disc,salaire,prime from salaires,employes,bénévoles where salaires.id = employes.id_em and salaires.id = bénévoles.id_e");
    if(q==2)
    modal->setQuery("select id_em,nom,prénom,nb_heures,nb_events,disc,salaire,prime from salaires,employes,bénévoles where salaires.id = employes.id_em and salaires.id = bénévoles.id_e and employes.type='Employe'");

    modal->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    return modal;
}

bool Employes::Modifier_Salaire(int id,int salaire,int nh,int disc)
{
    QSqlQuery query;
    query.prepare("update salaires set salaire=:s,nb_heures=:nh,disc=:disc where id=:id");
    query.bindValue(":id",id);
    query.bindValue(":s",salaire);
    query.bindValue(":nh",nh);
    query.bindValue(":disc",disc);
    return query.exec();
}

bool Employes::check_phone(QString n)
{
    QSqlQuery query;
    query.prepare("select téléphone from employes where téléphone=:num and type=:ty");
    query.bindValue(":num",n);
    query.bindValue(":ty","User");
    query.exec();
    query.next();
    QString id=query.value(0).toString();
    if(id=="")
        return 0;
    else
        return 1;
}
 bool Employes::check_existance(QString mail , QString num)
{

         QSqlQuery query;
         query.prepare("select téléphone,email from employes where téléphone=:num or email:=e");
         query.bindValue(":num",num);
         query.bindValue(":e",mail);
         query.exec();
         query.next();
         QString id=query.value(0).toString();
         QString e=query.value(1).toString();
         if((id=="")||(e==""))
             return 0;
         else
             return 1;
}
bool Employes::add_be()
{
    QSqlQuery query;
    query.exec("SELECT MAX( id_em ) FROM employes;");
    query.next();
    QString id=query.value(0).toString();

    query.prepare("insert into bénévoles (id_e,nb_events) values (:id,1)");
    query.bindValue(":id",id);
    return query.exec();



}
  QChartView *Employes::stat_gender()
  {
      int homme=0;
      int femme=0;
      int autre=0;

      QSqlQuery query;
      query.prepare("select * from employes where sexe='Homme'");
      query.exec();

      while(query.next())
          homme++;

      query.prepare("select * from employes where sexe='Femme'");
      query.exec();

      while(query.next())
          femme++;

      query.prepare("select * from employes where sexe='Autre'");
      query.exec();

      while(query.next())
          autre++;

      qDebug() << homme << femme << autre ;

      QPieSeries *series = new QPieSeries();
          series->append("Homme", homme);
          series->append("Femme", femme);
          series->append("Autre", autre);

          QPieSlice *slice = series->slices().at(0);
          slice->setExploded(true);
          slice->setColor("#f55d11");
          QPieSlice *slice2 = series->slices().at(1);
          slice2->setColor("#ff8b52");
          QPieSlice *slice3 = series->slices().at(2);
          slice3->setColor("#e6a88a");

          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("Statistique du Sexe");

          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
 chartView->chart()->legend()->hide();
          return chartView;

  }
  QChartView *Employes::stat_age()
  {


      QSqlQuery query;
      int g1=0;
      int g2=0;
      int g3=0;

      query.prepare("select date_nai from employes");
      if(query.exec())
      {
          while(query.next())
          {
              QString dates =query.value(0).toString();
              QDate date = QDate::fromString(dates,"ddd MMM M yyyy");
              dates = date.toString("yyyy");
              int year = dates.toInt();

              if(((2022-year) >= 20) && ((2022-year) <= 30) )
              g1++;
              if(((2022-year) >= 30) && ((2022-year) <= 40) )
              g2++;
              if(((2022-year) >= 40) && ((2022-year) <= 50) )
              g3++;
          }

      }

      QPieSeries *series = new QPieSeries();
          series->append("20-30 ans", g1);
          series->append("30-40 ans", g2);
          series->append("40-50 ans", g3);

          QPieSlice *slice = series->slices().at(0);
          slice->setExploded(true);
          slice->setColor("#092cdb");
          QPieSlice *slice2 = series->slices().at(1);
          slice2->setColor("#4360f0");
          QPieSlice *slice3 = series->slices().at(2);
          slice3->setColor("#303a6e");
         /* series->setLabelsVisible();
          series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);
          for(auto slice : series->slices())
              slice->setLabel(QString("%1%").arg(100*slice->percentage(), 0, 'f', 1));*/

          QChart *chart = new QChart();
          chart->addSeries(series);
          chart->setTitle("Statistique d'Age");

          series->setLabelsVisible();

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
 chartView->chart()->legend()->hide();
          return chartView;

  }
QChartView *Employes::stat_age_gender()
{

    QSqlQuery query;
    int flous=0;
    //nombre 3bed men kol jens
    int h1=0;
    int h2=0;
    int h3=0;

    int f1=0;
    int f2=0;
    int f3=0;

    int a1=0;
    int a2=0;
    int a3=0;

    query.prepare("select id_em,date_nai,sexe,salaire,prime from salaires,employes where salaires.id = employes.id_em");
    if(query.exec())
    {
        while(query.next())
        {
            int id=query.value(0).toInt();
            QString sexe=query.value(2).toString();
            int salaire=query.value(3).toInt();
            int prime=query.value(4).toInt();
            QString dates =query.value(1).toString();
            QDate date = QDate::fromString(dates,"ddd MMM M yyyy");
            dates = date.toString("yyyy");
            int year = dates.toInt();
            qDebug() << id << year << sexe << salaire << prime << "\n" ;
            flous+=salaire+prime;
            if(((2022-year) >= 20) && ((2022-year) <= 30) )
            {
                if(sexe == "Homme")
                h1++;

                if(sexe == "Femme")
                f1++;

                if(sexe == "Autre")
                 a1++;

            }
            if(((2022-year) >= 30) && ((2022-year) <= 40) )
            {
                if(sexe == "Homme")
                h2++;

                if(sexe == "Femme")
                 f2++;

                if(sexe == "Autre")
                a2++;

            }
            if(((2022-year) >= 40) && ((2022-year) <= 50) )
            {
                if(sexe == "Homme")
                h3++;

                if(sexe == "Femme")
                f3++;

                if(sexe == "Autre")
                a3++;

            }



        }

    }

    QBarSet *set1 = new QBarSet("Homme");
    QBarSet *set2 = new QBarSet("Femme");
    QBarSet *set3 = new QBarSet("Autre");

    *set1 << h1 << h2 << h3;
    *set2 << f1 << f2 << f3;
    *set3 << a1 << a2 << a3;

    QBarSeries *series = new QBarSeries();

    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart->addSeries(series);

    chart->setTitle("Statistique Demographique");
    QStringList cate;
    cate << "20-30" << "30-40" << "40-50";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(cate);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
    return chartView;
}
QChartView *Employes::stat_money_age()
{

    QSqlQuery query;
    int flous=0;
    //nombre 3bed men kol jens
    int h1=0;
    int h2=0;
    int h3=0;

    int f1=0;
    int f2=0;
    int f3=0;

    int a1=0;
    int a2=0;
    int a3=0;

    //kol 3bed men kol jens 9adeh edakhel flous
    float ah1=0;
    float ah2=0;
    float ah3=0;

    float af1=0;
    float af2=0;
    float af3=0;

    float aa1=0;
    float aa2=0;
    float aa3=0;
    query.prepare("select id_em,date_nai,sexe,salaire,prime from salaires,employes where salaires.id = employes.id_em");
    if(query.exec())
    {
        while(query.next())
        {
            int id=query.value(0).toInt();
            QString sexe=query.value(2).toString();
            int salaire=query.value(3).toInt();
            int prime=query.value(4).toInt();
            QString dates =query.value(1).toString();
            QDate date = QDate::fromString(dates,"ddd MMM M yyyy");
            dates = date.toString("yyyy");
            int year = dates.toInt();
            qDebug() << id << year << sexe << salaire << prime << "\n" ;
            flous+=salaire+prime;
            if(((2022-year) >= 20) && ((2022-year) <= 30) )
            {
                if(sexe == "Homme")
                {h1++;
                ah1+=salaire+prime;
                }
                if(sexe == "Femme")
                {f1++;
                af1+=salaire+prime;
                }
                if(sexe == "Autre")
                { a1++;
                aa1+=salaire+prime;
                }
            }
            if(((2022-year) > 30) && ((2022-year) <= 40) )
            {
                if(sexe == "Homme")
                {h2++;
                ah2+=salaire+prime;
                }
                if(sexe == "Femme")
                { f2++;
                af2+=salaire+prime;
                }
                if(sexe == "Autre")
                {a2++;
                aa2+=salaire+prime;
                }
            }
            if(((2022-year) > 40) && ((2022-year) <= 50) )
            {
                if(sexe == "Homme")
                {
                    h3++;
                    ah3+=salaire+prime;
                }
                if(sexe == "Femme")
                {
                    f3++;
                    af3+=salaire+prime;
                }
                if(sexe == "Autre")
                {
                    a3++;
                    aa3+=salaire+prime;
                }
            }



        }

    }

    QBarSet *set1 = new QBarSet("Homme");
    QBarSet *set2 = new QBarSet("Femme");
    QBarSet *set3 = new QBarSet("Autre");

    *set1 << 100*ah1/flous << 100*ah2/flous << 100*ah3/flous;
    *set2 << 100*af1/flous << 100*af2/flous << 100*af3/flous;
    *set3 << 100*aa1/flous << 100*aa2/flous << 100*aa3/flous;

    QBarSeries *series = new QBarSeries();

    series->append(set1);
    series->append(set2);
    series->append(set3);

    QChart *chart = new QChart();
    chart->addSeries(series);

    chart->setTitle("Statistique Du la Distribution du paiments");
    QStringList cate;
    cate << "20-30" << "30-40" << "40-50";

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(cate);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
chartView->chart()->setAnimationOptions(QChart::AllAnimations);
    return chartView;
}
