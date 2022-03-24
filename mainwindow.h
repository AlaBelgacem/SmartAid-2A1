#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QAbstractItemView>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>

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

    void on_rechercher_returnPressed();

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
