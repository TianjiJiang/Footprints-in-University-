#-*-coding:utf-8-*-
'''划价窗体主程序'''

import sys
import pymysql
import sql.dbopr as dbo
from UI.priui import Ui_MainWindow
from PyQt5.QtWidgets import * 

class Pri_Win(QMainWindow,Ui_MainWindow):
    def __init__(self,db = ""):
        super().__init__()
        self.db = db
        self.initUI()
        self.MODE = "MaT"
        self.M_Mode = "add"#add->添加  cha->修改
        self.show()

        
    def initUI(self):
        self.setupUi(self)
        self.statusbar.showMessage("Ready")
        self.MODE_MaT.triggered.connect(self.MODE_MaT_uiset)
        self.MODE_pay.triggered.connect(self.MODE_pay_uiset)
        self.B_Search.clicked.connect(self.search)
        self.B_MaT_CaA.clicked.connect(self.MaT_CaA)
        self.B_Payone.clicked.connect(self.payone)
        self.LE_MaTname.editingFinished.connect(self.cha_or_add)
        self.LE_MaTno.editingFinished.connect(self.cha_or_add)
        self.B_Payone.setVisible(0)
        
        
    def MODE_MaT_uiset(self):
        num = 0
        
        for i in ["编号","名称","价格"]:
            item = QTableWidgetItem(i)
            self.tableWidget.setHorizontalHeaderItem(num, item)
            num += 1
        for i in range(5 - num):
            item = QTableWidgetItem("")
            self.tableWidget.setHorizontalHeaderItem(i+num, item)
        self.tableWidget.setRowCount(0)
        self.MODE = "MaT"
        self.B_MaT_CaA.setEnabled(1)
        self.B_Payone.setVisible(0)
        self.LB_no.setText('编号')
        self.LB_name.setText('名称')

    def MODE_pay_uiset(self):
        num = 0
        for i in ["学号","处方号","药物","总价","是否付款"]:
            item = QTableWidgetItem(i)
            self.tableWidget.setHorizontalHeaderItem(num, item)
            num += 1
        for i in range(5 - num):
            item = QTableWidgetItem("")
            self.tableWidget.setHorizontalHeaderItem(i+num, item)
        self.tableWidget.setRowCount(0)
        self.MODE = "pay"
        self.B_MaT_CaA.setEnabled(0)
        self.B_Payone.setVisible(1)
        self.LB_no.setText('学号')
        self.LB_name.setText('处方号')
    
    def cha_or_add(self):
        M_name = self.LE_MaTname.text()
        M_no = self.LE_MaTno.text()
        if M_name == M_no == "":
            self.B_MaT_CaA.setText("添加")
            self.M_Mode = "add"
            return
        
        if M_no == '':
            return
        else:
            res = dbo.select(self.db,"pri_s_Mno",M_no)
            if res == ():
                self.B_MaT_CaA.setText("添加")
                self.M_Mode = 'add'
            else:
                self.B_MaT_CaA.setText("修改")
                self.M_Mode = 'cha'



        

    def payone(self):#单独付费
        n = self.tableWidget.currentRow()
        res_ = dbo.select(self.db,"fin_s_Sno_to_fins",self.res[n][0])
        if res_ == ():
            QMessageBox.warning(self,"错误","无此学生!")
        dbo.update(self.db,"Stu_fin",res_[0][0],res_[0][2]-self.res[n][-2],res_[0][3]+self.res[n][-2])
        a = dbo.update(self.db,"pri_onepay",self.res[n][0])
        if a == 0:
            QMessageBox.about(self,"success","缴费成功")

        print(2)
        pass

    def search(self):#搜索s
        if self.MODE == 'MaT':
            Mno = self.LE_no.text()
            Mname = self.LE_name.text()
            if Mno == Mname == '':
                res = dbo.select(self.db,"pri_n")
            elif Mno == '':
                res = dbo.select(self.db,"pri_s_Mname",Mname)
            elif Mname == '':
                res = dbo.select(self.db,"pri_s_Mno",Mno)
            else:
                res = dbo.select(self.db,"pri_D",Mno,Mname)
            self.show_res(res)
        else:
            Sno = self.LE_no.text()
            Pno = self.LE_name.text()
            if Sno == Pno == '':
                res = dbo.select(self.db,"pri_SP_n")
            elif Sno == '':
                res = dbo.select(self.db,"pri_SP_s_Pno",Pno)
            elif Pno == '':
                res = dbo.select(self.db,"pri_SP_s_Sno",Sno)
            else:
                res = dbo.select(self.db,"pri_SP_D",Sno,Pno)
            self.show_res(res)



        

    def MaT_CaA(self):#添加或修改药物
        self.statusbar.showMessage("Working")
        M_name = self.LE_MaTname.text()
        M_no = self.LE_MaTno.text()
        M_pri = self.DSB_MaTpri.value()
        if self.M_Mode == "add":
            if M_no == '':
                QMessageBox.warning(self,"信息缺失","请输入药物/治疗编码")
            elif M_no[0] not in ['M','T']:
                QMessageBox.warning(self,"信息错误","药物/医疗编码编码应以M/T开头")
            elif M_name == '':
                QMessageBox.warning(self,"信息缺失","请输入药物/治疗名称")
            else:
                a = dbo.insert(self.db,"MaT",(M_no,M_name,M_pri))
                if a == 0:
                    QMessageBox.about(self,"success","加入药物/治疗成功")
                else:
                    QMessageBox.warning(self,"fail","加入药物/治疗失败")
        else:
           
            if M_no == '':
                QMessageBox.warning(self,"信息缺失","请输入药物/治疗编码")
                return
            else:                    
                res = dbo.select(self.db,"pri_s_Mno",M_no)
                if M_name == '':
                    self.LE_MaTname.setText(res[0][1])
                    M_name = res[0][1]
                reply = QMessageBox.question(self,'确认',"是否确认修改?",QMessageBox.No|QMessageBox.Yes,QMessageBox.No)
                if reply == QMessageBox.No:
                    pass
                else:
                    a = dbo.update(self.db,"MaT",M_no,M_name,M_pri)
                    if a == 0:
                        QMessageBox.about(self,"success","修改药物/治疗成功")
                    else:
                        QMessageBox.warning(self,"fail","修改药物/治疗失败")
        self.statusbar.showMessage("Ready")
        return 

    def show_res(self,res):
        self.res = res
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
    db = pymysql.connect("localhost","pri_maker","123456","hospital")
    reg = Pri_Win(db)
    sys.exit(app.exec_())