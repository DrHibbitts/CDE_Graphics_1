/*
 * JointModelModel.cpp
 *
 *  Created on: 11 Nov 2014
 *      Author: gdp24
 */

#include "JointModel.h"

JointModel::JointModel() {
	setAngles(0, 0);
}

JointModel::JointModel(float zRotAngle, float yRotAngle) {
	setAngles(zRotAngle, yRotAngle);
}

JointModel::~JointModel() {
}

void JointModel::setAngles(float zRotAngle, float yRotAngle) {
	setZRotAngle(zRotAngle);
	setYRotAngle(yRotAngle);
}

float JointModel::getZRotAngle() const {
	return zRotAngle;
}

void JointModel::setZRotAngle(float angle) {
	this->zRotAngle = angle;
}

float JointModel::getYRotAngle() const {
	return yRotAngle;
}

void JointModel::setYRotAngle(float angle) {
	this->yRotAngle = angle;
}

