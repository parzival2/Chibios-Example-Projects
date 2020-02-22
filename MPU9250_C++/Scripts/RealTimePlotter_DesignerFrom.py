# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'realtime_plotter_designer.ui'
#
# Created by: PyQt5 UI code generator 5.12.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(672, 625)
        Form.setMinimumSize(QtCore.QSize(672, 625))
        self.gridLayout = QtWidgets.QGridLayout(Form)
        self.gridLayout.setObjectName("gridLayout")
        self.graphicsView = PlotWidget(Form)
        self.graphicsView.setObjectName("graphicsView")
        self.gridLayout.addWidget(self.graphicsView, 0, 0, 1, 1)
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.accelDataCheckBox = QtWidgets.QCheckBox(Form)
        self.accelDataCheckBox.setObjectName("accelDataCheckBox")
        self.horizontalLayout.addWidget(self.accelDataCheckBox)
        self.gyroDataCheckBox = QtWidgets.QCheckBox(Form)
        self.gyroDataCheckBox.setObjectName("gyroDataCheckBox")
        self.horizontalLayout.addWidget(self.gyroDataCheckBox)
        self.connectionStatus = QtWidgets.QLabel(Form)
        self.connectionStatus.setObjectName("connectionStatus")
        self.horizontalLayout.addWidget(self.connectionStatus)
        self.gridLayout.addLayout(self.horizontalLayout, 1, 0, 1, 1)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.accelDataCheckBox.setText(_translate("Form", "AccelData"))
        self.gyroDataCheckBox.setText(_translate("Form", "GyroData"))
        self.connectionStatus.setText(_translate("Form", "Not Connected"))


from pyqtgraph import PlotWidget
