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
		pointSet(new PointSet()) {
	drawTrail = true;
	pointSet->setUniformColor(glm::vec3(0.5, 0.9, 0.1));
}

Chain::~Chain() {
}

void Chain::draw(Renderer& renderer) const {
	glm::mat4 currentMat, rotMat;
	glm::vec3 boneTranslation;
	//Rotate along z axis
	glm::vec3 axisVec(0, 0, 1);

	//Main loop consists of applying joint rotation and then bone translation
	//For next bone do the same using the previous transformed coordinate system
	for (unsigned int i = 0; i < bones.size(); i++) {
		//Calculate rotation by the current joint
		rotMat = glm::rotate(joints[i]->getAngle(), axisVec);

		//Set joint position at the beginning of the current bone
		joints[i]->getDrawable()->setModelMat(currentMat);

		//Update total transformation with current joint rotation
		currentMat = currentMat * rotMat;

		//Bone total transformation is current transformation
		bones[i]->getDrawable()->setModelMat(currentMat);

		//Render the joints later so the bones appear on the background
		bones[i]->draw(renderer);

		joints[i]->draw(renderer);

		//Update total transformation with current bone translation
		boneTranslation.x = bones[i]->getLength();
		currentMat = currentMat * glm::translate(boneTranslation);
	}

	if (!drawTrail) {
		return;
	}

	//Get chain end position
	glm::vec3 currentEnd = glm::vec3(currentMat * glm::vec4(0, 0, 0, 1));

	//If end position is different than last point in the trail then
	//add new end position to trail
	if (pointSet->getLastVertex() != currentEnd) {
		pointSet->addPoint(currentEnd);
	}

	pointSet->draw(renderer);
}

void Chain::addBone(float size) {
	bones.push_back(BonePtr(new Bone(size)));
	joints.push_back(JointPtr(new Joint()));
}

void Chain::setJointAngle(unsigned int index, float angle) {
	joints.at(index)->setAngle(angle * TO_RAD);
}

float Chain::getJointAngle(unsigned int index) {
	return joints.at(index)->getAngle() * TO_DEG;
}

glm::vec3 Chain::getEndEfectorPos() const {
	glm::mat4 currentMat, rotMat;
	glm::vec3 boneTranslation;
	//Rotate along z axis
	glm::vec3 axisVec(0, 0, 1);

	//Main loop consists of applying joint rotation and then bone translation
	//For next bone do the same using the previous transformed coordinate system
	for (unsigned int i = 0; i < bones.size(); i++) {
		//Calculate rotation by the current joint
		rotMat = glm::rotate(joints[i]->getAngle(), axisVec);

		//Set joint position at the beginning of the current bone
		//joints[i]->getDrawable()->setModelMat(currentMat);

		//Update total transformation with current joint rotation
		currentMat = currentMat * rotMat;

		//Bone total transformation is current transformation
		//bones[i]->getDrawable()->setModelMat(currentMat);

		//Update total transformation with current bone translation
		boneTranslation.x = bones[i]->getLength();
		currentMat = currentMat * glm::translate(boneTranslation);
	}

	//Get chain end position
	return glm::vec3(currentMat * glm::vec4(0, 0, 0, 1));
}

unsigned int Chain::getNumJoints() const {
	return joints.size();
}

Chain::Chain(const Chain& otherChain) {
	drawTrail = false;
	pointSet = PointSetPtr(new PointSet());

	joints.resize(otherChain.joints.size());
	bones.resize(otherChain.bones.size());

	for (unsigned int i = 0; i < joints.size(); i++) {
		joints[i] = JointPtr(new Joint(otherChain.joints[i]->getAngle()));
		bones[i] = BonePtr(new Bone(otherChain.bones[i]->getLength()));
	}
}

glm::vec3 Chain::costFun(const glm::vec3& goal) const {
	return goal - getEndEfectorPos();
}
