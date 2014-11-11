/*
 * JointModelModel.cpp
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#include "JointModel.h"

JointModel::JointModel() {
	setAngle(0);
}

JointModel::JointModel(float angle) {
	setAngle(angle);
}

JointModel::~JointModel() {
}

float JointModel::getAngle() const {
	return angle;
}

void JointModel::setAngle(float angle) {
	this->angle = angle;
}

