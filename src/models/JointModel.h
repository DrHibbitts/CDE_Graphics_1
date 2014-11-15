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
	JointModel(float zRotAngle, float yRotAngle);
	virtual ~JointModel();

	void setAngles(float zRotAngle, float yRotAngle);

	float getZRotAngle() const;
	void setZRotAngle(float angle);

	float getYRotAngle() const;
	void setYRotAngle(float angle);
private:
	float zRotAngle;
	float yRotAngle;
};

#endif /* SRC_JOINTMODEL_H_ */
