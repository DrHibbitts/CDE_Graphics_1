/*
 * Chain.h
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_CHAIN_H_
#define SRC_CHAIN_H_

#define GLM_FORCE_RADIANS
#include <glm/gtx/transform.hpp>

#include "../../models/ChainModel.h"
#include "Drawable.h"
#include "Bone.h"
#include "Joint.h"
#include "PointSet.h"

class Chain: public Drawable, public ChainModel {
public:
	Chain();
	virtual ~Chain();

	virtual void draw(Renderer& renderer) const;

	//When a bone is added a new joint is created in the end of the previous
	//last bone
	void addBone(float size);
	void setJointZAngle(unsigned int index, float zAngle);
	void setJointYAngle(unsigned int index, float zAngle);
	void setJointAngles(unsigned int index, float zAngle, float yAngle);

	//Copy current Chain data into chainModel
	void copyToModel(ChainModel& chainModel) const;
private:
	std::vector<JointPtr> joints;
	std::vector<BonePtr> bones;
	PointSetPtr pointSet;
	bool drawingTrail;
	double trailEpsilon;

	void drawBonesJoints(Renderer& renderer, glm::mat4& currentMat) const;
	void drawTrail(Renderer& renderer, const glm::mat4& currentMat) const;
	void updateMatrices(glm::mat4& currentMat, unsigned int i) const;
};

typedef boost::shared_ptr<Chain> ChainPtr;

#endif /* SRC_CHAIN_H_ */
