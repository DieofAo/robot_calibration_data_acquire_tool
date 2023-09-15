cmake_minimum_required(VERSION 2.8.3)

project(ikfast_test)


#ikfast cpp lib no main setting
ADD_DEFINITIONS(-DIKFAST_NO_MAIN)
ADD_DEFINITIONS(-DIKFAST_HAS_LIBRARY)
ADD_DEFINITIONS(-DUR5_PARAMS)

include_directories(
  ../
)

add_executable(${PROJECT_NAME}
    test.cpp
    ../ur_kin.cpp
)
