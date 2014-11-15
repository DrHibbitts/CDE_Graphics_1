#include <GL/glew.h>

//Force radians to avoid pragma deprecated warnings
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Window.h"
#include "rendering/drawables/Triangle.h"
#include "rendering/drawables/Line.h"
#include "rendering/drawables/Square.h"
#include "rendering/drawables/Axis.h"
#include "rendering/drawables/Chain.h"
#include "rendering/drawables/Line.h"

int main(void) {
	//Only one Window is allowed in the application, singleton pattern
	//Create a window of: width, height, title
	Window& window = Window::getInstance();
	window.createWindow(1024, 768,
			std::string("Inverse kinematics course work"), 60.0);

	//All objects to be drawn have to be created with their pointers
	//Create 3D axis object
	AxisPtr axis(new Axis());

	//Once an object is added to the window, it will be rendered
	window.addDrawable(axis);

	TrianglePtr goalMarker(
			new Triangle(glm::vec3(-0.2f, -0.2f, 0.0f),
					glm::vec3(0.2f, -0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f)));
	goalMarker->setUniformColor(glm::vec3(0, 1, 1));
//
//	TrianglePtr triangle2(
//			new Triangle(glm::vec3(-2.0f, -2.0f, 0.0f),
//					glm::vec3(0.0f, -2.0f, 0.0f),
//					glm::vec3(-1.0f, 0.0f, 0.0f)));
//
//
//	triangle2->setUniformColor(glm::vec3(0, 1, 1));
//
//	triangle->translate(glm::vec3(1, 0.8, 0));
//
//	LinePtr line(new Line(glm::vec3(-2, 0, 0), glm::vec3(2, 0, 0)));
//	line->setUniformColor(glm::vec3(0, 1, 0));
//
//	//Indices should be provided as
//	// 3 - 4
//	// 1 - 2
//	SquarePtr square(
//			new Square(glm::vec3(-1.0f, -1.0f, 0.0f),
//					glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f),
//					glm::vec3(1.0f, 1.0f, 0.0f)));
//
//	square->setUniformColor(glm::vec3(0, 0, 1));
//
	window.addDrawable(goalMarker);
//	window.addDrawable(line);
//
//	window.addDrawable(square);
//	window.addDrawable(triangle2);

	//Create a chain object
	ChainPtr chain(new Chain());

	//Add several bones with different lengths and joints rotations
	//Bone of length 1
	chain->addBone(1);
	//Change the angle of joint 0 to 45 degrees
	chain->setJointAngle(0, 45);

	chain->addBone(0.5);
	chain->setJointAngle(1, 45);

	chain->addBone(2);
	chain->setJointAngle(2, 45);

	chain->addBone(1);
	chain->setJointAngle(3, -45);

	//Draw chain
	window.addDrawable(chain);

	// This only changes the light marker, to change the position go to
	//the renderer class
	glm::vec3 lightPosition(3, 3, -1);
	LinePtr lightX(new Line(glm::vec3(-0.1, 0, 0), glm::vec3(0.1, 0, 0)));
	lightX->translate(lightPosition);
	lightX->setUniformColor(glm::vec3(0.9, 0.9, 0.9));

	LinePtr lightY(new Line(glm::vec3(0, -0.1, 0), glm::vec3(0, 0.1, 0)));
	lightY->translate(lightPosition);
	lightY->setUniformColor(glm::vec3(0.9, 0.9, 0.9));

	window.addDrawable(lightX);
	window.addDrawable(lightY);

	CubePtr cube(new Cube());
	cube->setUniformColor(glm::vec3(0, 1, 1));

	//Start the input handling and rendering loop
	window.executeMainLoop();

	return 0;
}

//TODO Make introduce simulation and/or rendering controlled step size
