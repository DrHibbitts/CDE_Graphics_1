/*
 * Bone.h
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_BONE_H_
#define SRC_BONE_H_

#include <boost/shared_ptr.hpp>

#include "../../models/BoneModel.h"
#include "Cube.h"

class Bone: public Drawable, public BoneModel {
public:
	Bone();
	Bone(float length);
	virtual ~Bone();

	virtual void draw(Renderer& renderer) const;

	void setLength(float length);

	CubePtr getDrawable();

private:
	CubePtr cube;
};

typedef boost::shared_ptr<Bone> BonePtr;

#endif /* SRC_BONE_H_ */
