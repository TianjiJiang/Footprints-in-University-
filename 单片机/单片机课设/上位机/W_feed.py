import sys
from PyQt5.QtCore import QThread
from PyQt5.QtWidgets import QMainWindow, QApplication,QTableWidgetItem,QAbstractItemView,QMessageBox
from ui.feed_set import Ui_MainWindow
import moniter
import W_main
import time
global thread_lock
# import moniter

class W_feed(QMainWindow,Ui_MainWindow) :
    def __init__(self,store_for_main):
        super(W_feed, self).__init__()
        self.Init()
        self.store_for_main = store_for_main
        print(self.plan)
    def Init(self):
        self.setupUi(self)
        self.PB_add.clicked.connect(self.add_plan)
        self.PB_back.clicked.connect(self.back)
        self.PB_conf.clicked.connect(self.conf_plan)
        self.PB_del.clicked.connect(self.del_plan)
        self.plan = moniter.getFeedPlan()
        self.plan_num = len(self.plan[0])
        self.colunm_set()
        self.TB_plan.verticalHeader().setVisible(False)
        self.TB_plan.setEditTriggers(QAbstractItemView.NoEditTriggers)
        self.TB_plan.setSelectionBehavior(QAbstractItemView.SelectRows)
        self.show()
    
    def add_plan(self):
        if self.plan_num < 10:
            self.plan_num += 1
            text = self.SB_feed_time.text()
            if len(text) == 1:
                text = '0' + text
            if text.encode() in self.plan[0]:
                QMessageBox.information(self,"注意",'此时间已经有计划，请删除原计划后重新设置',QMessageBox.Yes,QMessageBox.Yes)
            else:
                self.plan[0].append(text.encode())
                self.plan[1].append(eval(self.SB_feed_weight.text()))
                self.colunm_set()
        else:
            QMessageBox.critical(self,"警告","计划喂食次数过多，这会对您的宠物造成伤害",QMessageBox.Yes)  

    def del_plan(self):
        if self.TB_plan.selectedItems():
            print('deldel:'+ self.TB_plan.selectedItems()[0].text() + '-1')
            del self.plan[0][eval(self.TB_plan.selectedItems()[0].text())-1]
            del self.plan[1][eval(self.TB_plan.selectedItems()[0].text())-1]
            self.colunm_set()

    def conf_plan(self):
        if QMessageBox.question(self,"确认",'您确认新的喂食方案吗？',QMessageBox.Yes|QMessageBox.No,QMessageBox.Yes) == QMessageBox.Yes:
            print([i.decode() for i in self.plan[0]],self.plan[1])
            moniter.setFeedPlan([i.decode() for i in self.plan[0]],self.plan[1])
            time.sleep(1.5)
            self.back()
        else:
            pass

    def colunm_set(self):
        self.plan_num = len(self.plan[1])
        self.TB_plan.setRowCount(self.plan_num)
        for i in range(len(self.plan[0])):
            self.TB_plan.setItem(i,0,QTableWidgetItem(str(i+1)))
            self.TB_plan.setItem(i,1,QTableWidgetItem((self.plan[0][i].decode() + ':00:00')))
            self.TB_plan.setItem(i,2,QTableWidgetItem(str(self.plan[1][i]) + '0g'))
    
    def back(self):
        self.main = W_main.W_mian(self.store_for_main)
        self.main.show()
        self.hide()
        print("back")



if __name__ == "__main__":
    app = QApplication(sys.argv)
    ui = W_feed([])
    sys.exit(app.exec_())

    