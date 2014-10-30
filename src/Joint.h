/*
 * Joint.h
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_JOINT_H_
#define SRC_JOINT_H_

#include <boost/shared_ptr.hpp>

#include "Triangle.h"

class Joint: public Drawable {
public:
	Joint();
	virtual ~Joint();

	void draw(Renderer& renderer) const;

	float getAngle() const;
	void setAngle(float angle);

	TrianglePtr getDrawable();

private:
	float angle;
	TrianglePtr triangle;
};

typedef boost::shared_ptr<Joint> JointPtr;

#endif /* SRC_JOINT_H_ */
