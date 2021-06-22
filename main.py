#!/usr/bin/env python3
from PyQt5 import QtWidgets, uic
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import QIODevice

from random import randrange

# https://stackoverflow.com/questions/35932660/qcombobox-click-event обновление по клику

app = QtWidgets.QApplication([])
ui = uic.loadUi("./main.ui")
ui.setWindowTitle("li0ard EEPROM reader")

serial = QSerialPort()
serial.setBaudRate(9600)

def onRead():
	if not serial.canReadLine(): return
	rx = serial.readLine()
	data = str(rx, 'utf-8').strip().split(' ')

	if data[0] == "memcopy":
		read_data = data
		read_data.pop(0)
		read_data = "".join(read_data)

		random_num = str(randrange(999))
		random_num2 = str(randrange(999))
		f = open("dump_memory_" + random_num + "_" + random_num2 + ".bin", "wb")
		read_data = bytearray.fromhex(read_data)
		f.write(read_data)
		f.close()
		ui.keyCode.document().setPlainText("Файл сохранен как \"dump_memory_" + random_num + "_" + random_num2 + ".bin\"")
	else:
		ui.keyCode.document().setPlainText(" ".join(data));

def onOpen():
	serial.setPortName(ui.comL.currentText())
	serial.open(QIODevice.ReadWrite)

def onClose():
	serial.close()

def updateList():
	portList = []
	ports = QSerialPortInfo().availablePorts()
	for port in ports: portList.append(port.portName())
	ui.comL.clear()
	ui.comL.addItems(portList)

def serialSend(data):
	txs = ''.join(map(str, data)) + '\n'
	serial.write(txs.encode())

def setRead():
	serialSend("r")

serial.readyRead.connect(onRead)
ui.openB.clicked.connect(onOpen)
ui.closeB.clicked.connect(onClose)
ui.readBtn.clicked.connect(setRead)

updateList()

ui.show()
app.exec()