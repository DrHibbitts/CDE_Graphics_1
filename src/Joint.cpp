/*
 * Joint.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Joint.h"

Joint::Joint() :
		triangle(new Triangle()) {
	setAngle(0);
}

Joint::~Joint() {
}

void Joint::draw(Renderer& renderer) const {
	triangle->draw(renderer);
}

float Joint::getAngle() const {
	return angle;
}

void Joint::setAngle(float angle) {
	this->angle = angle;

	triangle->setVertices(glm::vec3(0.1, -0.1, 0), glm::vec3(-0.1, -0.1, 0),
			glm::vec3(0, 0.1, 0));
	triangle->setUniformColor(glm::vec3(1, 0, 0));
}

TrianglePtr Joint::getDrawable() {
	return triangle;
}
