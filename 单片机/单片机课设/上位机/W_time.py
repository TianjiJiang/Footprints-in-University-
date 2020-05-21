import sys

from PyQt5.QtCore import QThread,pyqtSignal,QDateTime
from PyQt5.QtWidgets import QMainWindow, QApplication,QDialog
from ui.time_set import Ui_Dialog
import W_main
import moniter
import time

class reflashTime(QThread):
    newtime = pyqtSignal(str,str)
    def __init__(self,serial):
        super(reflashTime,self).__init__()
        self.serial = serial
        self.work = True
    def __del__(self):
        self.work = False
        self.wait()
    def run(self):
        while self.work :
            self.msleep(200)
            self.time = moniter.gettime()
            if self.time :
                self.sdate = '20' + self.time[0:2] + '-' + self.time [4:6] + '-' + self.time[6:8]
                self.stime = self.time[8:10] + ":" + self.time[10:12] +':' +self.time[12:14]
                self.newtime.emit(self.sdate,self.stime)
                pass
    def stop(self):
        self.work = False



class W_time(QDialog,Ui_Dialog) :
    def __init__(self,store_for_main):
        super(W_time, self).__init__()
        self.store_for_main = store_for_main
        self.init()
    
    def init(self):
        self.setupUi(self)
        self.PB_cencel.clicked.connect(self.cancel)
        self.PB_confirm.clicked.connect(self.conf)
        self.reflashTime = reflashTime(moniter.ser)
        self.reflashTime.start()
        self.reflashTime.newtime.connect(self.LcdReflash)
        self.CB_syTIme.stateChanged.connect(self.standerdTime)
        self.show()
    
    def conf(self):
        self.datetime= self.DTE.dateTime()
        self.datetime= str(self.datetime)[23:-1]
        self.datetime = self.datetime.replace(" ",'')
        self.datetime =self.datetime.split(',')
        del self.datetime[6:]
        for i in range(6):
            if len(self.datetime[i]) < 2:
                self.datetime[i] = '0' + self.datetime[i]
        self.datetime = ','.join(self.datetime)
        moniter.timeset(self.datetime)
        pass
    def cancel(self):
        self.reflashTime.stop()
        self.main = W_main.W_mian(self.store_for_main)
        self.main.show()
        self.hide()
    def LcdReflash(self,sdate,stime):
        self.LCD_data.display(sdate)
        self.LCD_TIME.display(stime)
        if self.CB_syTIme.isChecked():
            self.DTE.setDateTime(QDateTime.currentDateTime())
        
    def standerdTime(self):
        if self.CB_syTIme.isChecked():
            self.DTE.setEnabled(False)
            self.DTE.setDateTime(QDateTime.currentDateTime())
        else:
            self.DTE.setEnabled(True)
        pass


if __name__ == "__main__":
    app = QApplication(sys.argv)
    ui = W_time([])
    sys.exit(app.exec_())