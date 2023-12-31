add_executable(holodeck main.cpp
                        Holodeck.cpp
                        BufferDescriptor.cpp
                        EboDescriptor.cpp
                        VaoDescriptor.cpp
                        Program.cpp
                        Shader.cpp
                        Uniform.cpp
                        Model.cpp
                        Mesh.cpp
                        Cube.cpp
                        Quad.cpp
                        Texture.cpp
                        TextManager.cpp
                        JsonConfig.cpp
                        InputState.cpp
                        TransformState.cpp
                        CameraState.cpp
                        glad.c)

project(holodeck)

set_property(TARGET holodeck PROPERTY CXX_STANDARD 20)

message("holodeck current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(holodeck PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
                                    PUBLIC /usr/local/include/
                                    PUBLIC /usr/include/
                                    PUBLIC /usr/include/freetype2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
message("Looking for cmake modules in: ${CMAKE_SOURCE_DIR}/cmake/")

find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")
find_package(Freetype REQUIRED)
message(STATUS "Found Freetype in ${Freetype_INCLUDE_DIR}")

target_link_libraries(holodeck PUBLIC glfw ${FREETYPE_LIBRARIES} ${CMAKE_DL_LIBS})
