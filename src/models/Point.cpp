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

void Point::setColor(const glm::vec3& c) {
	colors[0] = c;

	updateBuffers();
}

void Point::setVertex(const glm::vec3& v) {
	vertices[0] = v;

	updateBuffers();
}

void Point::init() {
	generateBuffers();

	//A line has two vertices and is drawn with GL_LINES
	vertices.resize(1);
	colors.resize(1);
	indices.push_back(0);
	primitivePar.setValues(GL_POINTS, 0, 1);
}
