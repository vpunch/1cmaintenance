cmake_minimum_required(VERSION 3.5)

project(1CMaintenance LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Sql REQUIRED)

add_executable(1CMaintenance
  main.cpp
  mainwindow.cpp
  mainwindow.h
  ibstab.cpp
  ibstab.h
  ibdescwgt.cpp
  ibdescwgt.h
  commontab.cpp
  commontab.h
  global.cpp
  global.h
  taskstab.cpp
  taskstab.h
  ibfield.cpp
  ibfield.h
  storage.cpp
  storage.h
  data.qrc
)

target_link_libraries(1CMaintenance PRIVATE Qt5::Widgets Qt5::Sql)
