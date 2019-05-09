cmake_minimum_required(VERSION 3.14)
project(sdl C)

set(CMAKE_C_STANDARD 11)
set(DYNAMIC 0)

add_executable(${PROJECT_NAME} main.c)


if (DYNAMIC)
    INCLUDE(FindPkgConfig)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sdllogo.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
    INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
else ()
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sdllogo.bmp DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
    add_subdirectory(SDL-mirror)
    target_link_libraries(${PROJECT_NAME} SDL2main SDL2-static)
endif ()




