#-*-coding:utf-8-*-
'''医生窗体主程序'''

import sys
import pymysql
import sql.dbopr as dbo
from UI.Drui import Ui_mainWindow
from PyQt5.QtWidgets import * 

class Dr_Win(QMainWindow,Ui_mainWindow):
    def __init__(self,db = ""):
        super().__init__()
        self.db = db
        self.initUI()
        self.show()
        self.pre = [] #本次处方
        
    def initUI(self):
        self.setupUi(self)
        self.CB_Pno.activated[str].connect(self.refresh)
        self.B_add_MaT.clicked.connect(self.add_MaT)
        self.B_confirm.clicked.connect(self.confirm)
        self.B_del_MaT.clicked.connect(self.del_MaT)
        self.LE_Sno.editingFinished.connect(self.reitems)
        self.TB_MaT.setEditTriggers(QTableWidget.NoEditTriggers)
        

    def reitems(self):#刷新CB内的选项
        self.CB_Pno.clear()
        Sno = self.LE_Sno.text()
        if Sno == "":
            pass
        else:
            res = dbo.select(self.db,"Dr_Sno_to_Pno",Sno)
            if res == ():
                pass
            else:
                for i in res:
                    self.CB_Pno.addItem(i[0])
        
    def confirm(self):#确认
        Sno = self.LE_Sno.text()
        Pno = self.CB_Pno.currentText()
        sym = self.TE_sym.toPlainText()
        res = self.TE_res.toPlainText()
        if Pno == '':
            QMessageBox.about(self,"提醒","请先选择学生和处方号!")
        elif "请在这里书写" in [sym,res]:
            QMessageBox.about(self,"提醒","请先填写号症状及结论!")
        elif self.TE_res.isReadOnly():
            QMessageBox.about(self,"提醒","请对本次挂号进行诊断!")
        else:
            dbo.update(self.db,"Pno_to_sym_res",Sno,Pno,sym,res)
            for i in self.pre:
                print(dbo.insert(self.db,"Pre",(Pno,i[0],i[2],i[3],0)))
            QMessageBox.about(self,"success","成功!")

    def add_MaT(self):#增加处方
        Mno = self.LE_MaTno.text()
        Mname = self.LE_MaTname.text()
        num = self.MaTnum.value()
        if Mno == Mname == "":
            QMessageBox.about(self,"注意","请输入药品/治疗名称或编号")
        elif num == 0:
            QMessageBox.about(self,"注意","请输入药品/治疗数量")
        else:
            if Mno == "":
                res = dbo.select(self.db,"Dr_s_Mname_for_Mno_pri",Mname)
                if res != ():
                    self.LE_MaTno.setText(res[0][0])
                    Mno = res[0][0]
                    total = num * res[0][1]
                    self.pre.append((Mno,Mname,num,eval(str(total))))
                    self.show_res(self.pre)
                else:
                    QMessageBox.about(self,"提示","系统内暂时无此项目")
            else:
                res = dbo.select(self.db,"Dr_s_Mno_for_Mname_pri",Mno)
                if res != ():
                    self.LE_MaTname.setText(res[0][0])
                    Mname = res[0][0]
                    total = num * res[0][1]
                    self.pre.append((Mno,Mname,num,eval(str(total))))
                    self.show_res(self.pre)
                else:
                    QMessageBox.about(self,"提示","系统内暂时无此项目")
                
            

    def del_MaT(self):#减少处方
        n = self.TB_MaT.currentRow()
        del self.pre[n]
        self.show_res(self.pre)

       

    def refresh(self):#刷新对应的诊疗记录
        Sno = self.LE_Sno.text()
        Pno = self.CB_Pno.currentText()
        res = dbo.select(self.db,"Dr_D_Sno_Pno_for_sym_res",Sno,Pno)
        if res == ((None, None),):
            self.TE_sym.setPlainText("请在这里书写")
            self.TE_res.setPlainText("请在这里书写")
            self.TE_sym.setReadOnly(False)
            self.TE_res.setReadOnly(False)
        else:
            self.TE_sym.setPlainText(res[0][0])
            self.TE_res.setPlainText(res[0][1])
            self.TE_sym.setReadOnly(True)
            self.TE_res.setReadOnly(True)

    def show_res(self,res):
        row = 0
        self.TB_MaT.setRowCount(0)
        self.TB_MaT.setRowCount(len(res))
        for item in res:
            if item :
                column = 0
                for i in item:
                    _ = QTableWidgetItem(str(i))
                    self.TB_MaT.setItem(row,column,_)
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
    db = pymysql.connect("localhost","Dr","123456","hospital")
    reg = Dr_Win(db)
    sys.exit(app.exec_())