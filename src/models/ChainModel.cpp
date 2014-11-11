/*
 * ChainModel.cpp
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#include "ChainModel.h"

#define TO_RAD  M_PI / 180.0
#define TO_DEG  180.0 / M_PI

ChainModel::ChainModel() {
}

ChainModel::~ChainModel() {
}

void ChainModel::clear() {
	bones.clear();
	joints.clear();
}

void ChainModel::addBone(float size) {
	bones.push_back(BoneModel(size));
	joints.push_back(JointModel());
}

void ChainModel::setJointAngle(unsigned int index, float angle) {
	joints.at(index).setAngle(angle * TO_RAD);
}

float ChainModel::getJointAngle(unsigned int index) {
	return joints.at(index).getAngle() * TO_DEG;
}

glm::vec3 ChainModel::getEndEfectorPos() const {
	glm::mat4 currentMat, rotMat;
	//Rotate along z axis
	glm::vec3 axisVec(0, 0, 1);

	//Main loop consists of applying joint rotation and then bone translation
	//For next bone do the same using the previous transformed coordinate system
	for (unsigned int i = 0; i < bones.size(); i++) {
		updateMatrices(currentMat, axisVec, i, false);
	}

	//Get chain end position
	return glm::vec3(currentMat * glm::vec4(0, 0, 0, 1));
}

unsigned int ChainModel::getNumJoints() const {
	return joints.size();
}

void ChainModel::updateMatrices(glm::mat4& currentMat, const glm::vec3& axisVec,
		unsigned int i, bool updateBone) const {

	//Update total transformation with current joint rotation
	currentMat = currentMat * glm::rotate(joints[i].getAngle(), axisVec);

	//Update total transformation with current bone translation
	currentMat = currentMat
			* glm::translate(glm::vec3(bones[i].getLength(), 0, 0));
}

glm::vec3 ChainModel::costFun(const glm::vec3& goal) const {
	return goal - getEndEfectorPos();
}
