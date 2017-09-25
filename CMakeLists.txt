cmake_minimum_required(VERSION 3.7)
project(RootViewer)
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_DIR})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(ROOT REQUIRED)

include(${ROOT_USE_FILE})

set(rootviewer_SRC
  src/main.cpp
  src/rootviewer.cpp
  src/rootfile.cpp
  src/ttreemodel.cpp
  src/rootcanvaswidget.cpp
)

# Create code from a list of Qt designer ui files.
#set(CMAKE_AUTOUIC ON) # use this if you have CMake 3.x instead of the following
#qt5_wrap_ui(rootviewer_SRC src/rootviewer.ui)

# Tell CMake to create the helloworld executable
add_executable(rootviewer ${rootviewer_SRC})

# Use the Widgets module from Qt 5.
target_link_libraries(rootviewer Qt5::Widgets ${ROOT_LIBRARIES})

# Install the executable
install(TARGETS rootviewer DESTINATION bin)
install( PROGRAMS ROOTViewer.desktop DESTINATION ${XDG_APPS_INSTALL_DIR} )
ecm_install_icons(ICONS 128-apps-ROOT.png DESTINATION share/icons)

