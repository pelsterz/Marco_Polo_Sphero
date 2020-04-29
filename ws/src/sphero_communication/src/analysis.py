#!/usr/bin/env python2

import rospy

#from nav_msgs.msg import OccupancyGrid
from std_msgs.msg import UInt16MultiArray
from std_msgs.msg import Bool

received_direction = False
last_direction = 0

def send(event):
    print("sending command")
    global received_direction
    if not received_direction:
        command.data[0] = 0
    
    pub.publish(command)

    received_direction = False

def callback(direction):
    print("received direction")
    global received_direction
    global last_direction

    command.data[0] = 200
    if direction.data:
        if last_direction:
            if (command.data[1] - 10) < 0:
                command.data[1] = 255 + command.data[1] - 10
            else:
                command.data[1] -= 10
        else:
            command.data[1] += 5

    last_direction = direction.data
    received_direction = True

if __name__ == "__main__":
    # Initialize the node
    rospy.init_node('analysis', log_level=rospy.DEBUG)

    # Setup publisher
    pub = rospy.Publisher('/analysis',UInt16MultiArray,queue_size=10)

    # Setup subscriber
    tdoa_sub = rospy.Subscriber('/update',Bool,callback)

    command = UInt16MultiArray()
    
    command.data = [0, 0]

    print("analysis node ready")

    rospy.Timer(rospy.Duration(5), send) # Send commant every 5 seconds
    rospy.spin()
