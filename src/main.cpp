#include <GL/glew.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "Window.h"
#include "Triangle.h"
#include "Line.h"
#include "Square.h"
#include "Axis.h"

int main(void)
{
	Window window(1024, 768, std::string("Inverse kinematics course work"));

	TrianglePtr triangle(
			new Triangle(glm::vec3(-1.0f, -1.0f, 0.0f),
					glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	triangle->setColors(glm::vec3(1, 1, 0), glm::vec3(1, 0, 0),
			glm::vec3(1, 0, 0));

	TrianglePtr triangle2(
			new Triangle(glm::vec3(-2.0f, -2.0f, 0.0f),
					glm::vec3(0.0f, -2.0f, 0.0f),
					glm::vec3(-1.0f, 0.0f, 0.0f)));

	AxisPtr axis(new Axis());

	triangle2->setUniformColor(glm::vec3(0, 1, 1));

	triangle->translate(glm::vec3(1, 0.8, 0));

	LinePtr line(new Line(glm::vec3(-2, 0, 0), glm::vec3(2, 0, 0)));
	line->setUniformColor(glm::vec3(0, 1, 0));

	//Indices should be provided as
	// 3 - 4
	// 1 - 2
	SquarePtr square(
			new Square(glm::vec3(-1.0f, -1.0f, 0.0f),
					glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(-1.0f, 1.0f, 0.0f),
					glm::vec3(1.0f, 1.0f, 0.0f)));

	square->setUniformColor(glm::vec3(0, 0, 1));

	window.addDrawable(triangle);
	window.addDrawable(line);

	window.addDrawable(square);
	window.addDrawable(triangle2);

	window.addDrawable(axis);

	window.runLoop();

	return 0;
}

//TODO Capture keyboard and mouse events
//TODO MVP projections
