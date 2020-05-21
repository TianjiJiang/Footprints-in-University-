# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'feed_set.ui'
#
# Created by: PyQt5 UI code generator 5.13.2
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(745, 474)
        MainWindow.setWindowOpacity(1.0)
        MainWindow.setAutoFillBackground(False)
        MainWindow.setStyleSheet("")
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(0, 10, 741, 441))
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setContentsMargins(6, 21, 9, 7)
        self.gridLayout.setHorizontalSpacing(26)
        self.gridLayout.setVerticalSpacing(31)
        self.gridLayout.setObjectName("gridLayout")
        self.PB_del = QtWidgets.QPushButton(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(13)
        self.PB_del.setFont(font)
        self.PB_del.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.PB_del.setObjectName("PB_del")
        self.gridLayout.addWidget(self.PB_del, 1, 0, 1, 1)
        self.SB_feed_time = QtWidgets.QSpinBox(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.SB_feed_time.setFont(font)
        self.SB_feed_time.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.SB_feed_time.setMaximum(23)
        self.SB_feed_time.setObjectName("SB_feed_time")
        self.gridLayout.addWidget(self.SB_feed_time, 0, 1, 1, 1)
        self.SB_feed_weight = QtWidgets.QSpinBox(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.SB_feed_weight.setFont(font)
        self.SB_feed_weight.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.SB_feed_weight.setMaximum(255)
        self.SB_feed_weight.setObjectName("SB_feed_weight")
        self.gridLayout.addWidget(self.SB_feed_weight, 0, 3, 1, 1)
        self.label_2 = QtWidgets.QLabel(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.label_2.setFont(font)
        self.label_2.setAlignment(QtCore.Qt.AlignCenter)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 0, 2, 1, 1)
        self.label = QtWidgets.QLabel(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.label.setFont(font)
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.label_3 = QtWidgets.QLabel(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(16)
        self.label_3.setFont(font)
        self.label_3.setAlignment(QtCore.Qt.AlignCenter)
        self.label_3.setObjectName("label_3")
        self.gridLayout.addWidget(self.label_3, 1, 1, 1, 2)
        self.PB_conf = QtWidgets.QPushButton(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(13)
        self.PB_conf.setFont(font)
        self.PB_conf.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.PB_conf.setStyleSheet("background-image: url(:/pic/bg.png);")
        self.PB_conf.setObjectName("PB_conf")
        self.gridLayout.addWidget(self.PB_conf, 3, 0, 1, 1)
        self.PB_add = QtWidgets.QPushButton(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(13)
        self.PB_add.setFont(font)
        self.PB_add.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.PB_add.setObjectName("PB_add")
        self.gridLayout.addWidget(self.PB_add, 1, 3, 1, 1)
        self.PB_back = QtWidgets.QPushButton(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(13)
        self.PB_back.setFont(font)
        self.PB_back.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.PB_back.setStyleSheet("background-image: url(:/pic/bg.png);")
        self.PB_back.setObjectName("PB_back")
        self.gridLayout.addWidget(self.PB_back, 3, 3, 1, 1)
        self.TB_plan = QtWidgets.QTableWidget(self.gridLayoutWidget)
        self.TB_plan.setObjectName("TB_plan")
        self.TB_plan.setColumnCount(3)
        self.TB_plan.setRowCount(0)
        item = QtWidgets.QTableWidgetItem()
        self.TB_plan.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.TB_plan.setHorizontalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        self.TB_plan.setHorizontalHeaderItem(2, item)
        self.TB_plan.horizontalHeader().setDefaultSectionSize(241)
        self.gridLayout.addWidget(self.TB_plan, 2, 0, 1, 4)
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "喂食方案设定"))
        self.PB_del.setText(_translate("MainWindow", "删除"))
        self.label_2.setText(_translate("MainWindow", "喂食量（10g）"))
        self.label.setText(_translate("MainWindow", "喂食时间"))
        self.label_3.setText(_translate("MainWindow", "当前喂食方案"))
        self.PB_conf.setText(_translate("MainWindow", "确认"))
        self.PB_add.setText(_translate("MainWindow", "添加"))
        self.PB_back.setText(_translate("MainWindow", "返回"))
        item = self.TB_plan.horizontalHeaderItem(0)
        item.setText(_translate("MainWindow", "序号"))
        item = self.TB_plan.horizontalHeaderItem(1)
        item.setText(_translate("MainWindow", "时间"))
        item = self.TB_plan.horizontalHeaderItem(2)
        item.setText(_translate("MainWindow", "重量"))
