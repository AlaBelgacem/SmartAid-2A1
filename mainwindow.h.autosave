#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "benevoles.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QAbstractItemView>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include <QCompleter>
#include<QTcpSocket>
#include"arduino.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class QTcpSocket;

namespace  duartecorporation {


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_ajouter_clicked();

    void on_pushButton_actualiser_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();


    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    //void on_comboBox_2_activated(const QString &arg1);

    void on_evaluer_clicked();

    void on_pb_envoyer_clicked();

    void on_pb_connecter_clicked();

    //void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    benevoles Be;
    QTcpSocket *mSocket;

    //arduino
    QByteArray data; // variable contenant les données reçues
    Arduino A; // objet temporaire
};
}
#endif // MAINWINDOW_H
