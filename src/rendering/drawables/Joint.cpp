/*
 * Joint.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Joint.h"

Joint::Joint() :
		JointModel(), cube(new Cube()) {
}

Joint::Joint(float angle) :
		JointModel(angle), cube(new Cube()) {
	setAngle(angle);
}

Joint::~Joint() {
}

void Joint::draw(Renderer& renderer) const {
	cube->draw(renderer);
}

void Joint::setAngle(float angle) {
	JointModel::setAngle(angle);
	cube->setUniformColor(glm::vec3(1, 0, 0));
}

CubePtr Joint::getDrawable() {
	return cube;
}

