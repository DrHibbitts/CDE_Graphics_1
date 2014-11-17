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

	//Update total transformation with current joint rotation
	currentMat = currentMat * glm::rotate(joints[i].getYRotAngle(), yAxis)
			* glm::rotate(joints[i].getZRotAngle(), zAxis);

	//Update total transformation with current bone translation
	currentMat = currentMat
			* glm::translate(glm::vec3(bones[i].getLength(), 0, 0));
}

glm::vec3 ChainModel::costFun(const glm::vec3& goal,
		std::vector<double> angleConstrains) const {
	glm::vec3 distanceVec(goal - getEndEfectorPos());

	assert(angleConstrains.size() == 4);

	double penalty = 0;
	for (unsigned int i = 0; i < joints.size(); i++) {
		// If the angle gets close to the constraint then the penalty is increased
		// FLT_MIN is added to avoid 1 \ 0
		double aux = joints.at(i).getZRotAngle() - angleConstrains.at(0);
		penalty += 1.0 / std::abs(aux + FLT_MIN);

		aux = joints.at(i).getZRotAngle() - angleConstrains.at(1);
		penalty += 1.0 / std::abs(aux + FLT_MIN);

		aux = joints.at(i).getYRotAngle() - angleConstrains.at(2);
		penalty += 1.0 / std::abs(aux + FLT_MIN);

		aux = joints.at(i).getYRotAngle() - angleConstrains.at(3);
		penalty += 1.0 / std::abs(aux + FLT_MIN);
	}

	float anglePenalty = -0.01 * penalty;

	return (distanceVec + anglePenalty * glm::normalize(distanceVec));
}
