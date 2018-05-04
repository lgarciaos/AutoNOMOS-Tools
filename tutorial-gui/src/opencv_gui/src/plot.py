#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Int32
from geometry_msgs.msg import Point

import numpy as np
import cv2

h = 512
w = 512
rectangle_num = None
point_msg = None

def rectangle_callback(msg):
	global rectangle_num
	rectangle_num = msg.data

def point_callback(msg):
	global point_msg
	point_msg = msg

rospy.init_node('opencv_gui')
rospy.Subscriber("/rectangle_tutorial", Int32, rectangle_callback)
rospy.Subscriber("/point_tutorial", Point, point_callback)


def draw_rectangle(img):
	global rectangle_num
	top_left = (100 - rectangle_num,(int) (100 - rectangle_num * 1.6) )
	bottom_right = (100 + rectangle_num, (int) (100 + rectangle_num * 1.6) )
	img = cv2.rectangle(img,top_left,bottom_right,(0,255,0),3)

	return img

def draw_line(img):
	
	global h
	global w
	point_b = (h/2, w/2)
	point_f = ( int(point_msg.x), int(point_msg.y))
	cv2.line(img,point_b,point_f,(255,0,0),5)

	return img

while not rospy.is_shutdown():

	img = np.zeros((h,w,3), np.uint8)

	font = cv2.FONT_HERSHEY_SIMPLEX
	cv2.putText(img,'OpenCV_tutorial',(10,500), font, 1,(255,255,255),2,cv2.LINE_AA)

	if rectangle_num != None:
		img = draw_rectangle(img)

	if point_msg != None:
		img = draw_line(img)

	cv2.imshow('image',img)	



	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
	

cv2.destroyAllWindows()