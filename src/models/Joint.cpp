/*
 * Joint.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Joint.h"

Joint::Joint() :
		JointModel(), square(new Square()) {
}

Joint::Joint(float angle) :
		JointModel(angle), square(new Square()) {
	setAngle(angle);
}

Joint::~Joint() {
}

void Joint::draw(Renderer& renderer) const {
	square->draw(renderer);
}

void Joint::setAngle(float angle) {
	JointModel::setAngle(angle);

	square->setVertices(glm::vec3(-0.1, -0.1, 0), glm::vec3(0.1, -0.1, 0),
			glm::vec3(-0.1, 0.1, 0), glm::vec3(0.1, 0.1, 0));

	square->setUniformColor(glm::vec3(1, 0, 0));
}

SquarePtr Joint::getDrawable() {
	return square;
}

