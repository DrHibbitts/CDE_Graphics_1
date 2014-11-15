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
#include "Square.h"

class Joint: public JointModel, public Drawable {
public:
	Joint();
	Joint(float angle);
	virtual ~Joint();

	void draw(Renderer& renderer) const;

	void setAngle(float angle);

	SquarePtr getDrawable();

private:
	SquarePtr square;
};

typedef boost::shared_ptr<Joint> JointPtr;

#endif /* SRC_JOINT_H_ */
