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

	float getZRotAngle() const;
	void setZRotAngle(float angle);
private:
	float ZRotAngle;
	float YRotAngle;
};

#endif /* SRC_JOINTMODEL_H_ */
