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
	setWidth(width);
	setHeight(height);
}

Cube::~Cube() {
}

void Cube::setWidth(double width) {
	glm::vec3 offset;
	offset.x = (width - (vertices[1].x - vertices[0].x) * 0.5);

	//TODO This works but is to localised
	vertices[1] += offset;
	vertices[2] += offset;
	vertices[5] += offset;
	vertices[6] += offset;

	//vertices[0] -= offset;
	//vertices[3] -= offset;
	//vertices[4] -= offset;
	//vertices[7] -= offset;

	calculateNormals();
	updateBuffers();
}

void Cube::setHeight(double height) {
	glm::vec3 offset;
	offset.y = (height - (vertices[4].y - vertices[0].y)) * 0.5;

	vertices[0] -= offset;
	vertices[1] -= offset;
	vertices[2] -= offset;
	vertices[3] -= offset;

	vertices[4] += offset;
	vertices[5] += offset;
	vertices[6] += offset;
	vertices[7] += offset;

	calculateNormals();
	updateBuffers();
}

void Cube::setDepth(double depth) {
	glm::vec3 offset;
	offset.z = (depth - (vertices[2].z - vertices[1].z)) * 0.5;

	vertices[0] -= offset;
	vertices[1] -= offset;
	vertices[4] -= offset;
	vertices[5] -= offset;

	vertices[2] += offset;
	vertices[3] += offset;
	vertices[6] += offset;
	vertices[7] += offset;

	calculateNormals();
	updateBuffers();
}

void Cube::init() {
	generateBuffers();

	centre = glm::vec3(0, 0, 0);
	width = 0.2;
	height = 0.2;

	vertices.resize(8);
	colors.resize(8);
	normals.resize(8);

	// Vertices are
	// On the y = -0.1 plane,    On the y = 0.1 plane
	// v2 - v3						v6 - v7
	// v1 - v0						v5 - v4
	//Eight vertices of the cube
	vertices[0] = glm::vec3(-0.1, -0.1, -0.1);
	vertices[1] = glm::vec3(0.1, -0.1, -0.1);
	vertices[2] = glm::vec3(0.1, -0.1, 0.1);
	vertices[3] = glm::vec3(-0.1, -0.1, 0.1);
	vertices[4] = glm::vec3(-0.1, 0.1, -0.1);
	vertices[5] = glm::vec3(0.1, 0.1, -0.1);
	vertices[6] = glm::vec3(0.1, 0.1, 0.1);
	vertices[7] = glm::vec3(-0.1, 0.1, 0.1);

	// 12 Triangles, 3 vertices
	indices.reserve(36);

	indexVec3.push_back(glm::vec3(0, 1, 2));
	indexVec3.push_back(glm::vec3(0, 2, 3));
	indexVec3.push_back(glm::vec3(4, 5, 6));
	indexVec3.push_back(glm::vec3(4, 6, 7));
	indexVec3.push_back(glm::vec3(0, 3, 4));
	indexVec3.push_back(glm::vec3(3, 4, 7));
	indexVec3.push_back(glm::vec3(1, 2, 5));
	indexVec3.push_back(glm::vec3(2, 5, 6));
	indexVec3.push_back(glm::vec3(2, 6, 7));
	indexVec3.push_back(glm::vec3(2, 3, 7));
	indexVec3.push_back(glm::vec3(1, 4, 5));
	indexVec3.push_back(glm::vec3(0, 1, 4));

	for (unsigned int i = 0; i < indexVec3.size(); i++) {
		indices.push_back(indexVec3.at(i).x);
		indices.push_back(indexVec3.at(i).y);
		indices.push_back(indexVec3.at(i).z);
	}

	calculateNormals();

	// 12 triangles for a cube
	primitivePar.setValues(GL_TRIANGLES, 0, indices.size());

	updateBuffers();
}

void Cube::calculateNormals() {
	for (unsigned int i = 0; i < normals.size(); i++) {
		normals.at(i) = glm::normalize(vertices.at(i));
	}
}
