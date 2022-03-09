cmake_minimum_required(VERSION 3.5)

# Project Name
PROJECT(generator)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(${PROJECT_NAME} generate.cpp plane.cpp box.cpp cone.cpp sphere.cpp writer.cpp ../Utilities/point.cpp)


if  (WIN32)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
	
else (WIN32) #Linux and Mac
	target_link_libraries(${PROJECT_NAME})

	
endif(WIN32)








