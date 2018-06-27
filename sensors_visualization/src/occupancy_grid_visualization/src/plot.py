#!/usr/bin/env python
import rospy
# # from std_msgs.msg import Int32
# # from geometry_msgs.msg import Point
# from sensor_msgs.msg import LaserScan
from nav_msgs.msg import OccupancyGrid
import numpy as np
import cv2

h = None
w = None
laser_data = None
point_msg = None
x = 0
new_grid = True
img_h = 768 # must be even
img_w = 768 # must be even
grid_line_colors = (255, 255, 255)
grid_axis_color = (0, 0, 255)

def laser_callback(msg):
	global laser_data
	global h
	global w
	laser_data = msg.data
	h = msg.info.height
	w = msg.info.width



rospy.init_node('laser_occupancy_grid_visualization_node')
rospy.Subscriber("/laser_occupancy_grid", OccupancyGrid, laser_callback)

def draw_line(img, x_i, y_i, x_f, y_f):
	global grid_line_colors
	point_i = ( int(x_i), int(y_i))
	point_f = ( int(x_f), int(y_f))
	cv2.line(img, point_i, point_f, grid_line_colors, 1)
	return img

def draw_vertical_lines(img, y_i, y_f):
	for x in xrange(0,w):
		draw_line(img, x * img_w / w, y_i, x * img_w / w, y_f)
	cv2.line(img, (img_w / 2, y_i), (img_w / 2, y_f), grid_axis_color, 1)

def draw_horizontal_lines(img, x_i, x_f):
	for y in xrange(0,h):
		draw_line(img, x_i,  y * img_h / h, x_f, y * img_h / h)
	cv2.line(img, (x_i, img_h / 2), (x_f, img_h / 2), grid_axis_color, 1)

def draw_rectangles(img, x_i, y_i, x_f, y_f):
	for y in xrange(0, h):
		for x in xrange(0, w):
			# print "laser[", x + y * w , "]", laser_data[x + y * w]
			top_left = (x * img_w / w, (y + 1) * img_h / h )
			bottom_right = ((x + 1) * img_w / w, y * img_h / h)
			red = (41, 41, 178)
			orange = (68, 192, 255)
			blue = (255, 187, 0)
			if laser_data[x + y * w] <= -1:
				color = red
			else: #[sum(x) for x in zip(a,b)]
				# print laser_data[x + y * w]
				color = [sum(x) for x in zip (blue, (0, 0, int (255 - laser_data[x + y * w] * 255 / 100)))]
				# color = blue + (0, 0, int (255 - laser_data[x + y * w] * 255))
				# print color
			cv2.rectangle(img, top_left, bottom_right, color, -1)

			# cv2.rectangle(img, ())


def draw_grid(img):
	y_i = img_h
	y_f = 0
	x_i = 0
	x_f = img_w
	# print h, w
	draw_rectangles(img, x_i, y_i, x_f, y_f)
	draw_vertical_lines(img, y_i, y_f)
	draw_horizontal_lines(img, x_i, x_f)


while not rospy.is_shutdown():

	if h == None or w == None or laser_data == None:
		# for x in range (0,5):  
		img = np.zeros((img_h, img_w, 3), np.uint8)
		font = cv2.FONT_HERSHEY_SIMPLEX
		cv2.putText(img,'Waiting for topic',(10,500), font, 1,(255,255,255),2,cv2.LINE_AA)

	else:
		
		img = np.zeros((img_h, img_w, 3), np.uint8)
		draw_grid(img)

	
		# font = cv2.FONT_HERSHEY_SIMPLEX
		# cv2.putText(img,'OpenCV_tutorial',(10,500), font, 1,(255,255,255),2,cv2.LINE_AA)

		# if rectangle_num != None:
		# 	img = draw_rectangle(img)

		# if point_msg != None:
		# 	img = draw_line(img)

	cv2.imshow('laser_occupancy_grid_visualization_node',img)	



	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
	

cv2.destroyAllWindows()