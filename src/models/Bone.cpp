/*
 * Bone.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Bone.h"

Bone::Bone() :
		BoneModel(), square(new Square()) {
}

Bone::Bone(float length) :
		BoneModel(length), square(new Square()) {
	setLength(length);
}

Bone::~Bone() {
}

void Bone::draw(Renderer& renderer) const {
	square->draw(renderer);
}

void Bone::setLength(float length) {
	BoneModel::setLength(length);
	// 3 - 4
	// 1 - 2
	//width = length * 0.1;
	square->setVertices(glm::vec3(0, -getWidth(), 0),
			glm::vec3(getLength(), -getWidth(), 0), glm::vec3(0, getWidth(), 0),
			glm::vec3(getLength(), getWidth(), 0));

	square->setUniformColor(glm::vec3(1, 1, 0));
}

SquarePtr Bone::getDrawable() {
	return square;
}
