/*
 * BoneModel.cpp
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#include "BoneModel.h"

BoneModel::BoneModel() {
	setLength(1);
}

BoneModel::BoneModel(float length) {
	setLength(length);
}

BoneModel::~BoneModel() {
}

float BoneModel::getLength() const {
	return length;
}

void BoneModel::setLength(float length) {
	this->length = length;
}
