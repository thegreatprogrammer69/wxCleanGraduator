cmake_minimum_required(VERSION 3.20)
project(wxCleanGraduator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(wxWidgets REQUIRED COMPONENTS core base aui)
include(${wxWidgets_USE_FILE})

add_subdirectory(src/domain)
add_subdirectory(src/application)
add_subdirectory(src/app)
add_subdirectory(src/ui)
add_subdirectory(src/infrastructure)

add_executable(wxCleanGraduator
    main.cpp
)

target_include_directories(wxCleanGraduator
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(wxCleanGraduator
    PRIVATE
        app
        application
        domain
        infrastructure
        ui
        ${wxWidgets_LIBRARIES}
)
