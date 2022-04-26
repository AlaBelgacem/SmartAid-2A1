#include "mainwindow.h"
#include<QMessageBox>
#include"connection.h"
#include <QApplication>
#include "employes.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
