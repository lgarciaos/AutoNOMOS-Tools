#!/bin/sh

export ROS_MASTER_URI=http://192.168.11.126:11311
export ROS_HOSTNAME=192.168.11.98

#. ./devel/setup.bash

rqt_image_view &
rosrun keyboard_control keyboard_terminal.py
