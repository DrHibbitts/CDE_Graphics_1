/*
 * ChainModel.h
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#ifndef SRC_MODELS_CHAINMODEL_H_
#define SRC_MODELS_CHAINMODEL_H_

#include <vector>
#include <cmath>

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "JointModel.h"
#include "BoneModel.h"

class ChainModel {
public:
	ChainModel();
	virtual ~ChainModel();

	void clear();

	//When a bone is added a new joint is created in the end of the previous
	//last bone
	void addBone(float size);
	void setJointZAngle(unsigned int index, float zAngle);
	void setJointYAngle(unsigned int index, float yAngle);
	void setJointAngles(unsigned int index, float zAngle, float yAngle);

	float getBoneLength(unsigned int index) const;
	float getJointZAngle(unsigned int index) const;
	float getJointYAngle(unsigned int index) const;

	unsigned int getNumJoints() const;

	glm::vec3 getEndEfectorPos() const;

	glm::vec3 costFun(const glm::vec3& goal,
			std::vector<double> angleConstrains) const;

private:
	void updateMatrices(glm::mat4& currentMat, unsigned int i,
			bool updateBone) const;

protected:
	const static glm::vec3 zAxis;
	const static glm::vec3 yAxis;

private:
	std::vector<JointModel> joints;
	std::vector<BoneModel> bones;
};

#endif /* SRC_MODELS_CHAINMODEL_H_ */
