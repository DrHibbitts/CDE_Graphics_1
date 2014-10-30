/*
 * Bone.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Bone.h"

Bone::Bone() :
		square(new Square()) {
	width = 0.05;
	setLength(1);
}

Bone::Bone(float length) :
		square(new Square()) {
	width = 0.05;
	setLength(length);
}

Bone::~Bone() {
}

void Bone::draw(Renderer& renderer) const {
	square->draw(renderer);
}

float Bone::getLength() const {
	return length;
}

void Bone::setLength(float length) {
	this->length = length;
	// 3 - 4
	// 1 - 2
	//width = length * 0.1;
	square->setVertices(glm::vec3(0, -width, 0), glm::vec3(length, -width, 0),
			glm::vec3(0, width, 0), glm::vec3(length, width, 0));

	square->setUniformColor(glm::vec3(1, 1, 0));
}

SquarePtr Bone::getDrawable() {
	return square;
}
