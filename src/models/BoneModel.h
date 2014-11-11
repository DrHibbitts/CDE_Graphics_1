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

	float getWidth() const;
	void setWidth(float width);

private:
	float length;
	float width;
};

#endif /* SRC_BONEMODEL_H_ */
