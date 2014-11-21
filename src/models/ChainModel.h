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

//Chain of bones and joints
class ChainModel {
public:
	ChainModel();
	virtual ~ChainModel();

	//Assign operator
	ChainModel& operator=(const ChainModel& otherChain);

	void clear();

	//When a bone is added a new joint is created in the end of the previous
	//bone
	void addBone(float size);

	float getJointZAngle(unsigned int index) const;
	void setJointZAngle(unsigned int index, float zAngle);

	float getJointYAngle(unsigned int index) const;
	void setJointYAngle(unsigned int index, float yAngle);

	void setJointAngles(unsigned int index, float zAngle, float yAngle);

	void setAngleConstrains(double minZ, double maxZ, double minY, double maxY);
	void setBoneStiffness(unsigned int index, float stiffness);
	float getBoneStiffness(unsigned int index) const;

	float getBoneLength(unsigned int index) const;

	unsigned int getNumJoints() const;

	glm::vec3 getEndEfectorPos() const;

	glm::vec3 costFun(const glm::vec3& goal) const;

	double getMaxY() const;
	void setMaxY(double maxY);
	double getMaxZ() const;
	void setMaxZ(double maxZ);
	double getMinY() const;
	void setMinY(double minY);
	double getMinZ() const;
	void setMinZ(double minZ);
	double getMaximumRadius() const;

private:
	void updateMatrices(glm::mat4& currentMat, unsigned int i) const;

protected:
	const static glm::vec3 zAxis;
	const static glm::vec3 yAxis;
	double minZ, maxZ, minY, maxY;
	std::vector<float> stiffness;
	double maximumRadius;

private:
	std::vector<JointModel> joints;
	std::vector<BoneModel> bones;
};

#endif /* SRC_MODELS_CHAINMODEL_H_ */
