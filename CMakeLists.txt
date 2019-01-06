cmake_minimum_required(VERSION 2.9)

project(mazegen C CXX)

set(DEBUG True)

if (DEBUG)
  set(CMAKE_CXX_FLAGS "-O0 -g -Wall")
else()
  set(CMAKE_CXX_FLAGS "-O3 -s -Wall")
endif()

include_directories(deps/sfml/include)

file(GLOB SRC_FILES src/*.cpp)

# move executable out of build dir after building
add_executable(maze_generator ${SRC_FILES})
add_custom_command(TARGET maze_generator 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:maze_generator> ..)

if (WIN32 OR XCODE)
  add_subdirectory(deps/sfml)
  target_link_libraries(maze_generator sfml)
else()
  message(WARNING "Run sudo apt install libsfml-dev to install sfml libs")
  target_link_libraries(maze_generator sfml-graphics sfml-window sfml-system)
endif()
