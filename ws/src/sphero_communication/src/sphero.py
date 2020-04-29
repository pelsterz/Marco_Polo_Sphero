#!/usr/bin/env python3

import rospy

from std_msgs.msg import UInt16MultiArray

import sys
from time import sleep

from pysphero.core import Sphero
from pysphero.driving import Direction

global mac_address
speed = 0
heading = 0

def send():
    with Sphero(mac_address=mac_address) as sphero:
        sphero.power.wake()

        sleep(2)
        print(f"Send drive with speed {speed} and heading {heading}")

        sphero.driving.drive_with_heading(speed, heading, Direction.forward)

        sphero.power.enter_soft_sleep()

def callback(new_data):
    global speed 
    global heading
    speed = new_data.data[0]
    heading = new_data.data[1]
    send()

if __name__ == "__main__":
    # Initilize the node
    rospy.init_node('sphero', log_level=rospy.DEBUG)

    name = rospy.get_name()
    # Get address from parameters
    try:
        mac_address = rospy.get_param('%s/address'%name)
    except KeyError:
        print("Address not provided")
        sys.exit()
    
    # Setup subscriber
    sub = rospy.Subscriber('/analysis',UInt16MultiArray,callback)

    print("sphero setup")
    
    # Turn control over to ROS
    rospy.spin()
