/*
 * Joint.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Joint.h"

Joint::Joint()
{
	setAngle(0);
}

Joint::~Joint()
{
}

float Joint::getAngle() const
{
	return angle;
}

void Joint::setAngle(float angle)
{
	this->angle = angle;

	setVertices(glm::vec3(0.1, -0.1, 0), glm::vec3(-0.1, -0.1, 0),
			glm::vec3(0, 0.1, 0));
	setUniformColor(glm::vec3(1, 0, 0));
}
