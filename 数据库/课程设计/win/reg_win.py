#-*-coding:utf-8-*-
'''挂号窗体主程序'''

import sys
import pymysql
import random
import time
import sql.dbopr as dbo
from UI.regui import Ui_MainWindow
from PyQt5.QtWidgets import * 

class Reg_Win(QMainWindow,Ui_MainWindow):
    def __init__(self,db = ""):
        super().__init__()
        self.db = db
        self.initUI()
        self.SeachWay = "Stu_info"
        self.show()
        
    def initUI(self):
        self.setupUi(self)
        self.statusBar.showMessage("Ready")
        self.Stu_info.triggered.connect(self.Stu_info_uiset)
        self.Stu_reg.triggered.connect(self.Stu_reg_uiset)
        self.Search.clicked.connect(self.search)
        self.Reg.clicked.connect(self.register)       
        
    def Stu_info_uiset(self):
        num = 0
        for i in ["学号","姓名","年龄","学院","学生类型","医保类型"]:
            item = QTableWidgetItem(i)
            self.tableWidget.setHorizontalHeaderItem(num, item)
            num += 1
        for i in range(6 - num):
            item = QTableWidgetItem("")
            self.tableWidget.setHorizontalHeaderItem(i+num, item)
        self.SeachWay = "Stu_info"

    def Stu_reg_uiset(self):
        num = 0
        for i in ["学号","姓名","处方号","就诊时间"]:
            item = QTableWidgetItem(i)
            self.tableWidget.setHorizontalHeaderItem(num, item)
            num += 1
        for i in range(6 - num):
            item = QTableWidgetItem("")
            self.tableWidget.setHorizontalHeaderItem(i+num, item)
        self.SeachWay = "Stu_reg"

    def search(self):
        self.statusBar.showMessage('Working')
        if self.SeachWay == "Stu_info":
            self._search_info()
        else:
            self._search_reg()
        self.statusBar.showMessage('Ready')
    def register(self):
        self.statusBar.showMessage('Working')
        Sno = self.Sno_2.text()
        Sname = self.Sname_2.text()
        collage = self.collage.currentText()
        Age = self.Age.value()
        indent = self.indent.currentText();
        MT = self.MT.currentText()

        if Sno == '':
            QMessageBox.warning(self,"Warnning","请输入学号!",QMessageBox.Yes)#空学号
            self.statusBar.showMessage('Ready')
            return
        res = dbo.select(self.db,"reg_S_info_s_Sno",Sno)
        if res == ():#未知学号
            if Sname == '':
                QMessageBox.warning(self,"提示","创建新学生请输入姓名",QMessageBox.Yes)
                return
            else:
                reply = QMessageBox.question(self,"创建","是否创建新学生?",QMessageBox.Yes|QMessageBox.No,QMessageBox.No)
                if reply == QMessageBox.Yes:
                    a = dbo.insert(self.db,"Stu_info",(Sno,Sname,Age,collage,indent,MT))
                    if a == 0:
                        QMessageBox.about(self,"success","创建完成")
                    else:
                        QMessageBox.warning(self,"fail","创建失败")
        else:
            
            if Sname == "":#自动补全
                self.Sname_2.setText(res[0][1])
                Sname = res[0][1]

            if res[0][1:] != (Sname,Age,collage,indent,MT):
                reply = QMessageBox.question(self,"提示","信息冲突,是否更新信息?",QMessageBox.Yes|QMessageBox.No,QMessageBox.No)
                if reply == QMessageBox.No:
                    self.statusBar.showMessage('Ready')
                    return
                else:
                    dbo.update(self.db,"reg_info_update",(Sno,Sname,Age,collage,indent,MT))
                    self._register({"Sno":Sno,'Sname':Sname,'collage':collage,"Age":Age,"indent":indent,"MT":MT})
            else:
                self._register({"Sno":Sno,'Sname':Sname,'collage':collage,"Age":Age,"indent":indent,"MT":MT})

    def _register(self,info):
        
        Pno = str(random.randint(100000000,999999999))
        Mtime = time.strftime("%Y-%m-%d %H:%M:%S",time.gmtime())
        a = dbo.insert(self.db,'Me_Re',(info["Sno"],Pno,Mtime))
        if a == 0:
            QMessageBox.about(self,"挂号成功",'您的号码为:{}'.format(Pno))
        else:
            QMessageBox.warning(self,"挂号失败",'您的号码为:{}'.format(Pno))

    
    
    def _search_info(self):
        if self.Sno.text() == "" and self.Sname.text() == "":
            res = dbo.select(self.db,'reg_S_info_n')
            self.show_res(res)
        elif self.Sno.text() == "":
            res = dbo.select(self.db,'reg_S_info_s_Sname',self.Sname.text())
            self.show_res(res)
        elif self.Sname.text() == "":
            res = dbo.select(self.db,'reg_S_info_s_Sno',self.Sno.text())
            self.show_res(res)
        else:
            res = dbo.select(self.db,'reg_S_info_D_info',self.Sno.text(),self.Sname.text())
            self.show_res(res)    
    
    def _search_reg(self):#--------------------waiting for test
        if self.Sno.text() == "" and self.Sname.text() == "":
            res = dbo.select(self.db,'reg_S_reg_n')
            self.show_res(res)
        elif self.Sno.text() == "":
            res = dbo.select(self.db,'reg_S_reg_s_Sname',self.Sname.text())
            self.show_res(res)
        elif self.Sname.text() == "":
            res = dbo.select(self.db,'reg_S_reg_s_Sno',self.Sno.text())
            self.show_res(res)
        else:
            res = dbo.select(self.db,'reg_S_reg_D_info',self.Sno.text(),self.Sname.text())
            self.show_res(res)

    def show_res(self,res):
        row = 0
        self.tableWidget.setRowCount(0)
        self.tableWidget.setRowCount(len(res))
        for item in res:
            if item :
                column = 0
                for i in item:
                    _ = QTableWidgetItem(str(i))
                    self.tableWidget.setItem(row,column,_)
                    column += 1
                row += 1
        


    def closeEvent(self,event):
          reply = QMessageBox.question(self,'Message',"你是否确认退出?",QMessageBox.Yes|QMessageBox.No,QMessageBox.No)
          if reply == QMessageBox.Yes:
               event.accept()
          else:
               event.ignore()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    db = pymysql.connect("localhost","reg_admin","123456","hospital")
    reg = Reg_Win(db)
    sys.exit(app.exec_())