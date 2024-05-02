cmake_minimum_required(VERSION 3.0.2)
project(filters_nodes)

find_package(catkin REQUIRED COMPONENTS
  filters
  roscpp
  rospy
  std_msgs
)

catkin_package()

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(twist_mean_filter_node src/twist_mean_filter_node.cpp)
target_link_libraries(twist_mean_filter_node ${catkin_LIBRARIES})
