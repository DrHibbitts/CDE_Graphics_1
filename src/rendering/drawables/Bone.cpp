/*
 * Bone.cpp
 *
 *  Created on: 22 Oct 2014
 *      Author: garoe
 */

#include "Bone.h"

Bone::Bone() :
		BoneModel(), cube(new Cube()) {
}

Bone::Bone(float length) :
		BoneModel(length), cube(new Cube()) {
	setLength(length);
}

Bone::~Bone() {
}

void Bone::draw(Renderer& renderer) const {
	cube->draw(renderer);
}

void Bone::setLength(float length) {
	BoneModel::setLength(length);

	cube->setUniformColor(glm::vec3(1, 1, 0));
	// Set the cube to be as long as the bone, then move the cube centre to
	// match the bone centre
	cube->setWidth(length, glm::vec3(length * 0.5, 0, 0));
	cube->setHeight(0.1);
	cube->setDepth(0.1);
}

CubePtr Bone::getDrawable() {
	return cube;
}
