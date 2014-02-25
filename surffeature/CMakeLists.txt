cmake_minimum_required(VERSION 2.8)

SET(TARGET surffeature)
project( ${TARGET} )

SET(${TARGET}_HEADERS

)

SET(${TARGET}_SOURCES 
  #surf_feature_matching.cpp
  SURF_Homography.cpp
)

INCLUDE_DIRECTORIES(
    ${SDL_INCLUDE_DIR}
)

add_executable( ${TARGET} ${${TARGET}_SOURCES} ${${TARGET}_HEADERS} )
target_link_libraries( ${TARGET} ${OpenCV_LIBRARIES}  )

create_target_launcher(${TARGET} ARGS "" WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/../../bin/")

add_custom_command(
   TARGET ${TARGET} POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/${TARGET}${CMAKE_EXECUTABLE_SUFFIX}" "${PROJECT_SOURCE_DIR}/../../bin"
   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/../../bin
  )