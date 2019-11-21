#!/usr/bin/env python

import rospy
from geometry_msgs.msg import Twist

class move_Robot:
    def __init__(self):
        self.cmd_vel_pub = rospy.Publisher('cmd_vel', Twist, queue_size=1)

        #self.red_light_twist = Twist()
        self.twist = Twist()
        self.twist.linear.x = 0.5
        rate = rospy.Rate(10)

        while not rospy.is_shutdown():
            self.cmd_vel_pub.publish(self.twist)
            #rate.sleep()


rospy.init_node('move_robot')
move_robot = move_Robot()
rospy.spin()