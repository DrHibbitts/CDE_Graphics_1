/*
 * Point.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "Point.h"

Point::Point() {
	init();
}

Point::Point(const glm::vec3& v) {
	init();
	setVertex(v);
}

Point::~Point() {
}

void Point::setVertex(const glm::vec3& v) {
	vertices[0] = v;

	updateBuffers();
}

void Point::init() {
	generateBuffers();

	//A line has one vertex and is drawn with GL_POINTS
	vertices.resize(1);
	colors.resize(1);
	indices.push_back(0);
	primitivePar.setValues(GL_POINTS, 0, 1);
}
