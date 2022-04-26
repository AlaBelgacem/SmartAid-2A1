#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QStackedWidget>
#include <QAbstractItemView>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include "dons.h"
#include "categories.h"
#include "qcustomplot.h"
#include <QSqlQuery>
#include <QSystemTrayIcon>

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
    void on_listWidget_itemClicked(QListWidgetItem *item);

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
    Dons Etmp;
    Categories Cat;
};

#endif // MAINWINDOW_H
