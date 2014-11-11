/*
 * BoneModel.cpp
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#include "BoneModel.h"

BoneModel::BoneModel() {
	width = 0.05;
	setLength(1);
}

BoneModel::BoneModel(float length) {
	width = 0.05;
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

float BoneModel::getWidth() const {
	return width;
}

void BoneModel::setWidth(float width) {
	this->width = width;
}
