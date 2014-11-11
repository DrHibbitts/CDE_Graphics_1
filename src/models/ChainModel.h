/*
 * ChainModel.h
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#ifndef SRC_MODELS_CHAINMODEL_H_
#define SRC_MODELS_CHAINMODEL_H_

#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "JointModel.h"
#include "BoneModel.h"

class ChainModel {
public:
	ChainModel();
	virtual ~ChainModel();
	ChainModel(const ChainModel& ChainModel);

	//When a bone is added a new joint is created in the end of the previous
	//last bone
	void addBone(float size);
	void setJointAngle(unsigned int index, float angle);

	float getJointAngle(unsigned int index);

	unsigned int getNumJoints() const;

	glm::vec3 getEndEfectorPos() const;

	glm::vec3 costFun(const glm::vec3& goal) const;

	void updateMatrices(glm::mat4& currentMat, const glm::vec3& axisVec,
			unsigned int i, bool updateBone) const;
private:
	std::vector<JointModel> joints;
	std::vector<BoneModel> bones;
};

#endif /* SRC_MODELS_CHAINMODEL_H_ */
