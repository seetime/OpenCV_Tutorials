cmake_minimum_required(VERSION 2.8)

SET(TARGET cvTutorials)
project( ${TARGET} )

SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
include(CreateLaunchers)

if(MSVC)
#SET(OpenCV_DIR "D:\\temp\\opencv\\build")
SET(OpenCV_DIR "d:\\work\\opencv\\opencv\\build")
endif(MSVC)

find_package( OpenCV REQUIRED )

#message(WARNING "OpenCV_LIBS -- ${OpenCV_LIBS}")
#message(WARNING "OpenCV_LIBRARIES -- ${OpenCV_LIBRARIES}")

add_subdirectory (quadrilateral)
add_subdirectory (dynamicrange)
add_subdirectory (cameracalibration)
add_subdirectory (houghlines)
add_subdirectory (surffeature)
add_subdirectory (transform)