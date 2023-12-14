cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Bulb)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND} 
  -E copy_directory
    "${PROJECT_SOURCE_DIR}/res"
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
)

#### Add External Dependencies ####
# SFML - graphics library
add_subdirectory("lib/sfml" EXCLUDE_FROM_ALL)
#include_directories("lib/sfml/include")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D")
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

#### Add Engine and our own library projects####

file(GLOB_RECURSE RESOURCE_FILES "res/*.*")
## Engine ##
file(GLOB_RECURSE SOURCE_FILES engine/*.cpp engine/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_tile_level_loader lib_maths lib_ecm Box2D sfml-graphics sfml-audio)

## Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE "${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" )
target_link_libraries(lib_tile_level_loader lib_maths sfml-graphics)

# Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

## ECM lib
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)


################### Add Practicals Below ##########################

###### Bulb #######

file(GLOB_RECURSE SOURCES Bulb/*.cpp Bulb/*.h)
file(GLOB_RECURSE CMPNTS Bulb/components/*.cpp Bulb/components/*.h)
file(GLOB_RECURSE SCENES Bulb/scenes/*.cpp Bulb/scenes/*.h)
add_executable(Drop_Pod ${SOURCES} ${RESOURCE_FILES}
        Bulb/platformer_main.cpp
        Bulb/components/cmp_player_physics.cpp
        Bulb/components/cmp_physics.cpp
        Bulb/components/cmp_pointer.cpp
        Bulb/components/cmp_pointer.h
        Bulb/components/cmp_bullet.h
        Bulb/components/cmp_bullet.cpp
        Bulb/components/cmp_light.h
        Bulb/components/cmp_light.cpp
        Bulb/components/cmp_path_follow.h
        Bulb/components/cmp_path_follow.cpp
        Bulb/scenes/scene_level2.cpp
        Bulb/components/cmp_player_anim.h
        Bulb/components/cmp_player_anim.cpp
        Bulb/scenes/scene_level3.cpp
        Bulb/scenes/scene_level3.h
)
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
#target_include_directories(Drop_Pod SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(Drop_Pod lib_engine)
set(EXECUTABLES ${EXECUTABLES} Drop_Pod)

add_dependencies(Drop_Pod copy_resources)

set_target_properties(Drop_Pod 
    PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
)

