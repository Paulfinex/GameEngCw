cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/sfml")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")
add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
-E copy_directory "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)

## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" PRIVATE ${SFML_INCS})
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

#### Maths lib ####
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

#### ECM lib ####
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)

file(GLOB_RECURSE SOURCES coursework/*.cpp coursework/*.h)
add_executable(COURSEWORK ${SOURCES} )
target_include_directories(COURSEWORK SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(COURSEWORK sfml-graphics)

## Space invaders
file(GLOB_RECURSE SOURCES 2_invaders/*.cpp 2_invaders/*.h)
add_executable(2_INVADERS ${SOURCES} )
target_include_directories(2_INVADERS SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(2_INVADERS sfml-graphics)
add_dependencies(2_INVADERS copy_resources)

## Maze
file(GLOB_RECURSE SOURCES maze/*.cpp maze/*.h)
add_executable(MAZE ${SOURCES} )
target_include_directories(MAZE SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(MAZE lib_tile_level_loader sfml-graphics)
set_target_properties(MAZE PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))
add_dependencies(MAZE copy_resources)

## Pacman
file(GLOB_RECURSE SOURCES pacman/*.cpp pacman/*.h)
add_executable(pacman ${SOURCES} )
target_include_directories(pacman SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(pacman lib_tile_level_loader lib_ecm sfml-graphics)
set_target_properties(pacman PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))
add_dependencies(pacman copy_resources)


