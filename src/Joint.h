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

class Joint: public Triangle
{
public:
	Joint();
	virtual ~Joint();

	float getAngle() const;
	void setAngle(float angle);

private:
	float angle;
};

typedef boost::shared_ptr<Joint> JointPtr;

#endif /* SRC_JOINT_H_ */
