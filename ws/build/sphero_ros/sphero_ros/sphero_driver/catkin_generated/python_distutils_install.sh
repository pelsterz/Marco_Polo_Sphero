#!/bin/sh

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/zack/rob421/Marco_Polo_Sphero/ws/src/sphero_ros/sphero_ros/sphero_driver"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/zack/rob421/Marco_Polo_Sphero/ws/install/lib/python2.7/dist-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/zack/rob421/Marco_Polo_Sphero/ws/install/lib/python2.7/dist-packages:/home/zack/rob421/Marco_Polo_Sphero/ws/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/zack/rob421/Marco_Polo_Sphero/ws/build" \
    "/usr/bin/python2" \
    "/home/zack/rob421/Marco_Polo_Sphero/ws/src/sphero_ros/sphero_ros/sphero_driver/setup.py" \
    build --build-base "/home/zack/rob421/Marco_Polo_Sphero/ws/build/sphero_ros/sphero_ros/sphero_driver" \
    install \
    --root="${DESTDIR-/}" \
    --install-layout=deb --prefix="/home/zack/rob421/Marco_Polo_Sphero/ws/install" --install-scripts="/home/zack/rob421/Marco_Polo_Sphero/ws/install/bin"