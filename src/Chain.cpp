/*
 * Chain.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Chain.h"

#define TO_RAD  M_PI / 180.0

Chain::Chain() {
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
		joints[i]->setModelMat(currentMat);

		joints[i]->draw(renderer);

		//Update total transformation with current joint rotation
		currentMat = currentMat * rotMat;

		//Bone total transformation is current transformation
		bones[i]->setModelMat(currentMat);

		bones[i]->draw(renderer);

		//Update total transformation with current bone translation
		boneTranslation.x = bones[i]->getLength();
		currentMat = currentMat * glm::translate(boneTranslation);
	}
}

void Chain::addBone(float size) {
	bones.push_back(BonePtr(new Bone(size)));
	joints.push_back(JointPtr(new Joint()));
}

void Chain::setJointAngle(unsigned int index, float angle) {
	joints.at(index)->setAngle(angle * TO_RAD);
}
