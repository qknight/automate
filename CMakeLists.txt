cmake_minimum_required(VERSION 2.6)

# i wonder why i need C here (it is used for -- Looking for Q_WS_X11 - found ) and if i don't include C it gives me:
# CMake Error: Unknown extension ".c" for file "build/CMakeFiles/CMakeTmp/CheckSymbolExists.c".  TRY_COMPILE only works for enabled languages.
project(automate CXX C)

FIND_PACKAGE(Qt4 REQUIRED) # find and setup Qt4 for this project
INCLUDE( ${QT_USE_FILE} )

# i would to see more projects using these defaults (-pedantic does not work yet)
ADD_DEFINITIONS( "-Wall -ansi " )

# the version for the doxygen documenation is also controlled by AUTOMATE_VERSION
# but set in 'doc/CMakeLists.txt'
SET ( AUTOMATE_VERSION "1.0.0-rc1" )
  CONFIGURE_FILE(src/version.h.in version.h @ONLY IMMEDIATE)
# this code generates the version information for the .cpp/.h files

SET (Generated_Sources ${PROJECT_BINARY_DIR}/version.h )

OPTION(BUILD_AUTOMATE_DOCUMENTATION "Create doxygen documentation for developers" ON)

# this builds the documentation using doxygen
ADD_SUBDIRECTORY(doc)

# see http://cmake.org/cmake/help/cmake2.6docs.html#module:FindQt4
# SET (QT_USE_QTOPENGL 1)

SET( automate_SOURCES
  src/AbstractTreeItem.cpp
  src/AbstractView.cpp
  src/AutomateRoot.cpp
  src/GraphicsScene.cpp
  src/ItemView.cpp
  src/Model.cpp
  src/SceneItem_Connection.cpp
  src/SceneItem_ConnectionHandle.cpp
  src/SceneItem_LabelEditor.cpp
  src/SceneItem_Node.cpp
  src/SymbolTable.cpp
  src/automate.cpp
  src/automatehandler.cpp
  src/graphicsView.cpp
  src/main.cpp
  src/meta_node.cpp
  src/node.cpp
  src/node_connection.cpp
  src/objectCounter.cpp
  src/objectProperty.cpp
  src/treeView.cpp
  src/viewHandler.cpp
)

# if .h files are included which don't inherit or use QOBJECT you will get a warning but everything might work,
# in that case just remove that file here. in case you miss a include here you will get some weird vtable issue
# in that case look at the symbol name which can't be resolved and have a wise guess where that could be
# defined and finally include that specific header here and rebuild from a 'cleaned' build directory
SET( automate_MOC_HEADERS
  src/AbstractView.h
  src/ItemView.h
  src/automatehandler.h
  src/GraphicsScene.h
  src/graphicsView.h
  src/treeView.h
  src/SceneItem_LabelEditor.h
  src/SceneItem_ConnectionHandle.h
)

SET( automate_UIs
  src/ui/AutomateHandlerWidget.ui
  src/ui/treeViewMainWindow.ui
)

# icons and other stuff will be processed here
SET( automate_RCCs
  automatehandler.qrc
)

INCLUDE_DIRECTORIES(
  ${CMAKE_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

# QT4_WRAP_UI(outfiles inputfile ... OPTIONS ...)
QT4_WRAP_UI(automate_SOURCES ${automate_UIs})

# macro QT4_WRAP_CPP(outfiles inputfile ... )
QT4_WRAP_CPP (automate_SOURCES ${automate_MOC_HEADERS}) 

QT4_ADD_RESOURCES(automate_SOURCES ${automate_RCCs})

ADD_EXECUTABLE(automate ${automate_SOURCES} ${Generated_Sources} )

TARGET_LINK_LIBRARIES( automate ${QT_LIBRARIES} )

INSTALL ( TARGETS automate DESTINATION bin )
