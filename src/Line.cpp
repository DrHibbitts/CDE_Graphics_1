/*
 * Line.cpp
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#include "Line.h"

Line::Line()
{
	init();
}

Line::Line(const glm::vec3& v0, const glm::vec3& v1)
{
	init();
	setVertices(v0, v1);
}

Line::~Line()
{
}

void Line::draw(Renderer& renderer) const
{
	renderer.drawPrimitive(vertices, indices, colors, modelMat, primitivePar);
}

void Line::setVertices(const glm::vec3& v0, const glm::vec3& v1)
{
	vertices[0] = v0;
	vertices[1] = v1;
}

void Line::setColors(const glm::vec3& c0, const glm::vec3& c1)
{
	colors[0] = c0;
	colors[1] = c1;
}

void Line::init()
{
	vertices.resize(2);
	colors.resize(2);
	indices.push_back(0);
	indices.push_back(1);
	primitivePar.setValues(GL_LINES, 0, 2);
}
