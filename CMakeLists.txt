cmake_minimum_required(VERSION 3.13)
project(ugeneloader)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(ugeneloader
        ugeneloader.cpp pbm.c zio.c new.c misc.c
        window.c send.c reduce.c dither.c compress.c
        halftone.c imagetypes.c config.c
        tinyLoader.cpp tinyLoaderSplashScreen.cpp)

set(XINC -I/usr/X11R6/include)		# new X distributions (X.org, etc.)
set(XLIB -L/usr/X11R6/lib -lX11)

find_package(X11 REQUIRED)

message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")

add_compile_options(-pthread)

include_directories(${X11_INCLUDE_DIR} include)

link_directories(${X11_LIBRARIES} ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(ugeneloader ${X11_LIBRARIES} rt ${CMAKE_SOURCE_DIR}/lib/libcurl.a)
