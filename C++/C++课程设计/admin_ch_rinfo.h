#ifndef ADMIN_CH_RINFO_H
#define ADMIN_CH_RINFO_H

#include <QMainWindow>
#include <QDebug>
#include <QtGui>



namespace Ui {
class admin_ch_rinfo;
}

class admin_ch_rinfo : public QMainWindow
{
    Q_OBJECT

public:
    int n,l,r,o;
    int num;
    void paintEvent(QPaintEvent *event);
    QDateTime dateTime;
    explicit admin_ch_rinfo(QWidget *parent = nullptr);
    ~admin_ch_rinfo();
    void plot_info(QString,QString,QString,QString);
public slots:
    void on_menu_triggered(QAction*);
    void on_all_search_B_clicked();
    void on_s_search_B_clicked();
    void on_del_re_B_clicked();
    void on_tabWidget_currentChanged(int);
private:
    Ui::admin_ch_rinfo *ui;
    void self_init();
};

#endif // ADMIN_CH_RINFO_H
