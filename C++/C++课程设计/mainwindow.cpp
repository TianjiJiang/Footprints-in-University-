#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    self_init();
}

void MainWindow::self_init()
{
    //self UI init part

    connect(ui->for_rest_B,SIGNAL(clicked()),this,SLOT(for_rest()));
    connect(ui->adminlog,SIGNAL(clicked()),this,SLOT(admin_log()));
    connect(ui->reg_B,SIGNAL(clicked()),this,SLOT(incompany()));
    show_time();
    //self var init part
    ui->statusBar->showMessage( "Connecting the database...");
    inTime = QTime(8,0,0);
    outTime = QTime(17,0,0);
    overTime = QTime(20,0,0);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/tianji-jiang/Documents/C++/课程设计/测试/build-test-Desktop_Qt_5_13_0_GCC_64bit-Debug/company.db");
    if (!db.open())
    {
        ui->statusBar->showMessage( "Error: Failed to connect database.");
    }
    else
    {
        ui->statusBar->showMessage( "Succeed to connect database." );
    }


    admin_able = 0;//NO ADMIN LOGGED
}

void MainWindow::show_time()
{
    QTimer *pTimer = new QTimer(this);
    // 设置定时间隔
    pTimer->setInterval(500);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    // 启动定时器
    pTimer->start();
}
void MainWindow::onTimeOut()
{
    // 获取系统当前时间
    dateTime = QDateTime::currentDateTime();
    // 显示的内容
    ui->TIme_show->display(dateTime.toString("HH:mm:ss"));
    if (overTime <= dateTime.time())
    {
        time_flag = '1';
        ui->TIme_show->setStyleSheet("color: yellow");
    }
    else if(inTime >= dateTime.time() || outTime <= dateTime.time())
    {
        time_flag = '0';
        ui->TIme_show->setStyleSheet("color: green");
    }
    else
    {
        time_flag = '2';
        ui->TIme_show->setStyleSheet("color: red");

    }
}
void MainWindow::incompany()
{
    QString Sno;
    Sno = ui->Sno_LE->text();
    if (Sno == "")
        QMessageBox::critical(this,"错误","请输入职工号!");
    else
    {
        QSqlQuery sql_query;
        QString sql;
        sql = "select Sno,Sname from staff where Sno = '" + Sno + "';";
        qDebug() << Sno << endl;
        qDebug() << sql << endl;
        if(!sql_query.exec(sql))
        {
            QMessageBox::critical(NULL,"失败","签到失败!");
            ui->statusBar->showMessage(sql_query.lastError().text());
        }
        else
        {
           sql_query.next();
           ui->Sname_LE->setText(sql_query.value(1).toString());
           if(sql_query.value(0).toInt())
           {
               sql = "insert into Sign values(\""+ Sno +"\",\""
                       + dateTime.toString("yyyy-MM-dd HH:mm:ss").toUtf8()
                       +"\","+ time_flag+");";
               if(!sql_query.exec(sql))
               {
                   QMessageBox::critical(NULL,"失败","签到失败!");
                   ui->statusBar->showMessage(sql_query.lastError().text());
               }
               else
               {
                   QMessageBox::about(NULL,"成功","签到成功!\n祝您工作好心情!");
                   ui->statusBar->showMessage("insert complieted");
                   ui->statusBar->showMessage("Ready");
               }
           }
           else
           {
                  QMessageBox::critical(NULL,"失败","系统内无此员工!");
           }
        }
    }
}

void MainWindow::change_log(int i)
{
    admin_able = i;
}

void MainWindow::for_rest()
{
    if (admin_able == 0)
    {
    adminlog *adlg = new adminlog(this);
    connect(adlg,SIGNAL(logover(int)),this,SLOT(change_log(int)));
    adlg -> show();
    }
    if(admin_able== 1)
    {
        QString Sno;
        Sno = ui->Sno_LE->text();
        if (Sno == "")
            QMessageBox::critical(NULL,"错误","请输入职工号!");
        else
        {
            QSqlQuery sql_query;
            QString sql;
            sql = "select Sno,Sname from staff where Sno = '" + Sno + "';";
            if(!sql_query.exec(sql))
            {
                QMessageBox::critical(NULL,"失败","请假失败!");
                ui->statusBar->showMessage(sql_query.lastError().text());
            }
            else
            {
                sql_query.next();
                ui->Sname_LE->setText(sql_query.value(1).toString());
               if(sql_query.value(0).toInt())
               {
                   sql = "insert into Sign values(\""+ Sno +"\",\""
                           + dateTime.toString("yyyy-MM-dd HH:mm:ss").toUtf8()
                           +"\","+ "3" +");";
                   if(!sql_query.exec(sql))
                   {
                       QMessageBox::critical(NULL,"失败","请假失败!");
                       ui->statusBar->showMessage(sql_query.lastError().text());
                   }
                   else
                   {
                       QMessageBox::about(NULL,"成功","请假成功!");
                       ui->statusBar->showMessage("insert complieted");
                       ui->statusBar->showMessage("Ready");
                   }
               }
               else
               {
                      QMessageBox::critical(NULL,"失败","系统内无此员工!");
               }
            }
        }
    }
}

void MainWindow::admin_log()
{
    if (admin_able == 0)
    {
    adminlog *adlg = new adminlog(this);
    connect(adlg,SIGNAL(logover(int)),this,SLOT(change_log(int)));
    adlg -> show();
    }
    if (admin_able == 1)
    {
        admin_ch_sinfo *ad = new admin_ch_sinfo(this);
        ad->show();
        this->hide();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
