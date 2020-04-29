#!/usr/bin/env python3

import rospy

from std_msgs.msg import UInt8

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

def speed_callback(new_speed):
    global speed 
    speed = new_speed.data
    send()

def heading_callback(new_heading):
    global heading 
    heading = new_heading.data
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
    speed_sub = rospy.Subscriber('/analysis_speed',UInt8,speed_callback)
    heading_sub = rospy.Subscriber('/analysis_heading',UInt8,heading_callback)

    print("sphero setup")
    
    # Turn control over to ROS
    rospy.spin()
