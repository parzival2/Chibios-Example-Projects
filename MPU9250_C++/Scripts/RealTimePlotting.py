from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import QObject, QIODevice
from PyQt5.QtWidgets import QApplication, QWidget
import PyQt5.QtGui as QtGui
from Scripts.RealTimePlotter_DesignerFrom import Ui_Form
import re
import pyqtgraph as pg
import numpy as np
from collections import deque

# Set background to white
pg.setConfigOption('background', 'w')


class RealTimePlotter(QWidget, Ui_Form):
    def __init__(self):
        super(RealTimePlotter, self).__init__()
        # Setupui
        self.setupUi(self)
        # Create a serial port
        self.__serialPort = QSerialPort()
        # Setup Serialport
        # We are using USB serial driver, so the baud rate doesn't matter
        self.__serialPort.setBaudRate(QSerialPort.Baud1200, QSerialPort.Input)
        self.destroyed.connect(self.close)
        # Get the list of all available serial ports
        portsList = QSerialPortInfo.availablePorts()
        # Regex object for extracting numbers
        self.__numbersRegexObj = re.compile(r"[-+]?\d*\.?\d+")
        self.__accelRegexObj = re.compile(r"Accel \[X : [-+]?\d*\.?\d+, Y : [-+]?\d*\.?\d+, Z : [-+]?\d*\.?\d+")
        self.__gyroRegexObj = re.compile(r"Gyro \[X : [-+]?\d*\.?\d+, Y : [-+]?\d*\.?\d+, Z : [-+]?\d*\.?\d+")
        # Switch on Gyro and accel data
        self.accelDataCheckBox.stateChanged.connect(self.__onAccelDataCheckBoxChecked)
        self.gyroDataCheckBox.stateChanged.connect(self.__onGyroDataCheckBoxChecked)
        # Only connect to Chibios port
        chibiOsPort = None
        self.show()
        for port in portsList:
            if ("ChibiOS" in port.description()):
                chibiOsPort = port
        # Check of the device is connected.
        if (chibiOsPort is None):
            # We didn't find anything
            statusString = "Cannot find Chibios based device."
            self.connectionStatus.setText(statusString)
        else:
            # Dynamic arrays since numpy append is slow
            # self.__accelDataArray = DynamicArray((None,1,3))
            self.__accelDataXArray = deque([0], maxlen=1000)
            self.__accelDataYArray = deque([0], maxlen=1000)
            self.__accelDataZArray = deque([0], maxlen=1000)
            # Gyro
            self.__gyroDataXArray = deque([0], maxlen=1000)
            self.__gyroDataYArray = deque([0], maxlen=1000)
            self.__gyroDataZArray = deque([0], maxlen=1000)
            statusString = "Connected to : " + chibiOsPort.description()
            self.connectionStatus.setText(statusString)
            # Set the serial port
            self.__serialPort.setPort(chibiOsPort)
            self.__serialPort.setDataBits(QSerialPort.Data8)
            self.__serialPort.setFlowControl(QSerialPort.NoFlowControl)
            self.__serialPort.setParity(QSerialPort.NoParity)
            self.__serialPort.setStopBits(QSerialPort.OneStop)
            # Connect signals and slots
            self.__serialPort.readyRead.connect(self.__onSerialPortReadyRead)
            # Open the device
            self.__serialPort.open(QIODevice.ReadOnly)
            # Create curves for Accel and Gyro data
            # Accel Curve
            self.__accelXDataCurve = pg.PlotCurveItem()
            self.__accelYDataCurve = pg.PlotCurveItem()
            self.__accelZDataCurve = pg.PlotCurveItem()
            # Set pen
            self.__accelXDataCurve.setPen(pg.mkPen('r'), width=1)
            self.__accelYDataCurve.setPen(pg.mkPen('g'), width=1)
            self.__accelZDataCurve.setPen(pg.mkPen('b'), width=1)
            # Gyro curve
            self.__gyroXDataCurve = pg.PlotCurveItem()
            self.__gyroYDataCurve = pg.PlotCurveItem()
            self.__gyroZDataCurve = pg.PlotCurveItem()
            # Set pen
            self.__gyroXDataCurve.setPen(pg.mkPen('r'), width=1)
            self.__gyroYDataCurve.setPen(pg.mkPen('g'), width=1)
            self.__gyroZDataCurve.setPen(pg.mkPen('b'), width=1)
            # Add curves to plot
            self.graphicsView.addItem(self.__accelXDataCurve)
            self.graphicsView.addItem(self.__accelYDataCurve)
            self.graphicsView.addItem(self.__accelZDataCurve)
            self.graphicsView.addItem(self.__gyroXDataCurve)
            self.graphicsView.addItem(self.__gyroYDataCurve)
            self.graphicsView.addItem(self.__gyroZDataCurve)

    def __onSerialPortReadyRead(self):
        while (self.__serialPort.canReadLine()):
            bytesRead = self.__serialPort.readLine()
            strBytesRead = str(bytesRead)
            accelData = self.__accelRegexObj.findall(strBytesRead)
            gyroData = self.__gyroRegexObj.findall(strBytesRead)
            if (accelData and self.accelDataCheckBox.isChecked()):
                strFloats = self.__numbersRegexObj.findall(accelData[0])
                self.__accelDataXArray.append(float(strFloats[0]))
                self.__accelDataYArray.append(float(strFloats[1]))
                self.__accelDataZArray.append(float(strFloats[2]))
                # numpyFloats = np.asarray(strFloats, dtype=float).reshape((1,3))
                # self.__accelDataArray.append(numpyFloats)
                # numpyMat = self.__accelDataArray.getNumpyMatrix()
                self.__accelXDataCurve.setData(list(self.__accelDataXArray))
                self.__accelYDataCurve.setData(list(self.__accelDataYArray))
                self.__accelZDataCurve.setData(list(self.__accelDataZArray))
            elif (gyroData and self.gyroDataCheckBox.isChecked()):
                strGFloats = self.__numbersRegexObj.findall(gyroData[0])
                self.__gyroDataXArray.append(float(strGFloats[0]))
                self.__gyroDataYArray.append(float(strGFloats[1]))
                self.__gyroDataZArray.append(float(strGFloats[2]))
                self.__gyroXDataCurve.setData(list(self.__gyroDataXArray))
                self.__gyroYDataCurve.setData(list(self.__gyroDataYArray))
                self.__gyroZDataCurve.setData(list(self.__gyroDataZArray))

    def closeEvent(self, a0: QtGui.QCloseEvent) -> None:
        # On close, close the serial connection
        print("Closing serial port")
        self.__serialPort.close()

    def __onAccelDataCheckBoxChecked(self):
        self.__gyroXDataCurve.clear()
        self.__gyroYDataCurve.clear()
        self.__gyroZDataCurve.clear()
        if (self.accelDataCheckBox.isChecked()):
            self.gyroDataCheckBox.setCheckable(False)

        elif (not self.accelDataCheckBox.isChecked()):
            self.gyroDataCheckBox.setCheckable(True)

    def __onGyroDataCheckBoxChecked(self):
        self.__accelXDataCurve.clear()
        self.__accelYDataCurve.clear()
        self.__accelZDataCurve.clear()
        if (self.gyroDataCheckBox.isChecked()):
            self.accelDataCheckBox.setCheckable(False)
        elif (not self.gyroDataCheckBox.isChecked()):
            self.accelDataCheckBox.setCheckable(True)


if __name__ == '__main__':
    app = QApplication([])
    realTime = RealTimePlotter()
    app.exec()
