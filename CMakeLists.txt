cmake_minimum_required(VERSION 3.20)
project(wxCleanGraduator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(wxWidgets REQUIRED COMPONENTS core base aui)

include_directories(${CMAKE_SOURCE_DIR}/src)
include(${wxWidgets_USE_FILE})

add_executable(wxCleanGraduator main.cpp)

target_link_libraries(wxCleanGraduator ${wxWidgets_LIBRARIES})