CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_ECLIPSE_VERSION 3.7)

SET(PROJECT_NAME CDE_Graphics_1)
PROJECT(${PROJECT_NAME})
SET(PROJECT_EXE "${PROJECT_NAME}")

#Add custom .cmake files located in this folder
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakeModules")

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Boost REQUIRED)

add_subdirectory (external)

include_directories(
	external/AntTweakBar-1.16/include/
	external/glfw-3.0.3/include/GLFW/
	external/glm-0.9.4.0/
	external/glew-1.9.0/include/
	external/assimp-3.0.1270/include/
	external/bullet-2.81-rev2613/src/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	GLFW_303
	GLEW_190
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)


#Librearies for loading images and 3d models, not needed for the moment
#FIND_PACKAGE(FreeImageplus REQUIRED)
#FIND_PACKAGE(ASSIMP REQUIRED)

include_directories(glfw/include)
INCLUDE_DIRECTORIES( ${OPENGL_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${GLEW_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES( ${GLM_INCLUDE_DIRS} )
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

#INCLUDE_DIRECTORIES( ${FREEIMAGEPLUS_INCLUDE_DIRS} )
#INCLUDE_DIRECTORIES( ${ASSIMP_INCLUDE_DIRS} )

SET(SOURCE
src/main.cpp
src/Axis.cpp
src/Line.cpp
src/PrimitiveParameter.cpp
src/Renderer.cpp
src/ShaderLoader.cpp
src/Square.cpp
src/Triangle.cpp
src/VertexObject.cpp
src/Window.cpp
)

SET(HEADERS
src/Axis.h
src/Drawable.h
src/Line.h
src/PrimitiveParameter.h
src/Renderer.h
src/ShaderLoader.h
src/Square.h
src/Triangle.h
src/VertexObject.h
src/Window.h
)

#Create the executable
ADD_EXECUTABLE(${PROJECT_EXE} ${SOURCE} ${HEADERS})

#OpenGL linking
TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${OPENGL_LIBRARIES})
#target_link_libraries(${PROJECT_EXE} glfw ${GLFW_LIBRARIES})
TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${Boost_LIBRARIES})

#TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${FREEIMAGEPLUS_LIBRARIES})
#TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${ASSIMP_LIBRARIES})

#Extra linking for x11 enviroments
#TODO Check libraries flags on windows
TARGET_LINK_LIBRARIES(${PROJECT_EXE} ${ALL_LIBS})
