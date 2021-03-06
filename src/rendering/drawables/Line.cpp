/*
 * Line.cpp
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#include "Line.h"

Line::Line() {
	init();
}

Line::Line(const glm::vec3& v0, const glm::vec3& v1) {
	init();
	setVertices(v0, v1);
}

Line::~Line() {
}

void Line::setVertices(const glm::vec3& v0, const glm::vec3& v1) {
	vertices[0] = v0;
	vertices[1] = v1;

	centroid = (float) 0.5 * (v0 + v1);

	updateBuffers();
}

void Line::setColors(const glm::vec3& c0, const glm::vec3& c1) {
	colors[0] = c0;
	colors[1] = c1;

	updateBuffers();
}

void Line::init() {
	generateBuffers();

	//A line has two vertices and is drawn with GL_LINES
	vertices.resize(2);
	colors.resize(2);
	normals.resize(2, glm::vec3(0, 0, -1));
	indices.push_back(0);
	indices.push_back(1);
	primitivePar.setValues(GL_LINES, 0, indices.size());
}
