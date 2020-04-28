#!/usr/bin/env python3

import rospy

import random
import sys
from time import sleep

from pysphero.core import Sphero
from pysphero.driving import Direction

global mac_address

def main():
    with Sphero(mac_address=mac_address) as sphero:
        sphero.power.wake()

        for _ in range(5):
            sleep(2)
            speed = 255
            heading = 0
        #    speed = random.randint(50, 100)
        #    heading = random.randint(0, 360)
            print(f"Send drive with speed {speed} and heading {heading}")

            sphero.driving.drive_with_heading(speed, heading, Direction.forward)

        sphero.power.enter_soft_sleep()


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
    
    main()

    # Turn control over to ROS
    rospy.spin()
