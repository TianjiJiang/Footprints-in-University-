# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'time_set.ui'
#
# Created by: PyQt5 UI code generator 5.13.2
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(446, 282)
        Dialog.setStyleSheet("")
        self.gridLayoutWidget = QtWidgets.QWidget(Dialog)
        self.gridLayoutWidget.setGeometry(QtCore.QRect(0, 10, 441, 261))
        self.gridLayoutWidget.setObjectName("gridLayoutWidget")
        self.gridLayout = QtWidgets.QGridLayout(self.gridLayoutWidget)
        self.gridLayout.setContentsMargins(7, 2, 12, 3)
        self.gridLayout.setHorizontalSpacing(15)
        self.gridLayout.setVerticalSpacing(8)
        self.gridLayout.setObjectName("gridLayout")
        self.LCD_TIME = QtWidgets.QLCDNumber(self.gridLayoutWidget)
        self.LCD_TIME.setDigitCount(8)
        self.LCD_TIME.setObjectName("LCD_TIME")
        self.gridLayout.addWidget(self.LCD_TIME, 2, 1, 1, 2)
        self.PB_cencel = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.PB_cencel.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.PB_cencel.setObjectName("PB_cencel")
        self.gridLayout.addWidget(self.PB_cencel, 5, 2, 1, 1)
        self.PB_confirm = QtWidgets.QPushButton(self.gridLayoutWidget)
        self.PB_confirm.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.PB_confirm.setObjectName("PB_confirm")
        self.gridLayout.addWidget(self.PB_confirm, 5, 0, 1, 1)
        self.CB_syTIme = QtWidgets.QCheckBox(self.gridLayoutWidget)
        self.CB_syTIme.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.CB_syTIme.setObjectName("CB_syTIme")
        self.gridLayout.addWidget(self.CB_syTIme, 3, 0, 1, 1)
        self.LCD_data = QtWidgets.QLCDNumber(self.gridLayoutWidget)
        self.LCD_data.setDigitCount(10)
        self.LCD_data.setMode(QtWidgets.QLCDNumber.Dec)
        self.LCD_data.setSegmentStyle(QtWidgets.QLCDNumber.Filled)
        self.LCD_data.setProperty("value", 1254.0)
        self.LCD_data.setProperty("intValue", 1254)
        self.LCD_data.setObjectName("LCD_data")
        self.gridLayout.addWidget(self.LCD_data, 1, 0, 1, 2)
        self.label = QtWidgets.QLabel(self.gridLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(20)
        self.label.setFont(font)
        self.label.setAlignment(QtCore.Qt.AlignBottom|QtCore.Qt.AlignHCenter)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 3)
        self.DTE = QtWidgets.QDateTimeEdit(self.gridLayoutWidget)
        self.DTE.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.DTE.setDateTime(QtCore.QDateTime(QtCore.QDate(2000, 1, 1), QtCore.QTime(23, 59, 59)))
        self.DTE.setObjectName("DTE")
        self.gridLayout.addWidget(self.DTE, 3, 1, 1, 1)
        self.gridLayout.setRowStretch(0, 2)
        self.gridLayout.setRowStretch(1, 2)
        self.gridLayout.setRowStretch(2, 2)
        self.gridLayout.setRowStretch(3, 2)
        self.gridLayout.setRowStretch(4, 1)
        self.gridLayout.setRowStretch(5, 2)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "时间设定"))
        self.PB_cencel.setText(_translate("Dialog", "返回"))
        self.PB_confirm.setText(_translate("Dialog", "确认"))
        self.CB_syTIme.setText(_translate("Dialog", "卫星时钟"))
        self.label.setText(_translate("Dialog", "当前系统时间"))
        self.DTE.setDisplayFormat(_translate("Dialog", "yyyy/MM/dd hh:mm:ss"))
