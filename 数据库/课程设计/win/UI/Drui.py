# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Dr.ui'
#
# Created by: PyQt5 UI code generator 5.12.1
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_mainWindow(object):
    def setupUi(self, mainWindow):
        mainWindow.setObjectName("mainWindow")
        mainWindow.resize(592, 600)
        mainWindow.setFocusPolicy(QtCore.Qt.ClickFocus)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("../source/8b508045ce50657990e3afe7843944b8.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        mainWindow.setWindowIcon(icon)
        self.centralwidget = QtWidgets.QWidget(mainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.horizontalLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.horizontalLayoutWidget.setGeometry(QtCore.QRect(0, 30, 591, 51))
        self.horizontalLayoutWidget.setObjectName("horizontalLayoutWidget")
        self.horizontalLayout = QtWidgets.QHBoxLayout(self.horizontalLayoutWidget)
        self.horizontalLayout.setContentsMargins(0, 0, 15, 0)
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(self.horizontalLayoutWidget)
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.LE_Sno = QtWidgets.QLineEdit(self.horizontalLayoutWidget)
        self.LE_Sno.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.LE_Sno.setObjectName("LE_Sno")
        self.horizontalLayout.addWidget(self.LE_Sno)
        self.label_2 = QtWidgets.QLabel(self.horizontalLayoutWidget)
        self.label_2.setObjectName("label_2")
        self.horizontalLayout.addWidget(self.label_2)
        self.CB_Pno = QtWidgets.QComboBox(self.horizontalLayoutWidget)
        self.CB_Pno.setObjectName("CB_Pno")
        self.horizontalLayout.addWidget(self.CB_Pno)
        self.horizontalLayout.setStretch(0, 1)
        self.horizontalLayout.setStretch(1, 3)
        self.horizontalLayout.setStretch(3, 3)
        self.gridLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(0, 90, 591, 161))
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setContentsMargins(15, 0, 12, 0)
        self.gridLayout.setObjectName("gridLayout")
        self.label_3 = QtWidgets.QLabel(self.gridLayoutWidget)
        self.label_3.setAlignment(QtCore.Qt.AlignCenter)
        self.label_3.setObjectName("label_3")
        self.gridLayout.addWidget(self.label_3, 0, 0, 1, 1)
        self.TE_sym = QtWidgets.QPlainTextEdit(self.gridLayoutWidget)
        self.TE_sym.setMaximumBlockCount(200)
        self.TE_sym.setObjectName("TE_sym")
        self.gridLayout.addWidget(self.TE_sym, 1, 0, 1, 1)
        self.TE_res = QtWidgets.QPlainTextEdit(self.gridLayoutWidget)
        self.TE_res.setMaximumBlockCount(200)
        self.TE_res.setObjectName("TE_res")
        self.gridLayout.addWidget(self.TE_res, 1, 1, 1, 1)
        self.label_4 = QtWidgets.QLabel(self.gridLayoutWidget)
        self.label_4.setAlignment(QtCore.Qt.AlignCenter)
        self.label_4.setObjectName("label_4")
        self.gridLayout.addWidget(self.label_4, 0, 1, 1, 1)
        self.gridLayoutWidget_2 = QtWidgets.QWidget(self.centralwidget)
        self.gridLayoutWidget_2.setGeometry(QtCore.QRect(0, 280, 591, 261))
        self.gridLayoutWidget_2.setObjectName("gridLayoutWidget_2")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.gridLayoutWidget_2)
        self.gridLayout_2.setContentsMargins(14, 0, 10, 0)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.B_del_MaT = QtWidgets.QPushButton(self.gridLayoutWidget_2)
        self.B_del_MaT.setFocusPolicy(QtCore.Qt.ClickFocus)
        self.B_del_MaT.setObjectName("B_del_MaT")
        self.gridLayout_2.addWidget(self.B_del_MaT, 1, 2, 1, 1)
        self.label_6 = QtWidgets.QLabel(self.gridLayoutWidget_2)
        self.label_6.setAlignment(QtCore.Qt.AlignCenter)
        self.label_6.setObjectName("label_6")
        self.gridLayout_2.addWidget(self.label_6, 0, 2, 1, 1)
        self.B_add_MaT = QtWidgets.QPushButton(self.gridLayoutWidget_2)
        self.B_add_MaT.setObjectName("B_add_MaT")
        self.gridLayout_2.addWidget(self.B_add_MaT, 1, 3, 1, 1)
        self.label_7 = QtWidgets.QLabel(self.gridLayoutWidget_2)
        self.label_7.setAlignment(QtCore.Qt.AlignCenter)
        self.label_7.setObjectName("label_7")
        self.gridLayout_2.addWidget(self.label_7, 1, 0, 1, 1)
        self.B_confirm = QtWidgets.QPushButton(self.gridLayoutWidget_2)
        self.B_confirm.setObjectName("B_confirm")
        self.gridLayout_2.addWidget(self.B_confirm, 1, 4, 1, 1)
        self.LE_MaTname = QtWidgets.QLineEdit(self.gridLayoutWidget_2)
        self.LE_MaTname.setObjectName("LE_MaTname")
        self.gridLayout_2.addWidget(self.LE_MaTname, 0, 3, 1, 2)
        self.label_5 = QtWidgets.QLabel(self.gridLayoutWidget_2)
        self.label_5.setAlignment(QtCore.Qt.AlignCenter)
        self.label_5.setObjectName("label_5")
        self.gridLayout_2.addWidget(self.label_5, 0, 0, 1, 1)
        self.LE_MaTno = QtWidgets.QLineEdit(self.gridLayoutWidget_2)
        self.LE_MaTno.setObjectName("LE_MaTno")
        self.gridLayout_2.addWidget(self.LE_MaTno, 0, 1, 1, 1)
        self.MaTnum = QtWidgets.QSpinBox(self.gridLayoutWidget_2)
        self.MaTnum.setObjectName("MaTnum")
        self.gridLayout_2.addWidget(self.MaTnum, 1, 1, 1, 1)
        self.TB_MaT = QtWidgets.QTableWidget(self.gridLayoutWidget_2)
        self.TB_MaT.setObjectName("TB_MaT")
        self.TB_MaT.setColumnCount(4)
        self.TB_MaT.setRowCount(0)
        item = QtWidgets.QTableWidgetItem()
        self.TB_MaT.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        self.TB_MaT.setHorizontalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        self.TB_MaT.setHorizontalHeaderItem(2, item)
        item = QtWidgets.QTableWidgetItem()
        self.TB_MaT.setHorizontalHeaderItem(3, item)
        self.gridLayout_2.addWidget(self.TB_MaT, 2, 0, 1, 5)
        self.gridLayout_2.setColumnStretch(0, 2)
        self.gridLayout_2.setRowStretch(0, 1)
        self.verticalLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.verticalLayoutWidget.setGeometry(QtCore.QRect(0, 250, 591, 31))
        self.verticalLayoutWidget.setObjectName("verticalLayoutWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.label_8 = QtWidgets.QLabel(self.verticalLayoutWidget)
        self.label_8.setAlignment(QtCore.Qt.AlignCenter)
        self.label_8.setObjectName("label_8")
        self.verticalLayout.addWidget(self.label_8)
        self.verticalLayoutWidget_2 = QtWidgets.QWidget(self.centralwidget)
        self.verticalLayoutWidget_2.setGeometry(QtCore.QRect(0, 0, 591, 31))
        self.verticalLayoutWidget_2.setObjectName("verticalLayoutWidget_2")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.verticalLayoutWidget_2)
        self.verticalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.label_10 = QtWidgets.QLabel(self.verticalLayoutWidget_2)
        self.label_10.setAlignment(QtCore.Qt.AlignCenter)
        self.label_10.setObjectName("label_10")
        self.verticalLayout_3.addWidget(self.label_10)
        mainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(mainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 592, 22))
        self.menubar.setObjectName("menubar")
        mainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(mainWindow)
        self.statusbar.setObjectName("statusbar")
        mainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(mainWindow)
        QtCore.QMetaObject.connectSlotsByName(mainWindow)

    def retranslateUi(self, mainWindow):
        _translate = QtCore.QCoreApplication.translate
        mainWindow.setWindowTitle(_translate("mainWindow", "诊断书系统"))
        self.label.setText(_translate("mainWindow", "学号"))
        self.label_2.setText(_translate("mainWindow", "处方号"))
        self.label_3.setText(_translate("mainWindow", "症状"))
        self.label_4.setText(_translate("mainWindow", "结论"))
        self.B_del_MaT.setText(_translate("mainWindow", "删除"))
        self.label_6.setText(_translate("mainWindow", "名称"))
        self.B_add_MaT.setText(_translate("mainWindow", "添加"))
        self.label_7.setText(_translate("mainWindow", "数量"))
        self.B_confirm.setText(_translate("mainWindow", "确认"))
        self.label_5.setText(_translate("mainWindow", "编号"))
        item = self.TB_MaT.horizontalHeaderItem(0)
        item.setText(_translate("mainWindow", "编号"))
        item = self.TB_MaT.horizontalHeaderItem(1)
        item.setText(_translate("mainWindow", "名称"))
        item = self.TB_MaT.horizontalHeaderItem(2)
        item.setText(_translate("mainWindow", "数量"))
        item = self.TB_MaT.horizontalHeaderItem(3)
        item.setText(_translate("mainWindow", "价格"))
        self.label_8.setText(_translate("mainWindow", "~~~~~~~~~~~~~~~~~~~~~~~~~~处方~~~~~~~~~~~~~~~~~~~~~~~~~~"))
        self.label_10.setText(_translate("mainWindow", "~~~~~~~~~~~~~~~~~~~~~~~~~~诊断~~~~~~~~~~~~~~~~~~~~~~~~~~"))


