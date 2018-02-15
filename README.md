# test_camera_robot_calibration
This is a ROS package that uses [camera_robot_calibration](https://github.com/robotsthatdream/camera_robot_calibration.git) library/class to achieve the calibration and gives the transformation matrix between the 3D vision sensor and the robot.

# Dependencies
- *[camera_robot_calibration](https://github.com/robotsthatdream/camera_robot_calibration.git).*
- *[crustcrawler_mover_utils](https://github.com/robotsthatdream/crustcrawler_useful.git) :* 

  This is a simple class to make use of ROS capabilities, specially Moveit!, for the motion planning for the robotic arm. It works in integration with *crustcrawler_mover_config* and/or *crustcrawler_moveit_config_grasping* which are part of the *[crustcrawler_sdks](https://github.com/robotsthatdream/crustcrawler_dream.git).

# Installation
- Install *[camera_robot_calibration](https://github.com/robotsthatdream/camera_robot_calibration.git)* with all its dependencies as described in its README file.
- *[crustcrawler_mover_utils](https://github.com/robotsthatdream/crustcrawler_useful.git) :*
  
  Assuming your catkin workspace is in your home directory, then in a terminal one should do the following:
  ```
  git clone https://github.com/robotsthatdream/crustcrawler_useful.git
  cd ~/catkin_ws/src
  ln -s ~/crustcrawler_useful/crustcrawler_mover_utils
  cd ..
  source devel/setup.bash
  catkin_make -DCATKIN_WHITELIST_PACKAGES=crustcrawler_mover_utils install
  ```
  
  One thing we should mention, to clarify why we need this library/class, is that there are two ways to go about the calibration :
  - First way we can fix the QR code marker to robot End Effector and let the mover class move the marker randomly in front of the vision sensor till the calibration finishes. In this case we need this class to be installed.
  - Second way is to fix the marker but manually move the marker in front of the vision sensor till the calibration is done. If we want to use this mehtod we don't need this library, and we just need to comment the compilation of the node *automatic_calibration_test.cpp* and the dependency on this library as well in the *CMakeLists.txt* file.
  
  More explanation in the *[Tutorial](https://github.com/ghanimmukhtar/test_camera_robot_calibration/wiki/Tutorial)*.
