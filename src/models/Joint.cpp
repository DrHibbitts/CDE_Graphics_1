/*
 * Joint.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Joint.h"

Joint::Joint() :
		square(new Square()) {
	setAngle(0);
}

Joint::~Joint() {
}

void Joint::draw(Renderer& renderer) const {
	square->draw(renderer);
}

float Joint::getAngle() const {
	return angle;
}

void Joint::setAngle(float angle) {
	this->angle = angle;

	square->setVertices(glm::vec3(-0.1, -0.1, 0), glm::vec3(0.1, -0.1, 0),
			glm::vec3(-0.1, 0.1, 0), glm::vec3(0.1, 0.1, 0));

	square->setUniformColor(glm::vec3(1, 0, 0));
}

SquarePtr Joint::getDrawable() {
	return square;
}
