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

Joint::Joint(float zAngle, float yAngle) :
		JointModel(zAngle, yAngle), cube(new Cube()) {
	setAngles(zAngle, yAngle);
}

Joint::~Joint() {
}

void Joint::draw(Renderer& renderer) const {
	cube->draw(renderer);
}

void Joint::setAngles(float zAngle, float yAngle) {
	JointModel::setAngles(zAngle, yAngle);
	setZRotAngle(zAngle);
	setYRotAngle(yAngle);
}

void Joint::setZRotAngle(float angle) {
	JointModel::setZRotAngle(angle);
	cube->setUniformColor(glm::vec3(1, 0, 0));
}

void Joint::setYRotAngle(float angle) {
	JointModel::setYRotAngle(angle);
	cube->setUniformColor(glm::vec3(1, 0, 0));
}

CubePtr Joint::getDrawable() {
	return cube;
}

