# Source: https://matplotlib.org/users/screenshots.html#slider-demo

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button, RadioButtons

sa = 4
sap = 0.25
sb = 0
sc = 0.22
sd = 0

def map(x, f, t, minLim, maxLim):
    return (t + (f - t) * ((x - minLim) / (maxLim - minLim)));
	
def bezier(x, a, b, c, d, ap):
    c1 = np.multiply(np.power(1-x,ap), a)
    c2 = np.multiply(np.multiply(np.multiply(np.power(1-x,2), 3), b), x)
    c3 = np.multiply(np.multiply(np.multiply(1-x, np.power(x,2)), c), 3)
    c4 = np.multiply(np.power(x,3), d)
    sum = c1 + c2 + c3 + c4
    return map(sum, 0, 127, np.min(sum), np.max(sum))

MAX_DURATION = 300
MIN_DURATION = 3	
times = np.arange(MIN_DURATION, MAX_DURATION+1)
x = map(times, 0, 1, MIN_DURATION, MAX_DURATION)

fig, ax = plt.subplots(6, 1,  gridspec_kw = {'height_ratios':[20, 2, 2, 2, 2, 2]}, sharex=False, sharey=False)
fig.tight_layout()
ax = ax.flatten()
ax[0].set_xlabel('Duration in ms')
ax[0].set_ylabel('Velocity')
plt.subplots_adjust(left=0.1, right=0.90)

s = np.multiply(np.power(x,1), 1)
sv = map(s, 0, 127, np.min(s), np.max(s))

ax[0].plot(times,bezier(x,sa,sb,sc,sd,sap) , lw=2, color='red') # Inital Plot
#ax[0].axis([MIN_DURATION, MAX_DURATION, 0, 128]) # Axis

sas = Slider(ax[1], 'a', 0.01, 4, valinit=sa)
sbs = Slider(ax[2], 'b', 0.01, 1, valinit=sb)
scs = Slider(ax[3], 'c', 0.01, 1, valinit=sc)
sds = Slider(ax[4], 'd', 0.01, 1, valinit=sd)
saps = Slider(ax[5], 'power a', 0.01, 1, valinit=sap)

def update(val):
    ax[0].clear() #clear plot, slow
    ax[0].plot(times,bezier(x,sas.val,sbs.val,scs.val,sds.val,saps.val) , lw=2, color='red')
    ax[0].set_xlabel('Duration in ms')
    ax[0].set_ylabel('Velocity')
    fig.canvas.draw_idle()

# Event handler
sas.on_changed(update)
sbs.on_changed(update)
scs.on_changed(update)
sds.on_changed(update)
saps.on_changed(update)

#Reset Button
#resetax = plt.axes([0.8, 0.025, 0.1, 0.04])
#button = Button(resetax, 'Reset', color=axcolor, hovercolor='0.975')

def reset(event):
    sfreq.reset()
    samp.reset()
#button.on_clicked(reset)

#Color change radio buttons
#rax = plt.axes([0.025, 0.5, 0.15, 0.15], facecolor=axcolor)
#radio = RadioButtons(rax, ('red', 'blue', 'green'), active=0)

def colorfunc(label):
    l.set_color(label)
    fig.canvas.draw_idle()
#radio.on_clicked(colorfunc)

plt.show()
