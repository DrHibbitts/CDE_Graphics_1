/*
 * Bone.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Bone.h"

Bone::Bone() {
	setLength(1);
}

Bone::Bone(float length) {
	setLength(length);
}

Bone::~Bone() {
}

float Bone::getLength() const {
	return length;
}

void Bone::setLength(float length) {
	this->length = length;
	setVertices(glm::vec3(0, 0, 0), glm::vec3(length, 0, 0));
	setUniformColor(glm::vec3(0, 0, 1));
}
