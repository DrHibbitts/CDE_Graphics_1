/*
 * Joint.h
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_JOINT_H_
#define SRC_JOINT_H_

#include <boost/shared_ptr.hpp>

#include "../../models/JointModel.h"
#include "Cube.h"

class Joint: public JointModel, public Drawable {
public:
	Joint();
	Joint(float zAngle, float yAngle);
	virtual ~Joint();

	void draw(Renderer& renderer) const;

	void setAngles(float zAngle, float yAngle);

	void setZRotAngle(float angle);

	void setYRotAngle(float angle);

	CubePtr getDrawable();

private:
	CubePtr cube;
};

typedef boost::shared_ptr<Joint> JointPtr;

#endif /* SRC_JOINT_H_ */
