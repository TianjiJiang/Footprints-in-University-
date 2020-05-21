#-*-coding:utf-8-*-
'''财务窗体主程序'''

import sys
import pymysql
import sql.dbopr as dbo
from UI.finui import Ui_MainWindow
from PyQt5.QtWidgets import * 

class Fin_Win(QMainWindow,Ui_MainWindow):
    def __init__(self,db = ""):
        super().__init__()
        self.db = db
        self.initUI()
        self.show()
        
    def initUI(self):
        self.setupUi(self)
        self.B_search.clicked.connect(self.search)
        self.B_MaT_search.clicked.connect(self.MaTsearch)
        self.B_afr.clicked.connect(self.afr)

    def MaTsearch(self):
        Mno = self.LE_MaTno_search.text()
        Mname = self.LE_MaTname_search.text()

        if Mno == Mname == '':
            res = dbo.select(self.db,"pri_n")
            self.show_res_(res)
        elif Mno == '':
            res = dbo.select(self.db,"pri_s_Mname",Mname)
            self.show_res_(res)
        elif Mname == '':
            res = dbo.select(self.db,"pri_s_Mno",Mno)
            self.show_res_(res)
        else:
            res = dbo.select(self.db,"pri_D",Mno,Mname)
            self.show_res_(res)

    
    def afr(self):
        Sno = self.LE_Sno_afr.text()
        mon = eval(self.LE_mon_afr.text())
         
        res = dbo.select(self.db,"fin_s_Sno_to_fins",Sno)
        if res == ():
            QMessageBox.warning(self,"错误","学生不存在!")
        elif res[0][-2] < mon:
            QMessageBox.warning(self,"错误","报销金额过多!")
        else:
            ret = (res[0][0:-1],res[0][-1] + mon)
            a = dbo.update(self.db,"afr",ret)



   
    def search(self,Pno):
        Sno = self.LE_Sno_search.text()
        Sname = self.LE_Sname_search.text()

        if Sno == Sname == "":
            res = dbo.select(self.db,"fin_n")
            self.show_res(res,self.TB_Stu_info)
        elif Sname == "":
            res = dbo.select(self.db,"fin_s_Sno",Sno)
            self.show_res(res,self.TB_Stu_info)

        elif Sno == "":
            res = dbo.select(self.db,"fin_s_Sname",Sname)
            self.show_res(res,self.TB_Stu_info)
        else:
            res = dbo.select(self.db,"fin_D",Sno,Sname)
            self.show_res(res,self.TB_Stu_info)

    def show_res(self,res,Qtable):
        Qtable.setEditTriggers(QTableWidget.NoEditTriggers)
        self.res = res
        row = 0
        Qtable.setRowCount(0)
        Qtable.setRowCount(len(res))
        for item in res:
            if item :
                column = 0
                for i in item:
                    _ = QTableWidgetItem(str(i))
                    Qtable.setItem(row,column,_)
                    column += 1
                row += 1
    
    def show_res_(self,res):
        self.TB_T_info.setEditTriggers(QTableWidget.NoEditTriggers)
        self.TB_M_info.setEditTriggers(QTableWidget.NoEditTriggers)
        self.TB_T_info.setRowCount(0)
        self.TB_M_info.setRowCount(0)
        self.TB_T_info.setRowCount(len(res))
        self.TB_M_info.setRowCount(len(res))

        row1 = 0
        row2 = 0
        for item in res:
            if item :
                if item[0][0] == 'M':
                    column = 0
                    for i in item:
                        _ = QTableWidgetItem(str(i))
                        self.TB_M_info.setItem(row1,column,_)
                        column += 1
                    row1 += 1
                else :
                    column = 0
                    for i in item:
                        _ = QTableWidgetItem(str(i))
                        self.TB_T_info.setItem(row2,column,_)
                        column += 1
                    row2 += 1

    def closeEvent(self,event):
          reply = QMessageBox.question(self,'Message',"你是否确认退出?",QMessageBox.Yes|QMessageBox.No,QMessageBox.No)
          if reply == QMessageBox.Yes:
               event.accept()
          else:
               event.ignore()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    db = pymysql.connect("localhost","fin_staff","123456","hospital")
    reg = Fin_Win(db)
    sys.exit(app.exec_())