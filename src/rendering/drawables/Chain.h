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

//Chain of bones and joints
class Chain: public Drawable, public ChainModel {
public:
	Chain();
	virtual ~Chain();

	void draw(Renderer& renderer) const;

	//When a bone is added a new joint is created in the end of the previous
	//last bone
	void addBone(float size);
	void setJointZAngle(unsigned int index, float ZAngle);

	void copyToModel(ChainModel& chainModel) const;
private:
	std::vector<JointPtr> joints;
	std::vector<BonePtr> bones;
	PointSetPtr pointSet;
	bool drawingTrail;
	double trailEpsilon;

	void drawBonesJoints(Renderer& renderer, glm::mat4& currentMat) const;
	void drawTrail(const glm::mat4& currentMat, Renderer& renderer) const;
	void updateMatrices(glm::mat4& currentMat, const glm::vec3& axisVec,
			unsigned int i) const;
};

typedef boost::shared_ptr<Chain> ChainPtr;

#endif /* SRC_CHAIN_H_ */
