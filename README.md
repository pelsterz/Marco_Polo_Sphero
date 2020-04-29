# Marco_Polo_Sphero
 Marco Polo in bowling form. A Sphero BOLT pulls a trailer with two microphones to detect pins with speakers in them!

# Boot Up Process
1. Run the core:
```
roscore
```
2. Run the sphero node:
```
rosrun sphero_communication sphero.py _address:="D6:88:1B:3D:FC:66"
```
3. Run the analysis node:
```
rosrun sphero_communication analysis.py
```
4. Run the update node:
```
rosrun sphero_communication update.py
```
5. Run the rosserial node:
```
rosrun rosserial_arduino serial_node.py _port:=/dev/ttyUSB0
```
