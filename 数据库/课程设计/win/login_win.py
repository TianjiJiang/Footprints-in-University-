#-*-coding:utf-8-*-
'''登录窗体主程序'''
import sys
import pymysql
import sql.dbopr as dbo
from Dr_win import Dr_Win
from reg_win import Reg_Win
from fin_win import Fin_Win
from pri_win import Pri_Win
from UI.logui import Ui_mainWindow
from PyQt5.QtWidgets import * 

class Log_Win(QMainWindow,Ui_mainWindow):
     def __init__(self):
          super().__init__()
          self.setupUi(self)
          self.show()
          self.db = ''


     def login(self):
          try:
               name = self.lineEdit.text()
               password = self.lineEdit_2.text()
               self.db = pymysql.connect("localhost",name,password,"hospital")
               QMessageBox.about(self,"Welcome","登录成功")
               user = dbo.who(self.db)
               if user[0] == 'root@localhost':
                    print("root")
                    pass
               elif user[0] == 'reg_admin@localhost':
                    self.win = Reg_Win(self.db)
                    self.hide()
                    print('ok')
               elif user[0] == 'Dr@localhost':
                    self.win = Dr_Win(self.db)
                    self.hide()
                    print('ok')
               elif user[0] == 'fin_staff@localhost':
                    self.win = Fin_Win(self.db)
                    self.hide()
                    print('ok')
               elif user[0] == "pri_maker@localhost":
                    self.win = Pri_Win(self.db)
                    self.hide()
                    print('ok')
               return 
          except:
               QMessageBox.warning(self,"Warnning","登录失败",QMessageBox.Yes)
               self.lineEdit.setText("")
               self.lineEdit_2.setText("")
               print("i fales")
               pass

               
     def closeEvent(self,event):
          reply = QMessageBox.question(self,'Message',"你是否确认退出?",QMessageBox.Yes|QMessageBox.No,QMessageBox.No)
          if reply == QMessageBox.Yes:
               event.accept()
          else:
               event.ignore()


if __name__ == "__main__":
     app = QApplication(sys.argv)
     log = Log_Win()
     sys.exit(app.exec_())