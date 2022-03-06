#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QAbstractItemView>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QDateEdit>
#include <QDateTime>
#include <QCalendarWidget>
#include <QTableWidget>
#include <QTableView>
#include "connection.h"
#include "necessiteux.h"

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

    void on_ajouterNecessiteux_clicked();

    void on_tableN_activated(const QModelIndex &index);

    void on_supprimerNecessiteux_clicked();

    void on_modifier_Necessiteux_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_returnPressed();

private:
    Ui::MainWindow *ui;

    necessiteux N;
};
#endif // MAINWINDOW_H
