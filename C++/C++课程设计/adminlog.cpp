#include "adminlog.h"
#include "ui_adminlog.h"

adminlog::adminlog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminlog)
{
    ui->setupUi(this);
    connect(ui->log_B,SIGNAL(clicked()),this,SLOT(login()));
}

void adminlog:: login()
{
    QString paswd;
    paswd = ui->lineEdit->text();
    int res = 0;
    if(paswd == "00000000")
    {
        res = 1;
        emit logover(res);
        QMessageBox::information(this,"登录成功", "登录成功!");
        this->close();
    }
    else
        QMessageBox::critical(this,"错误", "密码错误!", QMessageBox::Yes);
}

adminlog::~adminlog()
{
    delete ui;
}
