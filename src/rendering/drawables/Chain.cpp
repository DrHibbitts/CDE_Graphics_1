/*
 * Chain.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Chain.h"

#define TO_RAD  M_PI / 180.0
#define TO_DEG  180.0 / M_PI

Chain::Chain() :
		ChainModel(), pointSet(new PointSet()) {
	drawingTrail = true;
	pointSet->setUniformColor(glm::vec3(0.5, 0.9, 0.1));
	trailEpsilon = 0.01;
}

Chain::~Chain() {
}

void Chain::draw(Renderer& renderer) const {
	glm::mat4 currentMat;

	drawBonesJoints(renderer, currentMat);

	if (!drawingTrail) {
		return;
	}

	drawTrail(renderer, currentMat);
}

void Chain::addBone(float size) {
	ChainModel::addBone(size);
	bones.push_back(BonePtr(new Bone(size)));
	joints.push_back(JointPtr(new Joint()));
}

void Chain::setJointZAngle(unsigned int index, float zAngle) {
	ChainModel::setJointZAngle(index, zAngle);
	joints.at(index)->setZRotAngle(zAngle * TO_RAD);
}

void Chain::setJointYAngle(unsigned int index, float yAngle) {
	ChainModel::setJointYAngle(index, yAngle);
	joints.at(index)->setYRotAngle(yAngle * TO_RAD);
}
void Chain::setJointAngles(unsigned int index, float zAngle, float yAngle) {
	ChainModel::setJointAngles(index, zAngle, yAngle);
	joints.at(index)->setAngles(zAngle * TO_RAD, yAngle * TO_RAD);
}

void Chain::updateMatrices(glm::mat4& currentMat, unsigned int i) const {

	//Set joint position at the beginning of the current bone
	joints[i]->getDrawable()->setModelMat(currentMat);

	//Update total transformation with current joint rotation
	currentMat = currentMat * glm::rotate(joints[i]->getZRotAngle(), zAxis)
			* glm::rotate(joints[i]->getYRotAngle(), yAxis);

	//Bone total transformation is current transformation
	bones[i]->getDrawable()->setModelMat(currentMat);

	//Update total transformation with current bone translation
	currentMat = currentMat
			* glm::translate(glm::vec3(bones[i]->getLength(), 0, 0));
}

void Chain::drawBonesJoints(Renderer& renderer, glm::mat4& currentMat) const {
	//Main loop consists of applying joint rotation and then bone translation
	//For next bone do the same using the previous transformed coordinate system
	for (unsigned int i = 0; i < bones.size(); i++) {
		//Calculate joint rotations and bone translations
		updateMatrices(currentMat, i);

		//Render the current bone and the current joint
		bones[i]->draw(renderer);
		joints[i]->draw(renderer);
	}
}

void Chain::drawTrail(Renderer& renderer, const glm::mat4& currentMat) const {
	//Get chain end position
	glm::vec3 currentEnd = glm::vec3(currentMat * glm::vec4(0, 0, 0, 1));

	//If end position is different than last point in the trail then
	//add new end position to trail
	if (glm::length(pointSet->getLastVertex() - currentEnd) > trailEpsilon) {
		pointSet->addPoint(currentEnd);
	}
	pointSet->draw(renderer);
}
