/*
 * PointSet.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "PointSet.h"

PointSet::PointSet(const unsigned int capacity) {
	halfCapacity = capacity * 0.5;

	generateBuffers();

	//Point set is going to preallocate capacity size in buffer data
	//to avoid buffer to many buffer reallocations
	vertices.resize(capacity);
	colors.resize(capacity);
	indices.resize(capacity);

	//Since we are rendering points each i index belongs to i vertex
	for (unsigned int i = 0; i < capacity; i++) {
		indices[i] = i;
	}

	//Render points, starting at 0 and 0 size
	primitivePar.setValues(GL_POINTS, 0, 0);

	//Since the data is likely to change in each frame set the buffer types
	//to dynamic
	bufferType = GL_DYNAMIC_DRAW;

	size = 0;

	updateBuffers();
}

PointSet::~PointSet() {
}

void PointSet::updateDynamicBuffer() {
	//Activate vbo
	glBindBuffer( GL_ARRAY_BUFFER, vbo);

	//Calculate next free position in the buffer
	unsigned int byteOffset = size * sizeof(glm::vec3);

	//Insert the new vertex at byteOffset position
	glBufferSubData(GL_ARRAY_BUFFER, byteOffset, sizeof(glm::vec3),
			&(vertices[size]));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PointSet::addPoint(const glm::vec3& p) {

	if (size == vertices.size()) {
		resizeDataVectors();
	}

	vertices.at(size) = p;

	//Faster dynamic way to update buffer information on OpenGL
	updateDynamicBuffer();

	size++;
	primitivePar.setCount(size);
}

void PointSet::removeAllPoints() {
	size = 0;
	primitivePar.setCount(size);
}

unsigned int PointSet::getSize() const {
	return size;
}

void PointSet::resizeDataVectors() {
	//We ran out of buffer space, resize everything and allocate bigger buffers
	unsigned int currentSize, newSize;
	currentSize = vertices.size();
	newSize = currentSize + halfCapacity;

	vertices.resize(newSize);
	colors.resize(newSize);
	indices.resize(newSize);

	for (unsigned int i = currentSize; i < newSize; i++) {
		colors[i] = colors[currentSize - 1];
		indices[i] = i;
	}

	//Do a full buffer update, I believe this can be done more efficiently
	//with glBufferSubData, but lets count on this method not get called
	//too often
	destroyBuffers();
	generateBuffers();
	updateBuffers();
}

const glm::vec3& PointSet::getLastVertex() const {
	if (size == 0) {
		return vertices.at(size);
	}

	return vertices.at(size - 1);
}
