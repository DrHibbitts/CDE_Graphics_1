# Locate the glfw(3) library
# This module defines the following variables:
# GLFW_LIBRARIES, the name of the library;
# GLFW_INCLUDE_DIRS, where to find glfw include files.
# GLFW_FOUND, true if both the GLFW_LIBRARIES and GLFW_INCLUDE_DIRS have been found.
#
# To help locate the library and include file, you could define an environment variable called
# GLFW_ROOT which points to the root of the glfw library installation. This is pretty useful
# on a Windows platform.
#
#
# Usage example to compile an "executable" target to the glfw library:
#
# FIND_PACKAGE (glfw REQUIRED)
# INCLUDE_DIRSECTORIES (${GLFW_INCLUDE_DIRS})
# ADD_EXECUTABLE (executable ${EXECUTABLE_SRCS})
# TARGET_LINK_LIBRARIES (executable ${GLFW_LIBRARIES})
#
# TODO:
# Allow the user to select to link to a shared library or to a static library.

#Search for the include file...
FIND_PATH(GLFW_INCLUDE_DIRS GLFW/glfw3.h DOC "Path to GLFW include directory."
  HINTS
  $ENV{GLFW_ROOT}
  PATH_SUFFIX include
  PATHS
  /usr/include/
  /usr/local/include/
  # By default headers are under GL subfolder
  /usr/include/GLFW
  /usr/local/include/GLFW
  ${GLFW_ROOT_DIR}/include/ # added by ptr
)

FIND_LIBRARY(GLFW_LIBRARIES_TEMP DOC "Absolute path to GLFW library."
  NAMES glfw GLFW.lib libglfw3.dylib libglfw3.a
  HINTS
  $ENV{GLFW_ROOT}
  # In the expanded GLFW source archive. Should be uncommon, but whatever.
  PATH_SUFFIXES lib/win32 lib/cocoa lib/x11
  PATHS
  /usr/local/lib
  /usr/lib
  ${GLFW_ROOT_DIR}/lib-msvc100/release # added by ptr
)

IF(GLFW_LIBRARIES_TEMP AND GLFW_INCLUDE_DIRS)
  SET(GLFW_FOUND "YES")
  message(STATUS "Found GLFW: ${GLFW_LIBRARIES_TEMP}")

  # For MinGW library
  IF(MINGW)
    SET(MINGW32_LIBRARY mingw32 CACHE STRING "mwindows for MinGW")
    SET(GLFW_LIBRARIES_TEMP ${MINGW32_LIBRARY} ${GLFW_LIBRARIES_TEMP})
  ENDIF(MINGW)

  # OS X uses the Cocoa port so we need to link against Cocoa
  IF(APPLE)
    SET(GLFW_LIBRARIES_TEMP ${GLFW_LIBRARIES_TEMP} "-framework Cocoa -framework IOKit")
    SET(GLFW_LIBRARIES ${GLFW_LIBRARIES_TEMP})
  ENDIF(APPLE)

  # Set the final string here so the GUI reflects the final state.
  SET(GLFW_LIBRARIES ${GLFW_LIBRARIES_TEMP} CACHE STRING "Where the GLFW Library can be found")
  # Set the temp variable to INTERNAL so it is not seen in the CMake GUI
  SET(GLFW_LIBRARIES_TEMP "" CACHE INTERNAL "")
ENDIF(GLFW_LIBRARIES_TEMP AND GLFW_INCLUDE_DIRS)
