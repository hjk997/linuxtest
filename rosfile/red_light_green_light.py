#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import Bool

class move_Robot:
    global cmd_vel_pub, green_light_twist, red_light_twist
    def __init__(self):
        self.cmd_vel_pub = rospy.Publisher('cmd_vel', Twist, queue_size=1)
        stoprobot = rospy.Subscriber('stopmsg', Bool, self.stop_callback)

        self.red_light_twist = Twist()
        self.green_light_twist = Twist()
        self.green_light_twist.linear.x = 0.5

        self.driving_forward = False
       # light_change_time = rospy.Time.now()
        #rate = rospy.Rate(10)


    def stop_callback(msgb):
        #cmd_vel_pub.publish(green_light_twist)
        if msgb.data:  # go
            print(msgb.data)
            cmd_vel_pub.publish(red_light_twist)
        else:  # stop
            print(msgb.data)
            cmd_vel_pub.publish(green_light_twist)


rospy.init_node('red_light_green_light')
move_robot = move_Robot()
rospy.spin()
'''
    # have to change when add color info
    if rospy.Time.now() > light_change_time:
        driving_forward = not driving_forward
        light_change_time = rospy.Time.now() + rospy.Duration(3)
    rate.sleep()
'''