#!/usr/bin/env python2

import rospy

from nav_msgs/OccupancyGrid.msg import OccupancyGrid
from std_msgs/Int8.msg import Int8

global speed = 255
global heading = 0

def grid_callback(grid):
    print("received grid")

    speed_pub.publish(speed)

    heading_pub.publish(heading)

if __name__ == "__main__":
    # Initialize the node
    rospy.init_node('update', log_level=rospy.DEBUG)

    # Setup publisher
    speed_pub = rospy.Publisher('/analysis_speed',Int8,queue_size=10)
    heading_pub = rospy.Publisher('/analysis_heading',Int8,queue_size=10)

    # Setup subscriber
    tdoa_sub = rospy.Subscriber('/update',OccupancyGrid,grid_callback)

    print("analysis node ready")

    # Turn control over to ROS
    rospy.spin()

