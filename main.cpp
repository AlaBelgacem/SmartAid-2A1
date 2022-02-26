#include "mainwindow.h"
#include"connection.h"
#include <QApplication>
#include<QMessageBox>


int main(int argc, char *argv[])
{
    Connection c; //declaration instance c
    bool test=c.createconnect();//  Connection avec base de données
    QApplication a(argc, argv);
    MainWindow w;
    if(test)//Si la connexion est établie
    {
    w.show();
    QMessageBox::information(nullptr,QObject::tr("database is open"),
    QObject::tr("connection sucessful.\n"
                                "Click Cancel To Exit."),QMessageBox::Cancel);
    }
    else //Si la connexion échoue
    {
        QMessageBox::critical(nullptr,QObject::tr("database is not open"),
        QObject::tr("connection failed.\n"
                                    "Click Cancel To Exit."),QMessageBox::Cancel);
    }




    return a.exec();
}
