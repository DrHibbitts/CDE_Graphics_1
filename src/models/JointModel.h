/*
 * JointModel.h
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#ifndef SRC_JOINTMODEL_H_
#define SRC_JOINTMODEL_H_

class JointModel {
public:
	JointModel();
	JointModel(float angle);
	virtual ~JointModel();

	float getAngle() const;
	void setAngle(float angle);
private:
	float angle;
};

#endif /* SRC_JOINTMODEL_H_ */
