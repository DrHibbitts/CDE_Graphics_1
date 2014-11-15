/*
 * Cube.cpp
 *
 *  Created on: 15 Nov 2014
 *      Author: garoe
 */

#include "Cube.h"

Cube::Cube() {
	init();
}

Cube::Cube(const glm::vec3& centre, double width, double height) {
	init();
	setCentre(centre);
	setWidth(width);
	setHeight(height);
}

Cube::~Cube() {
}

void Cube::setCentre(const glm::vec3& centre) {

}

void Cube::setWidth(double width) {
}

void Cube::setHeight(double height) {
}

void Cube::init() {
	generateBuffers();

	centre = glm::vec3(0, 0, 0);
	width = 0.2;
	height = 0.2;

	vertices.resize(8);
	colors.resize(8);
	normals.resize(12);

	vertices[0] = glm::vec3(-0.1, -0.1, -0.1);
	vertices[1] = glm::vec3(0.1, -0.1, -0.1);
	vertices[2] = glm::vec3(0.1, -0.1, 0.1);
	vertices[3] = glm::vec3(-0.1, -0.1, 0.1);
	vertices[4] = glm::vec3(-0.1, 0.1, -0.1);
	vertices[5] = glm::vec3(0.1, 0.1, -0.1);
	vertices[6] = glm::vec3(0.1, 0.1, 0.1);
	vertices[7] = glm::vec3(-0.1, 0.1, 0.1);

	// 12 Triangles, 3 vertices
	indices.reserve(26);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);

	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	indices.push_back(4);
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(4);
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(4);

	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(7);

	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(5);

	indices.push_back(2);
	indices.push_back(5);
	indices.push_back(6);

	indices.push_back(2);
	indices.push_back(6);
	indices.push_back(7);

	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(7);

	indices.push_back(1);
	indices.push_back(4);
	indices.push_back(5);

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(4);

	// 12 triangles for a cube
	primitivePar.setValues(GL_TRIANGLES, 0, 26);

	updateBuffers();
}
