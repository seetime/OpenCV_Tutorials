cmake_minimum_required(VERSION 2.8)

SET(TARGET cameracalibration)
project( ${TARGET} )

SET(${TARGET}_HEADERS

)

SET(${TARGET}_SOURCES 
#  calibration.cpp
	main.cpp
)

INCLUDE_DIRECTORIES(
    ${SDL_INCLUDE_DIR}
)

add_executable( ${TARGET} ${${TARGET}_SOURCES} ${${TARGET}_HEADERS} )
target_link_libraries( ${TARGET} ${OpenCV_LIBRARIES}  )

create_target_launcher(${TARGET} ARGS "-w 6 -h 9 -s 0.025 -o camera.yml -op -oe" WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/../../bin/")

add_custom_command(
   TARGET ${TARGET} POST_BUILD
   #COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${TARGET}${CMAKE_EXECUTABLE_SUFFIX}" "${PROJECT_SOURCE_DIR}/../colortest"
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${TARGET}${CMAKE_EXECUTABLE_SUFFIX}" "${PROJECT_SOURCE_DIR}/../../bin"
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin
  )