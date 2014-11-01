/*
 * PointSet.cpp
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#include "PointSet.h"

glm::vec3 PointSet::empty;

PointSet::PointSet(const unsigned int capacity) {
}

PointSet::~PointSet() {
}

void PointSet::draw(Renderer& renderer) const {
	for (unsigned int i = 0; i < pointVec.size(); i++) {
		pointVec.at(i)->draw(renderer);
	}
}

void PointSet::addPoint(const glm::vec3& p) {
	pointVec.push_back(PointPtr(new Point(p)));
	pointVec.back()->setUniformColor(glm::vec3(0.5, 0.9, 0.1));
}

void PointSet::removeAllPoints() {
	pointVec.clear();
}

unsigned int PointSet::getTotalSize() const {
	return pointVec.size();
}

const glm::vec3& PointSet::getLastVertex() const {
	if (pointVec.size() == 0) {
		return empty;
	}

	return pointVec.back()->getVertices().at(0);
}
