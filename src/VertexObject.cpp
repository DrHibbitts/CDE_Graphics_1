/*
 * DrawableObject.cpp
 *
 *  Created on: 11 Oct 2014
 *      Author: garoe
 */

#include "VertexObject.h"

VertexObject::VertexObject()
{
}

VertexObject::~VertexObject()
{
}

void VertexObject::translate(const glm::vec3& translation)
{
	modelMat = glm::translate(modelMat, translation);
}

void VertexObject::rotate(float angle, const glm::vec3& rotationAxis)
{
	modelMat = glm::rotate(modelMat, angle, rotationAxis);
}

const glm::mat4& VertexObject::getModelMat() const
{
	return modelMat;
}

const std::vector<glm::vec3>& VertexObject::getVertices() const
{
	return vertices;
}

const std::vector<unsigned int>& VertexObject::getIndices() const
{
	return indices;
}

const std::vector<glm::vec3>& VertexObject::getColors() const
{
	return colors;
}

const PrimitiveParameter& VertexObject::getPrimitivePar() const
{
	return primitivePar;
}

void VertexObject::setUniformColor(const glm::vec3& color)
{
	colors.assign(colors.size(), color);
}
