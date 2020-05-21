#ifndef ADMINLOG_H
#define ADMINLOG_H

#include <QMainWindow>
#include <QMessageBox>

namespace Ui {
class adminlog;
}

class adminlog : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminlog(QWidget *parent = nullptr);
    ~adminlog();
    signals:
    void logover(int);
public slots:
    void login();

private:
    Ui::adminlog *ui;

};

#endif // ADMINLOG_H
