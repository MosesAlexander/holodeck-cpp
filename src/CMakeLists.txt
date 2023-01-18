add_executable(holodeck main.cpp)

message("holodeck current source dir = ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(holodeck PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(glfw3 3.3 REQUIRED)

target_link_libraries(holodeck glfw)