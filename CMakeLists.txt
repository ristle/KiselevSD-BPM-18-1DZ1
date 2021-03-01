cmake_minimum_required(VERSION 3.19)
project(KiselevSD_BPM_18_1_DZ1)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -pg")

find_package(OpenCV 4.5 REQUIRED)

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(KiselevSD_BPM_18_1_DZ1 src/main.cpp)
target_link_libraries(KiselevSD_BPM_18_1_DZ1 ${OpenCV_LIBS})