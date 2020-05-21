# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'main.ui'
#
# Created by: PyQt5 UI code generator 5.13.2
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(525, 449)
        MainWindow.setStyleSheet("")
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(10, 0, 501, 391))
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setContentsMargins(14, 4, 15, 9)
        self.gridLayout.setHorizontalSpacing(32)
        self.gridLayout.setVerticalSpacing(13)
        self.gridLayout.setObjectName("gridLayout")
        self.TB_feed_record = QtWidgets.QTableWidget(self.gridLayoutWidget)
        self.TB_feed_record.setAutoScrollMargin(16)
        self.TB_feed_record.setObjectName("TB_feed_record")
        self.TB_feed_record.setColumnCount(3)
        self.TB_feed_record.setRowCount(0)
        item = QtWidgets.QTableWidgetItem()
        self.TB_feed_record.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.TB_feed_record.setHorizontalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        self.TB_feed_record.setHorizontalHeaderItem(2, item)
        self.TB_feed_record.horizontalHeader().setDefaultSectionSize(156)
        self.gridLayout.addWidget(self.TB_feed_record, 2, 0, 3, 1)
        self.PB_feed = QtWidgets.QPushButton(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.PB_feed.setFont(font)
        self.PB_feed.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.PB_feed.setObjectName("PB_feed")
        self.gridLayout.addWidget(self.PB_feed, 1, 0, 1, 1)
        self.LB_statys = QtWidgets.QLabel(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(16)
        self.LB_statys.setFont(font)
        self.LB_statys.setAlignment(QtCore.Qt.AlignCenter)
        self.LB_statys.setObjectName("LB_statys")
        self.gridLayout.addWidget(self.LB_statys, 0, 0, 1, 1)
        self.gridLayout.setColumnStretch(0, 1)
        self.gridLayout.setRowStretch(0, 3)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 525, 28))
        self.menubar.setObjectName("menubar")
        self.menu = QtWidgets.QMenu(self.menubar)
        self.menu.setObjectName("menu")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.action = QtWidgets.QAction(MainWindow)
        self.action.setObjectName("action")
        self.action_2 = QtWidgets.QAction(MainWindow)
        self.action_2.setObjectName("action_2")
        self.menu.addAction(self.action)
        self.menu.addAction(self.action_2)
        self.menubar.addAction(self.menu.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "宠物喂食系统"))
        item = self.TB_feed_record.horizontalHeaderItem(0)
        item.setText(_translate("MainWindow", "序号"))
        item = self.TB_feed_record.horizontalHeaderItem(1)
        item.setText(_translate("MainWindow", "时间"))
        item = self.TB_feed_record.horizontalHeaderItem(2)
        item.setText(_translate("MainWindow", "重量"))
        self.PB_feed.setText(_translate("MainWindow", "喂食"))
        self.LB_statys.setText(_translate("MainWindow", "系统状态"))
        self.menu.setTitle(_translate("MainWindow", "参数设定"))
        self.action.setText(_translate("MainWindow", "时间校正"))
        self.action_2.setText(_translate("MainWindow", "喂食方案"))
