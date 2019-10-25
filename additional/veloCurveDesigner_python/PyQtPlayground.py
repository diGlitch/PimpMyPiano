import sys
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QLineEdit, QLabel, QVBoxLayout
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import pyqtSlot
from PyQt5.QtGui import QPainter, QBrush, QPen
from PyQt5.QtGui import QMouseEvent
from PyQt5.QtCore import Qt
from qtpy import QtWidgets


class PowerBar(QtWidgets.QWidget):
    """
    Custom Qt Widget to show a power bar and dial.
    Demonstrating compound and custom-drawn widget.
    """

    def __init__(self, steps=5, *args, **kwargs):
        super(PowerBar, self).__init__(*args, **kwargs)

        layout = QtWidgets.QVBoxLayout()
        #self._bar = _Bar()
        #layout.addWidget(self._bar)

        self._dial = QtWidgets.QDial()
        layout.addWidget(self._dial)

        self.setLayout(layout)

class CustomCircle(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        #self.setAcceptDrops(True)

    def repaint(self):
        print("test")

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setPen(Qt.red)

        painter.setPen(Qt.blue)
        painter.setBrush(QBrush(Qt.red, Qt.SolidPattern))

        painter.drawEllipse(250, 250, 50, 50)

class App(QWidget):

    def __init__(self):
        super().__init__()
        self.title = 'PyQt5 drag and drop - pythonspot.com'
        self.left = 10
        self.top = 10
        self.width = 500
        self.height = 500
        self.initUI()

    def initUI(self):
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)

        editBox = QLineEdit('Drag this', self)
        editBox.setDragEnabled(True)
        editBox.move(10, 10)
        editBox.resize(100, 32)

        #button = CustomLabel('Drop here.', self)
        #button.move(130, 15)

        c = PowerBar()
        c.show()

        self.show()

    def mousePressEvent(self, e:QMouseEvent):
        print("Mouse Press Event ", e)

    def mouseMoveEvent(self, e:QMouseEvent):
        print("Mouse Move Event ", e)

    def mouseReleaseEvent(self, e:QMouseEvent):
        print("Mouse Release Event ", e)

    @pyqtSlot()
    def on_click(self):
        print('PyQt5 button click')


class CustomLabel(QLabel):

    def __init__(self, title, parent):
        super().__init__(title, parent)
        self.setAcceptDrops(True)

    def dragEnterEvent(self, e):
        if e.mimeData().hasFormat('text/plain'):
            e.accept()
        else:
            e.ignore()

    def dropEvent(self, e):
        self.setText(e.mimeData().text())


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())
