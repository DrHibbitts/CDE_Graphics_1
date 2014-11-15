/*
 * Square.cpp
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#include "Square.h"

Square::Square() {
	init();
}

Square::~Square() {
}

Square::Square(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
		const glm::vec3& v3) {
	init();
	setVertices(v0, v1, v2, v3);
}

void Square::setVertices(const glm::vec3& v0, const glm::vec3& v1,
		const glm::vec3& v2, const glm::vec3& v3) {
	vertices[0] = v0;
	vertices[1] = v1;
	vertices[2] = v2;
	vertices[3] = v3;

	glm::vec3 normal = glm::normalize(
			glm::cross(vertices.at(0), vertices.at(1)));

	normals[0] = normal;
	normals[1] = normal;
	normals[2] = normal;
	normals[3] = normal;

	updateBuffers();
}

void Square::setColors(const glm::vec3& c0, const glm::vec3& c1,
		const glm::vec3& c2, const glm::vec3& c3) {
	colors[0] = c0;
	colors[1] = c1;
	colors[2] = c2;
	colors[3] = c3;

	updateBuffers();
}

void Square::init() {
	generateBuffers();

	vertices.resize(4);
	colors.resize(4);
	normals.resize(4);
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	//Squares are drawn using two triangles
	//GL_TRIANGLE_STRIP uses the first three vertices for the first triangle and
	//then uses a new one and the two previous for consequent triangles
	primitivePar.setValues(GL_TRIANGLE_STRIP, 0, indices.size());
}
