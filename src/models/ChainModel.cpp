/*
 * ChainModel.cpp
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#include "ChainModel.h"

ChainModel::ChainModel() {
	// TODO Auto-generated constructor stub

}

ChainModel::~ChainModel() {
	// TODO Auto-generated destructor stub
}

void ChainModel::updateMatrices(glm::mat4& currentMat, const glm::vec3& axisVec,
		unsigned int i, bool updateBone) const {

	//Update total transformation with current joint rotation
	currentMat = currentMat * glm::rotate(joints[i].getAngle(), axisVec);

	//Update total transformation with current bone translation
	currentMat = currentMat
			* glm::translate(glm::vec3(bones[i].getLength(), 0, 0));
}
