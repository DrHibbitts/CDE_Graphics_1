/*
 * Point3DMarker.cpp
 *
 *  Created on: 16 Nov 2014
 *      Author: garoe
 */

#include "Point3DMarker.h"

Point3DMarker::Point3DMarker() :
		xLine(new Cube()), yLine(new Cube()), zLine(new Cube()) {
	xLine->resize(0.01);
	xLine->setWidth(0.5);

	yLine->resize(0.01);
	yLine->setHeight(0.5);

	zLine->resize(0.01);
	zLine->setDepth(0.5);

	//White
	xLine->setUniformColor(glm::vec3(0.9, 0.9, 0.9));
	yLine->setUniformColor(glm::vec3(0.9, 0.9, 0.9));
	zLine->setUniformColor(glm::vec3(0.9, 0.9, 0.9));
}

Point3DMarker::~Point3DMarker() {

}

void Point3DMarker::draw(Renderer& renderer) const {
	xLine->draw(renderer);
	yLine->draw(renderer);
	zLine->draw(renderer);
}

void Point3DMarker::translate(const glm::vec3& translation) {
	xLine->translate(translation);
	yLine->translate(translation);
	zLine->translate(translation);
}

void Point3DMarker::rotate(float angle, const glm::vec3& rotationAxis) {
	xLine->rotate(angle, rotationAxis);
	yLine->rotate(angle, rotationAxis);
	zLine->rotate(angle, rotationAxis);
}

void Point3DMarker::setUniformColor(const glm::vec3& color) {
	xLine->setUniformColor(color);
	yLine->setUniformColor(color);
	zLine->setUniformColor(color);
}

glm::vec3 Point3DMarker::getCurrentPosition() const {
	return xLine->getCurrentPosition();
}
