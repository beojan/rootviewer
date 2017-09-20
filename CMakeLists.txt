cmake_minimum_required(VERSION 2.8.11)
project(RootViewer)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

set(rootviewer_SRC
  src/main.cpp
  src/rootviewer.cpp
)

# Create code from a list of Qt designer ui files.
#set(CMAKE_AUTOUIC ON) # use this if you have CMake 3.x instead of the following
qt5_wrap_ui(rootviewer_SRC src/rootviewer.ui)

# Tell CMake to create the helloworld executable
add_executable(rootviewer ${rootviewer_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(rootviewer Qt5::Widgets)

# Install the executable
install(TARGETS rootviewer DESTINATION bin)
