cmake_minimum_required(VERSION 2.8.3)
project(test_camera_robot_calibration)

find_package(catkin REQUIRED COMPONENTS
  crustcrawler_mover_utils
  roscpp
  rospy
  tf
  rgbd_utils
  camera_robot_calibration
)

find_package(Boost REQUIRED COMPONENTS system )
find_package(OpenCV REQUIRED COMPONENTS features2d nonfree)
find_package(PCL 1.7 REQUIRED)
find_package(PkgConfig)
pkg_search_module(Eigen3 REQUIRED eigen3)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fPIC")

catkin_package(
 # INCLUDE_DIRS include
#  LIBRARIES test_camera_robot_calibration
#  CATKIN_DEPENDS camera_robot_calibration roscpp rospy tf
#  DEPENDS system_lib
)

include_directories(
  include /home/mukhtar/git/catkin_ws/install/include/
  ${catkin_INCLUDE_DIRS}
)

add_executable(test_camera_robot_calibration src/test_camera_robot_calibration.cpp )
target_link_libraries(test_camera_robot_calibration /usr/local/lib/libaruco.so ${catkin_LIBRARIES} ${PCL_LIBRARIES})

add_executable(automatic_calibration_test src/automatic_calibration_test.cpp )
target_link_libraries(automatic_calibration_test /usr/local/lib/libaruco.so ${catkin_LIBRARIES} ${PCL_LIBRARIES})
