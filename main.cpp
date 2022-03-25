#include "mainwindow.h"
#include"connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;//Une instance de la classe connection

    bool test=c.createconnection();//Etablir la connexion

    MainWindow w;

    if(test)//Si la connexion est établie
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
        QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else//Si la connexion a échoué

        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}
