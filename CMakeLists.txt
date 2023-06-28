cmake_minimum_required(VERSION 3.17)
project(Cal_last)

set(CMAKE_CXX_STANDARD 20)

# Comment if you are on mac
link_libraries(ws2_32 wsock32)

include_directories(src)
include_directories(resources)
add_executable(Cal_last main.cpp src/parser.cpp src/GraphViewer/connection.cpp src/GraphViewer/graphviewer.cpp src/WasteApp.cpp src/WasteApp.h src/Address.cpp src/Address.h src/User.cpp src/User.h src/CollectingPoint.cpp src/CollectingPoint.h src/Container.cpp src/Container.h src/Container.cpp src/Container.h src/Menu.cpp src/Menu.h)