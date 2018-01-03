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
    DESTDIR_ARG="--root=$DESTDIR"
fi

echo_and_run() { echo "+ $@" ; "$@" ; }

echo_and_run cd "/home/gary/AutoNOMOS-Tools/line-sensing-gui/src/main_gui"

# ensure that Python install destination exists
echo_and_run mkdir -p "$DESTDIR/home/gary/AutoNOMOS-Tools/line-sensing-gui/install/lib/python2.7/site-packages"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
echo_and_run /usr/bin/env \
    PYTHONPATH="/home/gary/AutoNOMOS-Tools/line-sensing-gui/install/lib/python2.7/site-packages:/home/gary/AutoNOMOS-Tools/line-sensing-gui/build/lib/python2.7/site-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/gary/AutoNOMOS-Tools/line-sensing-gui/build" \
    "/usr/bin/python" \
    "/home/gary/AutoNOMOS-Tools/line-sensing-gui/src/main_gui/setup.py" \
    build --build-base "/home/gary/AutoNOMOS-Tools/line-sensing-gui/build/main_gui" \
    install \
    $DESTDIR_ARG \
     --prefix="/home/gary/AutoNOMOS-Tools/line-sensing-gui/install" --install-scripts="/home/gary/AutoNOMOS-Tools/line-sensing-gui/install/bin"
