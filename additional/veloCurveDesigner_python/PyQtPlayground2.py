from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import Qt


class _Bar(QtWidgets.QWidget):
    pass

class PowerBar(QtWidgets.QWidget):
    """
    Custom Qt Widget to show a power bar and dial.
    Demonstrating compound and custom-drawn widget.
    """

    def __init__(self, steps=5, *args, **kwargs):
        super(PowerBar, self).__init__(*args, **kwargs)

        layout = QtWidgets.QVBoxLayout()
        self._bar = _Bar()
        layout.addWidget(self._bar)

        self._dial = QtWidgets.QDial()
        layout.addWidget(self._dial)

        self.setLayout(layout)

from PyQt5 import QtCore, QtGui, QtWidgets
#from power_bar import PowerBar

app = QtWidgets.QApplication([])
volume = PowerBar()
volume.show()
app.exec_()

#https://www.learnpyqt.com/courses/custom-widgets/creating-your-own-custom-widgets/
#https://www.learnpyqt.com/courses/qt-creator/embed-pyqtgraph-custom-widgets-qt-app/