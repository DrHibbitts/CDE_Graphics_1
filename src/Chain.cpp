/*
 * Chain.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Chain.h"

Chain::Chain()
{
}

Chain::~Chain()
{
}

void Chain::draw(Renderer& renderer) const
{
	glm::mat4 currentMat, rotMat;
	glm::vec3 boneLength;
	//Rotate along z axis
	glm::vec3 axisVec(0, 0, 1);

	for (unsigned int i = 0; i < bones.size(); i++)
	{
		//Calculate rotation for the current joint
		rotMat = glm::rotate(joints[i]->getAngle(), axisVec);

		//Set joint position at the beginning of the bone
		joints[i]->setModelMat(currentMat);

		joints[i]->draw(renderer);

		//Apply joint rotation
		currentMat = currentMat * rotMat;

		bones[i]->setModelMat(currentMat);

		bones[i]->draw(renderer);

		//Apply bone translation
		boneLength.x = bones[i]->getLength();
		currentMat = currentMat * glm::translate(boneLength);
	}
}

void Chain::addBone(float size)
{
	bones.push_back(BonePtr(new Bone(size)));
	joints.push_back(JointPtr(new Joint()));
}

void Chain::setJointAngle(unsigned int index, float angle)
{
	joints.at(index)->setAngle(angle);
}
