/*
 * JointModelModel.cpp
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#include "JointModel.h"

JointModel::JointModel() {
	setZRotAngle(0);
}

JointModel::JointModel(float angle) {
	setZRotAngle(angle);
}

JointModel::~JointModel() {
}

float JointModel::getZRotAngle() const {
	return ZRotAngle;
}

void JointModel::setZRotAngle(float angle) {
	this->ZRotAngle = angle;
}

