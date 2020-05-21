#ifndef ADMIN_CH_SINFO_H
#define ADMIN_CH_SINFO_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtGui>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

namespace Ui {
class admin_ch_sinfo;
}

class admin_ch_sinfo : public QMainWindow
{
    Q_OBJECT

public:
    QDateTime dateTime;//current time
    QString ch_or_ad;// A signal to tell change item or add one
    explicit admin_ch_sinfo(QWidget *parent = nullptr);
    ~admin_ch_sinfo();
public slots:
    void on_menu_triggered(QAction*);
    void on_Sno_LE_editingFinished();
    void on_Add_Ch_B_clicked();
    void on_del_B_clicked();
    void on_Search_B_clicked();
private:

    Ui::admin_ch_sinfo *ui;
    void self_init();
};

#endif // ADMIN_CH_SINFO_H
