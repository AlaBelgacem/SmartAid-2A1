#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QAbstractItemView>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include"evenements.h"
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    //Les Boutons Menu

    void on_Bouton_Ajouter_Event_Menu_clicked();
    void on_Bouton_Afficher_Event_Menu_clicked();
    void on_Bouton_Calendrier_Menu_clicked();
    void on_Bouton_Modif_Supp_Event_Menu_clicked();
    //Les Boutons HOME

    void on_Ajouter_Event_HOME_clicked();
    void on_Afficher_Event_HOME_clicked();
    void on_Modifier_Supprimer_Event_HOME_clicked();
    void on_Calendrier_HOME_clicked();
    //Les Boutons CRUD

    void on_Bouton_Modifier_Page3_clicked();
    void on_Bouton_Supprimer_Page3_clicked();
    void on_Ajouter_event_clicked();
    //Les Boutons plus

    void on_Bouton_Vider_Champs_Page1_clicked();
    void on_line_id_returnPressed();
    void on_search_bar_textChanged(const QString &arg1);
    void on_Tri_Croissant_clicked();
    void on_Tri_Decroissant_clicked();

    void on_Bouton_Certifications_Menu_clicked();
    //ouverture pdf

   //Bouton Design

    void on_pushButton_3_clicked();

    void on_Design1_clicked();

    void on_Design2_clicked();

    void on_Design3_clicked();

    void on_calendarWidgett_clicked(const QDate &date);

    void on_tabWidget_currentChanged(int index);

    void on_Affiche_Home_clicked();

    void on_ToDoList_HOME_clicked();

    void on_Bouton_Documents_Administratifs_Menu_clicked();

    void on_Bouton_Affiche_Menu_clicked();

    void on_b1_clicked();

    void ajouttodo();

    void done();

    void done2();

    void load();

    void inprogress();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_tri_id_clicked();

    void on_Nom_id_clicked();

    void on_Date_tri_clicked();

    void on_ard_butt_clicked();

private:
    Ui::MainWindow *ui;
    Evenements E;
public:
    QByteArray data; // variable contenant les données reçues
int i=0;
    Arduino A; // objet temporaire
};
#endif // MAINWINDOW_H
