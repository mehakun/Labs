cmake_minimum_required(VERSION 3.4)

project(SettingsWidget)
set(INCLUDE_DIR "src")

file(GLOB_RECURSE INCLUDES "${INCLUDE_DIR}/SettingsAttr.hpp" "${INCLUDE_DIR}/SettingsWidget.hpp")
file(GLOB_RECURSE SOURCES "${INCLUDE_DIR}/SettingsAttr.cpp" "${INCLUDE_DIR}/SettingsWidget.cpp")

if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(
  ${INCLUDE_DIR}
  ${Qt5Widgets_INCLUDE_DIRS}
  )

add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
