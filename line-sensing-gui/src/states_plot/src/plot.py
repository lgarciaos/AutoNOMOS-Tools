#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import Float32MultiArray

import numpy as np
import cv2

f = None

h = 512
w = 512

len_arr = 9
def callback(data):
	global f
	f = data
    # rospy.loginfo("I heard %s",data.data)


# Create a black image
img = np.zeros((512,512,3), np.uint8)

# Draw a diagonal blue line with thickness of 5 px
img = cv2.line(img,(0,0),(511,511),(255,0,0),5)

img = cv2.rectangle(img,(384,0),(510,128),(0,255,0),3)

img = cv2.circle(img,(447,63), 63, (0,0,255), -1)

img = cv2.ellipse(img,(256,256),(100,50),0,0,180,255,-1)

pts = np.array([[10,5],[20,30],[70,20],[50,10]], np.int32)
pts = pts.reshape((-1,1,2))
img = cv2.polylines(img,[pts],True,(0,255,255))

font = cv2.FONT_HERSHEY_SIMPLEX
cv2.putText(img,'OpenCV',(10,500), font, 4,(255,255,255),2,cv2.LINE_AA)

rospy.init_node('states_plot')
rospy.Subscriber("/localization_array", Float32MultiArray, callback)
# spin() simply keeps python from exiting until this node is stopped

def gen_lanes_img():
	global h
	global w
	global len_arr
	img = np.zeros((h,w,3), np.uint8)
	img = cv2.line(img,(2 * w / len_arr ,0),(2 * w / len_arr,511),(0,0,255),5)
	img = cv2.line(img,(7 * w / len_arr ,0),(7 * w / len_arr,511),(0,0,255),5)

	num_center_lines = 10
	for y in xrange(1, num_center_lines):
		if y % 2:
			img = cv2.line(img,(int(4.5 * w / len_arr),y * h / num_center_lines),(int(4.5 * w / len_arr), (y + 1) * h / num_center_lines ),(0,0,255),5)
		

	return img

def gen_plot_img(arr, img):
	
	global h
	global w
	# img = np.zeros((h,w,3), np.uint8)

	aux_1 = 0.0
	aux_2 = 0.0
	font = cv2.FONT_HERSHEY_SIMPLEX

	# print arr
	for val in xrange(0,len(arr)):
		bottom_right = ( (val + 1) * w / len(arr) , h)
		# print int( h * 1.0 / len(arr) )
		aux_1 += arr[val]
		aux_2 += h * arr[val]
		# top_left = (val * w / len(arr),h - (val+1) *  int( h * 1.0 / len(arr) ) ) 
		top_left = (val * w / len(arr),h - int(h * arr[val] ) ) 
		bottom_left = ( (val) * w / len(arr) ,h - int(h * arr[val] + 5 ) )
		img = cv2.rectangle(img,top_left,bottom_right,(0,255,0),3)

		str_val = '%.2f' % arr[val]
		cv2.putText(img, str_val, bottom_left, font, .75,(226, 226,52),1)
		cv2.putText(img, str(len(arr)), (0,50), font, .75, (226, 226, 52), 1)

	# print aux_1
	# print aux_2
	return img


while not rospy.is_shutdown():

	img = gen_lanes_img()
	# cv2.imshow('image',img)
	if f != None:
		# print f.data
		img = gen_plot_img(f.data, img)

		cv2.imshow('image',img)
	if cv2.waitKey(1) & 0xFF == ord('q'):
		break
	
	# rospy.spin()

cv2.destroyAllWindows()
# if __name__ == '__main__':
    # try:
        # keyboard_terminal()
    # except rospy.ROSInterruptException:
        # 
        # pass

