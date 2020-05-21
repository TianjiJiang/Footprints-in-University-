#include "admin_ch_sinfo.h"
#include "ui_admin_ch_sinfo.h"
#include "admin_ch_rinfo.h"

admin_ch_sinfo::admin_ch_sinfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin_ch_sinfo)
{
    ui->setupUi(this);
    self_init();
}

void admin_ch_sinfo::self_init()
{
    ui->info_TB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ch_or_ad = "ad";
}

admin_ch_sinfo::~admin_ch_sinfo()
{
    delete ui;
}

void admin_ch_sinfo::on_menu_triggered(QAction* A)//change the window
{
    if(A == ui->Rinfo_A)
    {
        admin_ch_rinfo *R = new admin_ch_rinfo(this);
        R->show();
        this->hide();
    }
}

void admin_ch_sinfo::on_Sno_LE_editingFinished()
{
    QSqlQuery sql_query;
    QString sql;
    QString Sno;
    Sno = ui->Sno_LE->text();
    sql = "select count(*) from staff where Sno = '" + Sno + "';";
    if(sql_query.exec(sql))
    {
        sql_query.next();
        if(sql_query.value(0).toInt())
        {
            ui-> Add_Ch_B->setText("修改");
            ui->del_B->setEnabled(true);
            ch_or_ad = "ch";
        }
        else
        {
            ui->del_B->setEnabled(false);
            ui->Add_Ch_B->setText("添加");
            ch_or_ad = "ad";
        }

    }

}

void admin_ch_sinfo::on_Add_Ch_B_clicked()
{
    QString Sno, Sname, Ssex, birth;
    Sname = ui->Sname_LE->text();
    Sno = ui->Sno_LE->text();
    Ssex = ui->Ssex_CB->currentText();
    birth = ui->birthday->text();
    if (ch_or_ad == "ad")
    {
        if (Sno == "" || Sname == "")
        {
            QMessageBox::critical(this,"错误","请输入完整信息!");
        }
        else
        {
            QSqlQuery sql_query;
            QString sql;
            sql = "insert into staff values('" + Sno + "','" + Sname + "','"
                    + Ssex + "','" + birth + "');";
            if(sql_query.exec(sql))
            {
                QMessageBox::about(this,"成功","添加新员工成功!");
            }
            else
            {
                QMessageBox::critical(this,"错误","添加失败!");
            }
        }
    }
    else
    {
        if (Sno == "" || Sname == "")
        {
            QMessageBox::critical(this,"错误","请输入完整信息!");
        }
        else
        {
            QSqlQuery sql_query;
            QString sql;
            sql = "update staff set Sname = '" + Sname + "',"
                    + "Ssex = '" + Ssex +"',"
                    + "birth = '" + birth + "' where Sno = '" + Sno + "';";
            if(sql_query.exec(sql))
            {
                QMessageBox::about(this,"成功","更改信息成功!");
            }
            else
            {
                QMessageBox::critical(this,"错误","更改信息失败!");
            }
        }
    }
}

void admin_ch_sinfo::on_del_B_clicked()
{

    if (QMessageBox::Yes == QMessageBox::question(this,"确认","是否确认删除信息?"))
    {
        QSqlQuery sql_query;
        QString sql,Sno;
        Sno = ui->Sno_LE->text();
        dateTime = QDateTime::currentDateTime();
        sql = "insert into back_up select *,'" + dateTime.toString("yyyy-MM-dd HH:mm:ss") +"' from Sign where Sno = '" + Sno + "';";
        if (sql_query.exec(sql))
        {
            sql = "delete from staff where Sno = '" + Sno + "';";
            if (sql_query.exec(sql))
            {
                sql = "delete from Sign where Sno = '" + Sno + "';";
                if (sql_query.exec(sql)) QMessageBox::about(this,"成功","删除成功!");
                else
                    QMessageBox::information(this,"失败","删除失败!");

            }
            else
                QMessageBox::information(this,"失败","删除失败!");
        }
        else
            QMessageBox::information(this,"失败","删除失败!");
    }
}

void admin_ch_sinfo::on_Search_B_clicked()
{
    QString Sno, Sname;
    QString sql;
    QSqlQuery sql_query;
    Sno = ui->Sno_S_LE->text();
    Sname = ui->Sname_S_LE->text();

    if (Sno == "" && Sname == "")
    {
        sql = "select * from staff;";
    }
    else if (Sno == "")
    {
        sql = "select * from staff where Sname = '" + Sname + "';";
    }
    else if (Sname == "")
    {
        sql = "select * from staff where Sno = '" + Sno + "';";
    }
    else
    {
        sql = "select * from staff where Sno = '" + Sno + "' and Sname = '"+ Sname +"';";
    }

    if(sql_query.exec(sql))
    {
        ui->info_TB->clearContents();
        int i = 0;

        while(sql_query.next())
        {
            ui->info_TB->setRowCount(i + 1);
            ui->info_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
            ui->info_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
            ui->info_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
            ui->info_TB->setItem(i,3,new QTableWidgetItem(sql_query.value(3).toString()));
            i++;
        }

    }
    else {
        qDebug() << sql <<endl;
        qDebug() << sql_query.lastError();
    }


}
