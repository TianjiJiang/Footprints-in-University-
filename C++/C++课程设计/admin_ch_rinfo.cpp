#include "admin_ch_rinfo.h"
#include "ui_admin_ch_rinfo.h"
#include "admin_ch_sinfo.h"

admin_ch_rinfo::admin_ch_rinfo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::admin_ch_rinfo)
{
    ui->setupUi(this);

    self_init();
}

void admin_ch_rinfo::self_init()
{
    ui->over_TB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->la_or_ear_TB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rest_TB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->del_TB->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->nor_TB->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->over_TB->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->la_or_ear_TB->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->rest_TB->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->del_TB->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->nor_TB->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->info_LB1 ->setText("");
    ui->info_LB2 ->setText("");
    ui->info_LB3 ->setText("");
    ui->info_LB4 ->setText("");

    n = 0;
    l = 0;
    r = 0;
    o = 0;
}

admin_ch_rinfo::~admin_ch_rinfo()
{
    delete ui;
}

void admin_ch_rinfo::on_menu_triggered(QAction* A)
{
    if(A == ui->Sinfo_A)
    {
        admin_ch_sinfo *S = new admin_ch_sinfo(this);
        S->show();
        this->hide();
    }
}

void admin_ch_rinfo::plot_info(QString nor, QString over, QString laear, QString rest)
{
    if (num == 1)
    {
        ui->info_LB1 ->setText("正常到岗离岗:" + nor + "天");
        ui->info_LB2 ->setText("迟到早退:" + laear + "天");
        ui->info_LB3 ->setText("请假天数:" + rest + "天");
        ui->info_LB4 ->setText("加班天数:" + over + "天");
    }
    else
    {
        ui->info_LB1 ->setText(QString("平均正常到岗离岗:%1天").arg(nor.toFloat()/num));
        ui->info_LB2 ->setText(QString("平均迟到早退:%1天").arg(laear.toFloat()/num));
        ui->info_LB3 ->setText(QString("平均请假天数:%1天").arg(rest.toFloat()/num));
        ui->info_LB4 ->setText(QString("平均加班天数:%1天").arg(over.toFloat()/num));

    }

    n = nor.toInt();
    l = laear.toInt();
    r = rest.toInt();
    o = over.toInt();

    this->repaint();
//    paintEvent(QPaintEvent *event);
}


void admin_ch_rinfo::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    // 设置画笔颜色
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing, true);
    QRectF rect(80,35,180,180);
    QRectF rect1(300,43,10,10);
    QRectF rect2(300,91,10,10);
    QRectF rect3(300,134,10,10);
    QRectF rect4(300,185,10,10);

    if((n + r + o + l) == 0)
    {
        painter.setPen(QColor(0, 160, 230));

            // 设置字体：微软雅黑、点大小50、斜体
            QFont font;
            font.setFamily("Microsoft YaHei");
            font.setPointSize(30);
            font.setItalic(true);
            painter.setFont(font);

            // 绘制文本
            painter.drawText(rect, Qt::AlignCenter, "无数据");
    }
    else
    {
        painter.drawRect(rect1);
        painter.drawRect(rect2);
        painter.drawRect(rect3);
        painter.drawRect(rect4);

        int rn = 360*16*n/(n + o + l + r);
        int rl = 360*16*l/(n + o + l + r);
        int rr = 360*16*r/(n + o + l + r);
        int ro = 360*16*o/(n + o + l + r);
        qDebug() << rn << rl << rr << ro << endl ;

        painter.setBrush(QColor(50,190,80));
        painter.drawPie(rect,0, rn);
        painter.drawRect(rect1);

        painter.setBrush(QColor(190,100,100));
        painter.drawPie(rect, rn ,rl);
         painter.drawRect(rect2);

        painter.setBrush(QColor(100,100,190));
        painter.drawPie(rect,rn +rl,rr);
        painter.drawRect(rect3);

        painter.setBrush(QColor(120,180,190));
        painter.drawPie(rect,rn +rl + rr,ro);
        painter.drawRect(rect4);

    }


}


void admin_ch_rinfo::on_all_search_B_clicked()
{
    QString sql, t1, t2, t3, t4;
    QSqlQuery sql_query;
    sql = "select count(*) from staff group by Sno;";
    if (sql_query.exec(sql))
    {
        num = 0;
            while(sql_query.next())
            {
                num += sql_query.value(0).toInt();
            }


    }
    sql = "select status,count(*) from Sign group by status order by status";
    if(sql_query.exec(sql))
    {
        sql_query.next();
        t1 = sql_query.value(1).toString();
        sql_query.next();
        t2 = sql_query.value(1).toString();
        sql_query.next();
        t3 = sql_query.value(1).toString();
        sql_query.next();
        t4 = sql_query.value(1).toString();
        plot_info(t1,t2,t3,t4);

    }
    else {
        qDebug() << sql;
        qDebug() << sql_query.lastError();
    }

    sql = "select Sign.Sno, Sname,Sign.time from Sign,staff where status = 0 and staff.Sno = Sign.Sno;";
    if (sql_query.exec(sql))
    {
        ui->nor_TB->clearContents();
        int i = 0;
        while(sql_query.next())
        {
            ui->nor_TB->setRowCount(i + 1);
            ui->nor_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
            ui->nor_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
            ui->nor_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
            i++;
        }
    }
    else {
        qDebug() << sql;
        qDebug() << sql_query.lastError();
    }

    sql = "select Sign.Sno, Sname,Sign.time from Sign,staff where status = 1 and staff.Sno = Sign.Sno;";
    if (sql_query.exec(sql))
    {
        ui->over_TB->clearContents();
        int i = 0;
        while(sql_query.next())
        {
            ui->over_TB->setRowCount(i + 1);
            ui->over_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
            ui->over_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
            ui->over_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
            i++;
        }
    }
    else {
        qDebug() << sql;
        qDebug() << sql_query.lastError();
    }

    sql = "select Sign.Sno, Sname,Sign.time from Sign,staff where status = 2 and staff.Sno = Sign.Sno;";
    if (sql_query.exec(sql))
    {
        ui->la_or_ear_TB->clearContents();
        int i = 0;
        while(sql_query.next())
        {
            ui->la_or_ear_TB->setRowCount(i + 1);
            ui->la_or_ear_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
            ui->la_or_ear_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
            ui->la_or_ear_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
            i++;
        }
    }
    else {
        qDebug() << sql;
        qDebug() << sql_query.lastError();
    }


    sql = "select Sign.Sno, Sname,Sign.time from Sign,staff where status = 3 and staff.Sno = Sign.Sno;";
    if (sql_query.exec(sql))
    {
        ui->rest_TB->clearContents();
        int i = 0;
        while(sql_query.next())
        {
            ui->rest_TB->setRowCount(i + 1);
            ui->rest_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
            ui->rest_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
            ui->rest_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
            i++;
        }
    }
    else {
        qDebug() << sql;
        qDebug() << sql_query.lastError();
    }

    sql = "select back_up.Sno, Sname,time, addtime from back_up,staff where staff.Sno = back_up.Sno;";
    if (sql_query.exec(sql))
    {
        ui->del_TB->clearContents();
        int i = 0;
        while(sql_query.next())
        {
            ui->del_TB->setRowCount(i + 1);
            ui->del_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
            ui->del_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
            ui->del_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
            ui->del_TB->setItem(i,3,new QTableWidgetItem(sql_query.value(3).toString()));
            i++;
        }
    }
    else {
        qDebug() << sql;
        qDebug() << sql_query.lastError();
    }

}

void admin_ch_rinfo::on_s_search_B_clicked()
{
    QString sql, t1, t2, t3, t4, Sno, Sname;
    QSqlQuery sql_query;
    num = 1;
    Sno = ui->Sno_LE->text();
    Sname = ui->Sname_LE->text();
    if (Sno == "")
    {
        QMessageBox::critical(this,"注意","请输入职工号!");
    }
    else
    {
        sql = "select Sign.Sno, Sname,Sign.time from Sign,staff where Sign.Sno = '" + Sno + "' and status = 0 and staff.Sno = Sign.Sno;";
        if (sql_query.exec(sql))
        {
            ui->nor_TB->clearContents();
            int i = 0;
            while(sql_query.next())
            {
                ui->nor_TB->setRowCount(i + 1);
                ui->nor_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
                ui->nor_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
                ui->nor_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
                i++;
            }
        }
        else {
            qDebug() << sql;
            qDebug() << sql_query.lastError();
        }
        sql = "select count(*) from Sign where Sno = '" + Sno + "' and status = 0;";
        sql_query.exec(sql);
        sql_query.next();
        t1 = sql_query.value(0).toString();

        sql = "select Sign.Sno, Sname,Sign.time from Sign,staff where Sign.Sno = '" + Sno + "' and status = 1 and staff.Sno = Sign.Sno;";
        if (sql_query.exec(sql))
        {
            ui->over_TB->clearContents();
            int i = 0;
            while(sql_query.next())
            {
                ui->over_TB->setRowCount(i + 1);
                ui->over_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
                ui->over_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
                ui->over_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
                i++;
            }
        }
        else {
            qDebug() << sql;
            qDebug() << sql_query.lastError();
        }

        sql = "select count(*) from Sign where Sno = '" + Sno + "' and status = 1;";
        sql_query.exec(sql);
        sql_query.next();
        t2 = sql_query.value(0).toString();

        sql = "select Sign.Sno, Sname,Sign.time from Sign,staff where Sign.Sno = '" + Sno + "' and status = 2 and staff.Sno = Sign.Sno;";
        if (sql_query.exec(sql))
        {
            ui->la_or_ear_TB->clearContents();
            int i = 0;
            while(sql_query.next())
            {
                ui->la_or_ear_TB->setRowCount(i + 1);
                ui->la_or_ear_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
                ui->la_or_ear_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
                ui->la_or_ear_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
                i++;
            }
        }
        else {
            qDebug() << sql;
            qDebug() << sql_query.lastError();
        }

        sql = "select count(*) from Sign where Sno = '" + Sno + "' and status = 2;";
        sql_query.exec(sql);
        sql_query.next();
        t3 = sql_query.value(0).toString();

        sql = "select Sign.Sno, Sname,Sign.time from Sign,staff where Sign.Sno = '" + Sno + "' and status = 3 and staff.Sno = Sign.Sno;";
        if (sql_query.exec(sql))
        {
            ui->rest_TB->clearContents();
            int i = 0;
            while(sql_query.next())
            {
                ui->rest_TB->setRowCount(i + 1);
                ui->rest_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
                ui->rest_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
                ui->rest_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
                i++;
            }
        }
        else {
            qDebug() << sql;
            qDebug() << sql_query.lastError();
        }
        sql = "select count(*) from Sign where Sno = '" + Sno + "' and status = 3;";
        sql_query.exec(sql);
        sql_query.next();
        t4 = sql_query.value(0).toString();
        plot_info(t1,t2,t3,t4);


        sql = "select back_up.Sno, Sname,time, addtime from back_up,staff where staff.Sno = '" + Sno + "' and staff.Sno = back_up.Sno;";
        if (sql_query.exec(sql))
        {
            ui->del_TB->clearContents();
            int i = 0;
            while(sql_query.next())
            {
                ui->del_TB->setRowCount(i + 1);
                ui->del_TB->setItem(i,0,new QTableWidgetItem(sql_query.value(0).toString()));
                ui->del_TB->setItem(i,1,new QTableWidgetItem(sql_query.value(1).toString()));
                ui->del_TB->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
                ui->del_TB->setItem(i,3,new QTableWidgetItem(sql_query.value(3).toString()));
                i++;
            }
        }
        else {
            qDebug() << sql;
            qDebug() << sql_query.lastError();
        }
    }
}

void admin_ch_rinfo::on_del_re_B_clicked()
{
    if (ui->tabWidget->currentIndex() == 4)
    {
        if (ui->del_TB->currentRow() != -1)
        {
            QList<QTableWidgetItem*> citem = ui->del_TB->selectedItems();
            QString Sno,time;
            Sno = citem.value(0)->text();
            time = citem.value(2)->text();

            QString sql;
            QSqlQuery sql_query;
            sql = "insert into Sign select Sno,time,status from back_up where Sno = '" + Sno + "' and time = '" + time + "';" ;
            if (sql_query.exec(sql))
            {
                    sql = "delete from back_up where Sno = '" + Sno + "' and time = '" + time + "';" ;
                    if(sql_query.exec(sql))
                    {
                        QMessageBox::about(this,"success","恢复成功!");
                    }
            }
        }
        else {
            QMessageBox::about(this,"提示","请选择具体记录!");
        }
    }
    else
    {
        QTableWidget * tmptable;
        switch(ui->tabWidget->currentIndex())
        {
        case 0: tmptable = ui->nor_TB;break;
        case 1: tmptable = ui->la_or_ear_TB;break;
        case 2: tmptable = ui->rest_TB;break;
        case 3: tmptable = ui->over_TB;break;
        }
        qDebug() << tmptable->currentRow();
        if (tmptable->currentRow() != -1)
        {
            QList<QTableWidgetItem*> citem = tmptable->selectedItems();


            QString Sno,time;

            Sno = citem.value(0)->text();
            time = citem.value(2)->text();

            QString sql;
            QSqlQuery sql_query;
            dateTime = QDateTime::currentDateTime();
            sql = "insert into back_up select *,'" + dateTime.toString("yyyy-MM-dd HH:mm:ss")
                    +"' from Sign where Sno = '" + Sno + "' and time = '" + time + "';";
            if(sql_query.exec(sql))
            {
                sql = "delete from Sign where Sno = '" + Sno + "' and time = '" + time + "';";
                if (sql_query.exec(sql))
                    QMessageBox::about (this,"success","删除成功!");
                else
                {
                    QMessageBox::critical(this,"failed","删除失败!");
                }
            }
            else
            {
                QMessageBox::critical(this,"failed","删除失败!");
            }
        }
        else
        {
            QMessageBox::about(this,"提示","请选择具体记录");
        }
    }
}

void admin_ch_rinfo::on_tabWidget_currentChanged(int index)
{
    if (index == 4) ui->del_re_B->setText("恢复记录");
    else ui->del_re_B->setText("记录删除");
}
