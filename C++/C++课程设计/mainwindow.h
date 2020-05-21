#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "adminlog.h"
#include "admin_ch_sinfo.h"
#include <QMainWindow>
#include <QtGui>
#include <QDebug>


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    QDateTime dateTime;//current time
    QTime inTime;//in comany time
    QTime outTime;//out  comany time
    QTime overTime;//jiaban shijian
    QSqlDatabase db;
    QString time_flag;//2late or 2early or 1over or 0normal or 3 rest
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    void show_time();
    void self_init();
    int admin_able;
public slots:
    void incompany();
    void for_rest();
    void admin_log();
    void onTimeOut();
    void change_log(int);

};

#endif // MAINWINDOW_H
