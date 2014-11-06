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

#include "Drawable.h"
#include "Bone.h"
#include "Joint.h"
#include "PointSet.h"

//Chain of bones and joints
class Chain: public Drawable {
public:
	Chain();
	virtual ~Chain();

	void draw(Renderer& renderer) const;

	//When a bone is added a new joint is created in the end of the previous
	//last bone
	void addBone(float size);
	void setJointAngle(unsigned int index, float angle);

	float getJointAngle(unsigned int index);

	unsigned int getNumJoints() const;

	glm::vec3 getEndEfectorPos() const;

	glm::vec3 costFun(const glm::vec3& goal) const;
private:
	std::vector<JointPtr> joints;
	std::vector<BonePtr> bones;
	PointSetPtr pointSet;
	bool drawTrail;
};

typedef boost::shared_ptr<Chain> ChainPtr;

#endif /* SRC_CHAIN_H_ */
