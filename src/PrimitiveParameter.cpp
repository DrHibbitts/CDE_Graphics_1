/*
 * DrawPrimitive.cpp
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#include "PrimitiveParameter.h"

PrimitiveParameter::PrimitiveParameter() {
	setValues(GL_POINTS, 0, 0);
}

PrimitiveParameter::PrimitiveParameter(GLenum mode, GLint first,
		GLsizei count) {
	setValues(mode, first, count);
}

PrimitiveParameter::~PrimitiveParameter() {
}

GLenum PrimitiveParameter::getMode() const {
	return mode;
}

GLint PrimitiveParameter::getFirst() const {
	return first;
}

GLsizei PrimitiveParameter::getCount() const {
	return count;
}

void PrimitiveParameter::setValues(GLenum mode, GLint first, GLsizei count) {
	this->mode = mode;
	this->count = count;
	this->first = first;
}
