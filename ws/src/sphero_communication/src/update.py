#!/usr/bin/env python3

import rospy

#from nav_msgs.msg import OccupancyGrid
from std_msgs.msg import Int32
from std_msgs.msg import UInt8MultiArray
from std_msgs.msg import Bool

speed = 0
#grid = OccupancyGrid()

def tdoa_callback(time_diff):
    print(f"tdoa {time_diff}")
    if speed == 0:
        direction = Bool()
        if time_diff.data < 200:
            direction.data = 1
        else:
            direction.data = 0
        pub.publish(direction)

def analysis_callback(current_command):
    global speed
    speed = current_command.data[0];
    print(f"current speed {speed}")

if __name__ == "__main__":
    # Initialize the node
    rospy.init_node('update', log_level=rospy.DEBUG)

    # Setup publisher
    pub = rospy.Publisher('/update',Bool,queue_size=10)

    # Setup subscriber
    tdoa_sub = rospy.Subscriber('/tdoa',Int32,tdoa_callback)

    analysis_sub = rospy.Subscriber('/analysis',UInt8MultiArray,analysis_callback)

    print("update node ready")

    # Turn control over to ROS
    rospy.spin()
