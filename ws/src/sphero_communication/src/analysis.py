#!/usr/bin/env python2

import rospy

from nav_msgs.msg import OccupancyGrid
from std_msgs.msg import UInt8MultiArray

def send(event):
    print("sending command")
    pub.publish(command)

def callback(grid):
    print("received grid")

    command.data[0] = 255
    command.data[1] = 0

if __name__ == "__main__":
    # Initialize the node
    rospy.init_node('update', log_level=rospy.DEBUG)

    # Setup publisher
    pub = rospy.Publisher('/analysis',UInt8MultiArray,queue_size=10)

    # Setup subscriber
    tdoa_sub = rospy.Subscriber('/update',OccupancyGrid,callback)

    command = UInt8MultiArray()
    
    command.data = [0, 0]

    print("analysis node ready")

    rospy.Timer(rospy.Duration(3), send) # Send commant every 3 seconds
    rospy.spin()
