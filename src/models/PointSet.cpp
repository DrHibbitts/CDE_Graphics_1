/*
 * PointSet.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "PointSet.h"

PointSet::PointSet(const unsigned int capacity) {

	originalCapacity = capacity;

	generateBuffers();

	//Preallocate for capacity size
	vertices.resize(capacity);
	colors.resize(capacity);
	indices.resize(capacity);

	for (unsigned int i = 0; i < capacity; i++) {
		indices[i] = i;
	}

	primitivePar.setValues(GL_POINTS, 0, 0);

	updateBuffers();
}

PointSet::~PointSet() {
}

void PointSet::addPoint(const glm::vec3& p) {

	if ((unsigned int) primitivePar.getCount() == vertices.size()) {
		resizeDataVectors();
	}

	vertices.at(primitivePar.getCount()) = p;

	primitivePar.setCount(primitivePar.getCount() + 1);
}

void PointSet::removeAllPoints() {
	primitivePar.setCount(0);
}

void PointSet::resizeDataVectors() {

	unsigned int currentSize, newSize;
	currentSize = vertices.size();
	newSize = currentSize + originalCapacity * 0.5;

	vertices.resize(newSize);
	colors.resize(newSize);
	indices.resize(newSize);

	for (unsigned int i = currentSize; i < newSize; i++) {
		colors[i] = colors[currentSize - 1];
		indices[i] = i;
	}

	updateBuffers();
}
