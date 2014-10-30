/*
 * Bone.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Bone.h"

Bone::Bone() :
		line(new Line()) {
	setLength(1);
}

Bone::Bone(float length) :
		line(new Line()) {
	setLength(length);
}

Bone::~Bone() {
}

void Bone::draw(Renderer& renderer) const {
	line->draw(renderer);
}

float Bone::getLength() const {
	return length;
}

void Bone::setLength(float length) {
	this->length = length;
	line->setVertices(glm::vec3(0, 0, 0), glm::vec3(length, 0, 0));
	line->setUniformColor(glm::vec3(1, 1, 0));
}

LinePtr Bone::getDrawable() {
	return line;
}
