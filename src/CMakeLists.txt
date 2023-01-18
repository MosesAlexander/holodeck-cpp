add_executable(holodeck main.cpp
                        Application.cpp
                        glad.c)

project(holodeck)

set(CMAKE_CXX_STANDARD 17)

message("holodeck current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build")
#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

#set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
#set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

target_include_directories(holodeck PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                                    PUBLIC /usr/include/)

#find_package(glfw 3.3 REQUIRED)
#find_package(OpenGL REQUIRED)

#message("GLFW3_LIBRARY: ${GLFW_LIBRARY} INCLUDE_DIR: ${GLFW_INCLUDE_DIRS} OPENGL_INCLUDE_DIR: ${OPENGL_INCLUDE_DIR}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
message("Looking for cmake modules in: ${CMAKE_SOURCE_DIR}/cmake/")

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

target_link_libraries(holodeck PUBLIC glfw)
