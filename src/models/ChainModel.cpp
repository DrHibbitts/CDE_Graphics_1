/*
 * ChainModel.cpp
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#include "ChainModel.h"

#define TO_RAD  M_PI / 180.0
#define TO_DEG  180.0 / M_PI

const glm::vec3 ChainModel::zAxis(0, 0, 1);
const glm::vec3 ChainModel::yAxis(0, 1, 0);

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

void ChainModel::setJointZAngle(unsigned int index, float zAngle) {
	joints.at(index).setZRotAngle(zAngle * TO_RAD);
}

void ChainModel::setJointYAngle(unsigned int index, float yAngle) {
	joints.at(index).setYRotAngle(yAngle * TO_RAD);
}

void ChainModel::setJointAngles(unsigned int index, float zAngle,
		float yAngle) {
	joints.at(index).setAngles(zAngle * TO_RAD, yAngle * TO_RAD);
}

float ChainModel::getJointZAngle(unsigned int index) const {
	return joints.at(index).getZRotAngle() * TO_DEG;
}

float ChainModel::getJointYAngle(unsigned int index) const {
	return joints.at(index).getYRotAngle() * TO_DEG;
}

float ChainModel::getBoneLength(unsigned int index) const {
	return bones.at(index).getLength();
}

glm::vec3 ChainModel::getEndEfectorPos() const {
	glm::mat4 currentMat, rotMat;

	//Main loop consists of applying joint rotation and then bone translation
	//For next bone do the same using the previous transformed coordinate system
	for (unsigned int i = 0; i < bones.size(); i++) {
		updateMatrices(currentMat, i, false);
	}

	//Get chain end position
	return glm::vec3(currentMat * glm::vec4(0, 0, 0, 1));
}

unsigned int ChainModel::getNumJoints() const {
	return joints.size();
}

void ChainModel::updateMatrices(glm::mat4& currentMat, unsigned int i,
		bool updateBone) const {

	//Update total transformation with current joint rotation and translation
	currentMat = currentMat * glm::rotate(joints[i].getZRotAngle(), zAxis)
			* glm::rotate(joints[i].getYRotAngle(), yAxis)
			* glm::translate(glm::vec3(bones[i].getLength(), 0, 0));
}

glm::vec3 ChainModel::costFun(const glm::vec3& goal) const {
	return goal - getEndEfectorPos();
}
