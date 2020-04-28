execute_process(COMMAND "/home/zack/rob421/Marco_Polo_Sphero/ws/build/sphero_ros/sphero_ros/sphero_driver/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/zack/rob421/Marco_Polo_Sphero/ws/build/sphero_ros/sphero_ros/sphero_driver/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
