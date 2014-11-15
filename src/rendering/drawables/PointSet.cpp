/*
 * PointSet.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "PointSet.h"

PointSet::PointSet(const unsigned int capacity) {
	generateBuffers();

	//Point set is going to preallocate capacity size in buffer data
	//to avoid buffer to many buffer reallocations
	vertices.resize(capacity);
	colors.resize(capacity);
	indices.resize(capacity);
	normals.resize(capacity);

	//Since we are rendering points each i index belongs to i vertex
	for (unsigned int i = 0; i < capacity; i++) {
		indices[i] = i;
	}

	//Render points, starting at 0 and 0 size
	primitivePar.setValues(GL_POINTS, 0, 0);

	//Since the data is likely to change in each frame set the buffer types
	//to dynamic
	bufferType = GL_DYNAMIC_DRAW;

	currentIndex = 0;
	totalSize = 0;

	updateBuffers();
}

PointSet::~PointSet() {
}

void PointSet::updateDynamicBuffer() {
	//Activate vbo
	glBindBuffer( GL_ARRAY_BUFFER, vbo);

	//Calculate next free position in the buffer
	unsigned int byteOffset = currentIndex * sizeof(glm::vec3);

	//Insert the new vertex at byteOffset position
	glBufferSubData(GL_ARRAY_BUFFER, byteOffset, sizeof(glm::vec3),
			&(vertices[currentIndex]));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PointSet::addPoint(const glm::vec3& p) {

	//If we reach the end, insert points at the beginning of the buffer
	if (currentIndex == vertices.size()) {
		currentIndex = 0;
	}

	//Increment the number of points being drawn if possible
	if (totalSize < vertices.size()) {
		totalSize++;
	}

	vertices.at(currentIndex) = p;

	//Faster dynamic way to update buffer information on OpenGL
	updateDynamicBuffer();

	currentIndex++;
	primitivePar.setCount(totalSize);
}

void PointSet::removeAllPoints() {
	currentIndex = 0;
	totalSize = 0;
	primitivePar.setCount(totalSize);
}

unsigned int PointSet::getSize() const {
	return totalSize;
}

void PointSet::resizeDataVectors() {
	//We ran out of buffer space, resize everything and allocate bigger buffers
	unsigned int currentSize = vertices.size();
	totalSize = 2 * currentSize;

	vertices.resize(totalSize);
	colors.resize(totalSize);
	indices.resize(totalSize);
	normals.resize(totalSize);

	for (unsigned int i = currentSize; i < totalSize; i++) {
		colors[i] = colors[currentSize - 1];
		indices[i] = i;
	}

	//Do a full buffer update, this is slow, better preallocate enough space
	destroyBuffers();
	generateBuffers();
	updateBuffers();
}

const glm::vec3& PointSet::getLastVertex() const {
	//If the vector is empty return an empty vertex
	if (currentIndex == 0) {
		return vertices.at(currentIndex);
	}

	return vertices.at(currentIndex - 1);
}
