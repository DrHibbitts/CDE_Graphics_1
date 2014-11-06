#include <GL/glew.h>

//Force radians to avoid pragma deprecated warnings
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Window.h"
#include "models/Triangle.h"
#include "models/Line.h"
#include "models/Square.h"
#include "models/Axis.h"
#include "models/Chain.h"

int main(void) {
	//Only one Window is allowed in the application, singleton pattern
	//Create a window of: width, height, title
	Window& window = Window::getInstance();
	window.createWindow(1024, 768,
			std::string("Inverse kinematics course work"));

	//All objects to be drawn have to be created with their pointers
	//Create 3D axis object
	AxisPtr axis(new Axis());

	//Once an object is added to the window, it will be rendered
	window.addDrawable(axis);

	TrianglePtr triangle(
			new Triangle(glm::vec3(-0.2f, -0.2f, 0.0f),
					glm::vec3(0.2f, -0.2f, 0.0f), glm::vec3(0.0f, 0.2f, 0.0f)));
	triangle->setUniformColor(glm::vec3(0, 1, 1));
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
	window.addDrawable(triangle);
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

	//Start the input handling and rendering loop
	window.executeMainLoop();

	return 0;
}

//TODO In Window move simulation code to new class
//TODO Make introduce simulation and/or rendering controlled step size
