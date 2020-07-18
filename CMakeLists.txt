cmake_minimum_required(VERSION 3.5)

project( my_program )

##set(CMAKE_POSITION_INDEPENDENT_CODE ON)

##setting LIB path
#set(LIB shell pkg-config --libs libczmq zlib)

##set(CMAKE_CXX_STANDARD 14)

SET(GCC_LINK_FLAGS "-lczmq")

## load in pkg-config support
find_package(PkgConfig)

## find packages of opencv
find_package( OpenCV REQUIRED )

## use pkg-config to get hints for 0mq locations
pkg_check_modules(PC_ZeroMQ QUIET zmq)


include_directories("/usr/include")
include_directories(.)


## use the hint from above to find where 'czmq.h' is located
##find_path(ZeroMQ_INCLUDE_DIR NAMES czmq.h PATHS ${PC_ZeroMQ_INCLUDE_DIRS})


add_executable(my_program main.cpp zwssock.c zwsdecoder.c zwshandshake.c)


## sir if i am including this line then error is 2nd image
#### add the include directory to our compile directives
##target_include_directories(my_program PUBLIC ${ZeroMQ_INCLUDE_DIR})

target_link_libraries(my_program PUBLIC -lczmq -lzmq -lz ${OpenCV_LIBS})

