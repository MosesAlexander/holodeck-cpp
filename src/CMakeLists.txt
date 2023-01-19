add_executable(holodeck main.cpp
                        Application.cpp
                        Buffer.cpp
                        Program.cpp
                        Shader.cpp
                        glad.c)

project(holodeck)

set(CMAKE_CXX_STANDARD 17)

message("holodeck current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(holodeck PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                                    PUBLIC /usr/include/)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
message("Looking for cmake modules in: ${CMAKE_SOURCE_DIR}/cmake/")

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")

target_link_libraries(holodeck PUBLIC glfw)
