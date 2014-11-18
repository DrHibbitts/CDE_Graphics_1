/*
 * BoneModel.h
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#ifndef SRC_BONEMODEL_H_
#define SRC_BONEMODEL_H_

class BoneModel {
public:
	BoneModel();
	BoneModel(float length);
	virtual ~BoneModel();

	float getLength() const;
	void setLength(float length);

private:
	float length;
};

#endif /* SRC_BONEMODEL_H_ */
