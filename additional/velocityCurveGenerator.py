# Source: https://matplotlib.org/users/screenshots.html#slider-demo

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button, RadioButtons


def map(x, f, t, minLim, maxLim):
    return (t + (f - t) * ((x - minLim) / (maxLim - minLim)));
	
MAX_DURATION = 300
MIN_DURATION = 3	
times = np.arange(MIN_DURATION, MAX_DURATION+1)
x = map(times, 0, 1, MIN_DURATION, MAX_DURATION)

fig, ax = plt.subplots(5, 1,  gridspec_kw = {'height_ratios':[20, 2, 2, 2, 2]}, sharex=True, sharey=True)
#plt.subplots_adjust(left=None, bottom=None, right=None, top=None, wspace=None, hspace=0.5)
fig.tight_layout()
ax = ax.flatten()
ax[0].set_xlabel('Duration in ms')
ax[0].set_ylabel('Velocity')
plt.subplots_adjust(left=0.1, right=0.90)

t = times
a0 = 5
f0 = 3
s = np.multiply(np.power(1-x,3), 2)
#l, = plt.plot(t, s, lw=2, color='red')
ax[0].plot(t, x, lw=2, color='red')
ax[0].axis([MIN_DURATION, MAX_DURATION, 0, 128]) # Axis

axcolor = 'lightgoldenrodyellow'
#ax[1] = plt.axes([0.1, 0.15, 0.80, 0.03], facecolor=axcolor)
#axb = plt.axes([0.1, 0.1, 0.80, 0.03], facecolor=axcolor)
#axc = plt.axes([0.1, 0.05, 0.80, 0.03], facecolor=axcolor)
#axd = plt.axes([0.1, 0.01, 0.80, 0.03], facecolor=axcolor)

sa = Slider(ax[1], 'a', 0, 1, valinit=0)
sb = Slider(ax[2], 'b', 0, 1, valinit=1)
sc = Slider(ax[3], 'c', 0, 1, valinit=0)
sd = Slider(ax[4], 'd', 0, 1, valinit=1)

def update(val):
    a = sa.val # Pull Values from silders
    b = sb.val
    c = sc.val
    d = sd.val
    c1 = np.multiply(np.power(1-x,3), a)
    c2 = np.multiply(np.multiply(np.multiply(np.power(1-x,2), 3), b), x)
    c3 = np.multiply(np.multiply(np.multiply(1-x, np.power(x,2)), c), 3)
    c4 = np.multiply(np.power(x,3), d)
    sum = c1 + c2 + c3 + c4
    ax[0].set_ydata(map(sum, 0, 127, np.max(sum), np.min(sum))) ## Formula here
    fig.canvas.draw_idle()

# Event handler
sa.on_changed(update)
sb.on_changed(update)
sc.on_changed(update)
sd.on_changed(update)

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
