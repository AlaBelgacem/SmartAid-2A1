#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "crises.h"
#include "PieChart.h"
#include "Arduino.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QAbstractItemView>
#include <QString>
#include <QDebug>
#include <QListWidget>
#include <QMessageBox>
#include "smtp.h"
#include <QtWidgets/QMessageBox>
#include <QFileDialog>

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

    void on_pushButton_PDF_clicked();

    void on_browseBtn_clicked();

    void on_sendBtn_clicked();

    void mailSent(QString);

    void on_boutonAller_clicked();

    void afficherPosition(QString latitude, QString longitude);

    void afficherInformations(QString adresse, QString coordonnee);

    void get_rfid();

private:
    Ui::MainWindow *ui;
    QStringList files;
    Crises Cr; //object de type crises
    QByteArray data;
    QString uid;
    Arduino A;
};
#endif // MAINWINDOW_H
