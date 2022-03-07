#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "crises.h"
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
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_ajouter_clicked();

    void on_pushButton_supp_clicked();

    void on_pushButton_modif_clicked();

    void on_lineEditRecherche_textChanged(const QString &arg1);

    void on_tableView_activated(const QModelIndex &index);

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

private:
    Ui::MainWindow *ui;

    Crises Cr;
};
#endif // MAINWINDOW_H
