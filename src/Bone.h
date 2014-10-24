/*
 * Bone.h
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_BONE_H_
#define SRC_BONE_H_

#include <boost/shared_ptr.hpp>

#include "Line.h"

//Bone class defines a bone of size length on the x axis
class Bone: public Line {
public:
	Bone();
	Bone(float length);
	virtual ~Bone();
	float getLength() const;
	void setLength(float length);

private:
	float length;
};

typedef boost::shared_ptr<Bone> BonePtr;

#endif /* SRC_BONE_H_ */
