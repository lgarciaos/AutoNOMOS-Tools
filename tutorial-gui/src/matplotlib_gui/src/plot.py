#!/usr/bin/env python

import rospy
from std_msgs.msg import Float32
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import random
from matplotlib import style



style.use('fivethirtyeight')

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)
xs = []
ys = []
x_next = 0
next_y = None

def animate(i):
	global x_next
	global xs 
	global ys 
	xs.append(x_next)

	if next_y != None:
		ys.append(next_y)
	else:
		ys.append(random.uniform(1,10))
	x_next += 1
	ax1.clear()
	ax1.plot(xs, ys)

def plot_y_callback(msg):
	global next_y
	next_y = msg.data

rospy.init_node('matplotlib_gui')
rospy.Subscriber("/plot_y", Float32, plot_y_callback)
ani = animation.FuncAnimation(fig, animate, interval=1000)
plt.show()