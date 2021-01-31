cmake_minimum_required(VERSION 3.5)

project(CrossPE LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

FILE(GLOB HEADER_FILES "include/*.h")
FILE(GLOB SRC_FILES "src/*.c" "src/*.cpp")

set(PROJECT_SOURCES
        ${SRC_FILES}
        ${HEADER_FILES}
)


qt_add_executable(CrossPE
    ${PROJECT_SOURCES}
)


target_link_libraries(CrossPE PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
