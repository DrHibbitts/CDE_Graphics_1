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
class Bone: public Drawable {
public:
	Bone();
	Bone(float length);
	virtual ~Bone();

	void draw(Renderer& renderer) const;

	float getLength() const;
	void setLength(float length);

	LinePtr getDrawable();

private:
	float length;
	LinePtr line;
};

typedef boost::shared_ptr<Bone> BonePtr;

#endif /* SRC_BONE_H_ */
