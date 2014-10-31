CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_ECLIPSE_VERSION 3.7)

SET(PROJECT_NAME CDE_Graphics_1)
PROJECT(${PROJECT_NAME})
SET(PROJECT_EXE "${PROJECT_NAME}")

#C++11 support
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#All warnings and thread compiling on linux
IF(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
ENDIF()

#Add custom .cmake files located in this folder
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakeModules")

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLFW REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(GLM REQUIRED)
FIND_PACKAGE(Boost REQUIRED)

#Librearies for loading images and 3d models, not needed for the moment
#FIND_PACKAGE(FreeImageplus REQUIRED)
#FIND_PACKAGE(ASSIMP REQUIRED)

INCLUDE_DIRECTORIES( ${OPENGL_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${GLFW_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${GLEW_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${GLM_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

#INCLUDE_DIRECTORIES( ${FREEIMAGEPLUS_INCLUDE_DIRS} )
#INCLUDE_DIRECTORIES( ${ASSIMP_INCLUDE_DIRS} )

SET(SOURCE
src/main.cpp
src/models/Axis.cpp
src/models/Bone.cpp
src/models/Chain.cpp
src/models/Joint.cpp
src/models/Line.cpp
src/models/Point.cpp
src/models/PointSet.cpp
src/models/PrimitiveParameter.cpp
src/models/Square.cpp
src/models/Triangle.cpp
src/models/VertexObject.cpp
src/rendering/Renderer.cpp
src/rendering/ShaderLoader.cpp
src/rendering/FPSCounter.cpp
src/simulation/SimulationController.cpp
src/simulation/SimulationSolver.cpp
src/Window.cpp
)

SET(HEADERS
src/models/Axis.h
src/models/Bone.h
src/models/Chain.h
src/models/Drawable.h
src/models/Joint.h
src/models/Line.h
src/models/Point.h
src/models/PointSet.h
src/models/PrimitiveParameter.h
src/models/Square.h
src/models/Triangle.h
src/models/VertexObject.h
src/rendering/Renderer.h
src/rendering/ShaderLoader.h
src/rendering/FPSCounter.h
src/simulation/SimulationController.h
src/simulation/SimulationSolver.h
src/Window.h
)

#Create the executable
ADD_EXECUTABLE(${PROJECT_EXE} ${SOURCE} ${HEADERS})

#OpenGL linking
TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${OPENGL_LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${GLFW_LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${GLEW_LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${Boost_LIBRARIES})

#TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${FREEIMAGEPLUS_LIBRARIES})
#TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${ASSIMP_LIBRARIES})

#Threads library, Could be needed for windows
#TARGET_LINK_LIBRARIES(${PROJECT_EXE} "-lpthread")

#Extra linking for linux running X11 enviroments
IF(UNIX)
    TARGET_LINK_LIBRARIES(${PROJECT_EXE} "-lX11 -lXrandr -lXi -lXxf86vm")
ENDIF()
