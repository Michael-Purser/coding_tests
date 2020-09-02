cmake_minimum_required(VERSION 3.1)
project(hello_world)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_CATKIN_DEPS
    roscpp
)

find_package(catkin REQUIRED
  COMPONENTS
    ${PROJECT_CATKIN_DEPS}
)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    ${PROJECT_NAME}
  CATKIN_DEPENDS
    ${PROJECT_CATKIN_DEPS}
)

add_definitions(${catkin_DEFINITIONS})
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_subdirectory(src/${PROJECT_NAME})

########################################################
# Installs
########################################################

install(
  DIRECTORY
    include/${PROJECT_NAME}/
  DESTINATION
    ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
