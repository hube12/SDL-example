cmake_minimum_required(VERSION 3.14)
project(sdl C)

set(CMAKE_C_STANDARD 99)
set(DYNAMIC 0)
if (DYNAMIC)
    INCLUDE(FindPkgConfig)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sdllogo.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
else ()
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
    add_subdirectory(SDL-mirror)
    include_directories(SDL-mirror/include)
    include_directories(SDL-mirror/src)
    link_directories(SDL-mirror)
    link_libraries(SDL2)

endif ()
add_executable(${PROJECT_NAME} main.c)



