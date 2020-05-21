import sys
import pymysql
sys.path += ["/home/tianji-jiang/Documents/数据库/正式数据库/win"]
from win import *
from PyQt5.QtWidgets import * 

class SYSTEMWINDOW(login_win.Log_Win):
     def __init__(self):
          super().__init__()
     

if __name__ == "__main__":
     app = QApplication(sys.argv)
     log = SYSTEMWINDOW()
     sys.exit(app.exec_())
    
