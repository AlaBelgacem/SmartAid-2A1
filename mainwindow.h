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
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_Ajouter_event_3_clicked();

    void on_Ajouter_event_clicked();

    void on_Ajouter_event_2_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_Ajouter_event_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
