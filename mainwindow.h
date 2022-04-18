#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QAbstractItemView>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include "arduino.h"
#include "evenements.h"
#include "dons.h"
#include "categories.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_listWidget_itemClicked();

    void on_Ajouter_clicked();

    void on_Actualiser_clicked();

    void on_table1_activated(const QModelIndex &index);

    void on_Modifier_clicked();

    void on_Supprimer_clicked();

    void clear();

    bool control(int n);

    void init_errors();

    void init_errors_2();

    void on_comboBox_highlighted(const QString &arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_Menu_modi_supp_employe_clicked();

    void on_Menu_afficher_employe_clicked();

    void on_Menu_ajouter_employe_clicked();

    void on_Ajouter_Emp_HOME_clicked();

    void on_modifier_Emp_HOME_clicked();

    void on_Afficher_Emp_HOME_clicked();

    void on_bo_3_clicked();

    void profil();

    void on_pdf_clicked();

    void on_pushButton_2_clicked();

    void on_table4_activated(const QModelIndex &index);

    void on_mdp_oub_clicked();

    void on_mdp_b_clicked();

    void on_pushButton_9_clicked();

    void on_mdp_b_2_clicked();

    void on_Ajouter_2_clicked();

    void on_table3_activated(const QModelIndex &index);

    void on_Modifier_2_clicked();

    void on_Supprimer_2_clicked();

    void on_pushButton_13_clicked();

    void on_rechercher_textChanged(const QString &arg1);

    void on_tab_ge_currentChanged(int index);

    void update_stat();

    void on_pushButton_14_clicked();

    void on_logout_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    //evenement
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

    void test();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_tri_id_clicked();

    void on_Nom_id_clicked();

    void on_Date_tri_clicked();

    //don
    void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_ajouter_c_clicked();

    void on_pushButton_modifier_c_clicked();

    void on_pushButton_supprimer_c_clicked();

    void on_tableView_2_activated(const QModelIndex &index);

    void on_lineEdit_recherche_textChanged(const QString &arg1);

    void on_lineEdit_recherche_c_textChanged(const QString &arg1);

    void on_radioButton_C_clicked();

    void on_radioButton_D_clicked();

    void on_radioButton_C_c_clicked();

    void on_radioButton_D_c_clicked();

    void on_pushButton_PDF_clicked();

    void on_pushButton_PDF_c_clicked();

    void on_tabstat_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;

    QByteArray data;

    Arduino A;

    Evenements E;

    Dons Etmp;

    Categories Cat;
};
#endif // MAINWINDOW_H
