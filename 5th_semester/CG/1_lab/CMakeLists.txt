cmake_minimum_required(VERSION 2.8.11)

project(cg_lab01)

set(INCLUDE_DIR "include")
set(SOURCE_DIR "src")
set(INCLUDE_SUF "hpp")
set(SOURCE_SUF "cpp")

file(GLOB_RECURSE INCLUDES "${INCLUDE_DIR}/*.${INCLUDE_SUF}")
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.${SOURCE_SUF}")

if (CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

include_directories(
  ${INCLUDE_DIR}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5Charts_INCLUDE_DIRS}
  )

add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})
# qt5_use_modules(${PROJECT_NAME} Widgets Charts)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

target_link_libraries(
  ${PROJECT_NAME}
  Qt5::Widgets
  Qt5::Charts
  )
