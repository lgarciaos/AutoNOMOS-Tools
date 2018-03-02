#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
from std_msgs.msg import Int16
from std_msgs.msg import Int32
import sys,tty,termios
import curses


screen = None
start = 0
speed = 0
steering = 1400

def reset():
    global start
    global speed
    global steering
    start = 0
    speed = 0
    steering = 1400

def keyboard_terminal():
    pub_start = rospy.Publisher('/manual_control/stop_start', Int16, queue_size=1)
    pub_speed = rospy.Publisher('/manual_control/speed', Int32, queue_size=1)
    pub_steer = rospy.Publisher('/manual_control/steering', Int16, queue_size=1)
    rospy.init_node('keyboard_terminal', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    screen = curses.initscr()

    curses.noecho()
    curses.cbreak()
    screen.keypad(True)
    screen.addstr("Usage: \n")
    screen.addstr("\tUP: w or up arrow \n")
    screen.addstr("\tDOWN: s or down arrow \n")
    screen.addstr("\tRIGHT: d or right arrow \n")
    screen.addstr("\tLEFT: a or left arrow \n")
    screen.addstr("\tSTART/STOP: spacebar \n")
    global start
    global speed
    global steering
    reset()
    while not rospy.is_shutdown():
        c = screen.getch()
        if c == curses.KEY_UP or c == ord("w"):
            # pub.publish()
            speed += 10
            pub_speed.publish(speed)
        elif c == curses.KEY_DOWN or c == ord("s"):
            speed -= 10
            pub_speed.publish(speed)
        elif c == curses.KEY_LEFT or c == ord("a"):
            steering += 2
            pub_steer.publish(steering)
        elif c == curses.KEY_RIGHT or c == ord("d"):
            steering -= 2
            pub_steer.publish(steering)
        elif c == ord(" "):
            if start == 1:
                start = 0
            else:
                start = 1
            pub_start.publish(start)
        elif c == ord("r"):
            reset()
            pub_start.publish(start)
            pub_speed.publish(speed)
            pub_steer.publish(steering)
        elif c == 27:
            start = 0
            reset()
            pub_start.publish(start)
            pub_speed.publish(speed)
            pub_steer.publish(steering)

        screen.refresh()
        # screen.getch()
        # curses.endwin()
        # hello_str = "hello world %s" % rospy.get_time()
        # rospy.loginfo(hello_str)
        # pub.publish(hello_str)
        # rate.sleep()

    curses.nocbreak()
    screen.keypad(False)
    curses.echo()
    curses.endwin()
if __name__ == '__main__':
    try:
        keyboard_terminal()
    except rospy.ROSInterruptException:
        # 
        pass