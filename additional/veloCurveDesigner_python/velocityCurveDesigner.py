# <Velocity Designer - A helper programm to design a velocity curve for the PimpMyPiano Project>
# Copyright (C) 2018  Jeremy Constantin Börker aka diGlitch

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button, RadioButtons

#Values for inital slider position and inital plot
sa = 1.3
sb = 0
sc = 0.34
sd = 0
sap = 0.5

# Map a value from one range (f and t) into another one (maxLim and minLim)
def map(x, f, t, minLim, maxLim):
    return (t + (f - t) * ((x - minLim) / (maxLim - minLim)));

def bezier(x, a, b, c, d, ap):
    c1 = np.multiply(np.power(1-x,ap), a)
    c2 = np.multiply(np.multiply(np.multiply(np.power(1-x,2), 3), b), x)
    c3 = np.multiply(np.multiply(np.multiply(1-x, np.power(x,2)), c), 3)
    c4 = np.multiply(np.power(x,3), d)
    sum = c1 + c2 + c3 + c4
    return map(sum, 0, 127, np.min(sum), np.max(sum))

# print given array in the folling format: { x_0, x_1, x_2, x_3, x_4 };
def printAsCArray(h):
    string = "{"
    for i in h:
        string = string + str(int(np.round(i))) + ", "
    string = string[:-2] + "};"
    print(string)

# Create constants
MAX_DURATION = 300
MIN_DURATION = 3	
TIMES = np.arange(MIN_DURATION, MAX_DURATION+1)
X = map(TIMES, 0, 1, MIN_DURATION, MAX_DURATION)

# Set up Plots
fig, ax = plt.subplots(7, 1,  gridspec_kw = {'height_ratios':[20, 2, 2, 2, 2, 2, 4]}, sharex=False, sharey=False)
fig.tight_layout()
ax = ax.flatten()
ax[0].set_xlabel('Duration in ms')
ax[0].set_ylabel('Velocity')
plt.subplots_adjust(left=0.1, right=0.90)
ax[0].plot(TIMES,bezier(X,sa,sb,sc,sd,sap) , lw=2, color='red') # Inital Plot
#ax[0].axis([MIN_DURATION, MAX_DURATION, 0, 128]) # Axis

# Create Sliders
sas = Slider(ax[1], 'a', 0.01, 4, valinit=sa)
sbs = Slider(ax[2], 'b', 0.01, 1, valinit=sb)
scs = Slider(ax[3], 'c', 0.01, 1, valinit=sc)
sds = Slider(ax[4], 'd', 0.01, 1, valinit=sd)
saps = Slider(ax[5], 'power a', 0.01, 1, valinit=sap)

# Update plot when sliders change
def update(val):
    ax[0].clear() #clear plot, slow
    ax[0].plot(TIMES,bezier(X,sas.val,sbs.val,scs.val,sds.val,saps.val) , lw=2, color='red')
    ax[0].set_xlabel('Duration in ms')
    ax[0].set_ylabel('Velocity')
    fig.canvas.draw_idle()

# Event handler
sas.on_changed(update)
sbs.on_changed(update)
scs.on_changed(update)
sds.on_changed(update)
saps.on_changed(update)

axcolor = 'lightgoldenrodyellow'

btnPrintArray = Button(ax[6], 'Print', color=axcolor, hovercolor='0.975')

def printArray(event):
    printAsCArray(bezier(X,sas.val,sbs.val,scs.val,sds.val,saps.val))
btnPrintArray.on_clicked(printArray)

plt.show()
