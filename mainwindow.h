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

    void on_pushButton_actualiser_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_supprimer_clicked();

    void on_pushButton_modifier_clicked();


    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    benevoles Be;
};
#endif // MAINWINDOW_H
