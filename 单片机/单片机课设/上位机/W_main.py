import sys
from PyQt5.QtCore import QThread,pyqtSignal
from PyQt5.QtWidgets import QMainWindow, QApplication,QTableWidgetItem,QAbstractItemView
import moniter
import W_time
import time
import W_feed
from ui.main import Ui_MainWindow

class monit(QThread):
    status_chang = pyqtSignal(str)
    def __init__(self,serial):
        super(monit,self).__init__()
        self.serial = serial
        self.work = True
    def __del__(self):
        self.work = False
        self.wait()
    def run(self):
        while self.work:
            try:   
                re = self.serial.readline()
                print(re)
                if re == b'MOPEN\n':
                    self.status_chang.emit("MOPEN")
                elif re == b"MCLOSE\n":
                    self.status_chang.emit("MCLOSE")
                elif re == b'box opened\n':
                    self.status_chang.emit("box opened")
                elif re == b'box closed\n':
                    self.status_chang.emit("box closed")
                elif re ==b"feed start\n":
                    self.status_chang.emit("feed start")
                elif re == b"Feed over\n":
                    self.status_chang.emit("Feed over")
                elif re == b"Empty\n":
                    self.status_chang.emit("Empty")
                elif re == b"Not Empty\n":
                    self.status_chang.emit("Not Empty")
                else :
                    pass
                self.msleep(700)
            except:
                pass

    def stop(self):
        self.work = False

class W_mian(QMainWindow,Ui_MainWindow) :
    def __init__(self,store = []):
        super(W_mian, self).__init__()
        self.setupUi(self)
        self.recoder = store 
        self.init()
    def init(self):
        self.monit = monit(moniter.ser)
        self.monit.status_chang.connect(self.status)
        self.monit.status_chang.connect(self.newfeed)
        self.PB_feed.clicked.connect(self.soft_feed)
        self.action.triggered.connect(self.timeset_open)
        self.action_2.triggered.connect(self.feedset_open)
        self.TB_feed_record.verticalHeader().setVisible(False)
        self.TB_feed_record.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.TB_feed_record.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.monit.start()
        self.show()
    def status(self,re):
        if re == 'MOPEN':
            self.LB_statys.setText("强制开启")
        elif re == "MCLOSE":
            self.LB_statys.setText("强制关闭")
        elif re == "box opened":
            self.LB_statys.setText("存储罐打开")
        elif re == 'box closed':
            self.LB_statys.setText("存储罐关闭")
        elif re == "Empty":
            self.LB_statys.setText("存储罐空")
        elif re == "Not Empty":
            self.LB_statys.setText("一切正常")
        elif re == "feed start":
            self.LB_statys.setText("正在喂食")
        elif re == "Feed over":
            self.LB_statys.setText("喂食结束")
        else:
            pass
    def newfeed(self,re):
        if re == "Feed over":
            while True:
                self.time = moniter.gettime()
                if self.time:
                    break
            
            self.recoder.append(
                ('20' + self.time[0:2] + '-' + self.time [4:6] + '-' + self.time[6:8] + ' '
                + self.time[8:10] + ":" + self.time[10:12] +':' +self.time[12:14],"No Scales")
            )
            self.ReflashTable()
    def ReflashTable(self):
        self.TB_feed_record.setRowCount(len(self.recoder))
        for i in range(len(self.recoder)):
            self.TB_feed_record.setItem(i,0,QTableWidgetItem(str(i+1)))
            self.TB_feed_record.setItem(i,1,QTableWidgetItem((self.recoder[i][0])))
            self.TB_feed_record.setItem(i,2,QTableWidgetItem(str(self.recoder[i][1])))
    
    def soft_feed(self):
        moniter.sendcmd(moniter.ser,"M".encode())
    
    def timeset_open(self):
        self.monit.stop()
        self.WT = W_time.W_time(self.recoder)
        self.WT.show()
        self.hide()
        pass
    def feedset_open(self):
        self.monit.stop()
        self.WF = W_feed.W_feed(self.recoder)
        self.WF.show()
        self.hide()
        pass

if __name__ == "__main__":
    app = QApplication(sys.argv)
    ui = W_mian()

    sys.exit(app.exec_())