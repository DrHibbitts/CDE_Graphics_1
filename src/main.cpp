#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Window.h"
#include "Triangle.h"
#include "Line.h"
#include "Square.h"
#include "Axis.h"
#include "Chain.h"

int main(void) {
	//Only one Window is allowed in the application, singleton pattern
	//Create a window of: width, height, title
	Window& window = Window::getInstance();
	window.createWindow(1024, 768,
			std::string("Inverse kinematics course work"));

	//Create 3D axis object
	AxisPtr axis(new Axis());

	//Draw it
	window.addDrawable(axis);

//	TrianglePtr triangle(
//			new Triangle(glm::vec3(-1.0f, -1.0f, 0.0f),
//					glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
//	triangle->setColors(glm::vec3(1, 1, 0), glm::vec3(1, 0, 0),
//			glm::vec3(1, 0, 0));
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
//	window.addDrawable(triangle);
//	window.addDrawable(line);
//
//	window.addDrawable(square);
//	window.addDrawable(triangle2);

//Create a chain object
	ChainPtr chain(new Chain());

	//Add several bones with different lengths and joints rotations
	chain->addBone(1);
	chain->setJointAngle(0, 45);
	chain->addBone(0.5);
	chain->setJointAngle(1, 45);
	chain->addBone(2);
	chain->setJointAngle(2, 45);
	chain->addBone(1);
	chain->setJointAngle(3, -45);

	//Draw chain
	window.addDrawable(chain);

	//Execute main loop
	window.runLoop();

	return 0;
}

//TODO MVP projections
