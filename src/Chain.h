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

#include "Renderer.h"
#include "Joint.h"
#include "Bone.h"
#include "Drawable.h"

class Chain: public Drawable {
public:
	Chain();
	virtual ~Chain();

	void draw(Renderer& renderer) const;

	void addBone(float size);
	void setJointAngle(unsigned int index, float angle);
private:
	std::vector<JointPtr> joints;
	std::vector<BonePtr> bones;
};

typedef boost::shared_ptr<Chain> ChainPtr;

#endif /* SRC_CHAIN_H_ */
