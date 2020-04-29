#!/usr/bin/env python2

import rospy

from nav_msgs/OccupancyGrid.msg import OccupancyGrid
from std_msgs/Int32.msg import Int32
from std_msgs/Int8.msg import Int8

global speed = 0

def tdoa_callback(time_diff):
    if speed == 0:
        print(time_diff)

def analysis_callback(current_speed):
    speed = current_speed;

if __name__ == "__main__":
    # Initialize the node
    rospy.init_node('update', log_level=rospy.DEBUG)

    # Setup publisher
    pub = rospy.Publisher('/update',OccupancyGrid,queue_size=10)

    # Setup subscriber
    tdoa_sub = rospy.Subscriber('/tdoa',Int32,tdoa_callback)

    analysis_sub = rospy.Subscriber('/analysis_speed',Int8,analysis_callback)

    print("update node ready")

    # Turn control over to ROS
    rospy.spin()
