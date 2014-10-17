/*
 * Axis.cpp
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#include "Axis.h"

Axis::Axis() :
		xAxis(new Line()), yAxis(new Line()), zAxis(new Line())
{
	xAxis->setVertices(glm::vec3(0, 0, 0), glm::vec3(1, 0, 0));
	yAxis->setVertices(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	zAxis->setVertices(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));

	xAxis->setUniformColor(glm::vec3(1, 0, 0)); //Red
	yAxis->setUniformColor(glm::vec3(0, 1, 0)); //Green
	zAxis->setUniformColor(glm::vec3(0, 0, 1)); //Blue
}

Axis::~Axis()
{
}

void Axis::draw(Renderer& renderer) const
{
	xAxis->draw(renderer);
	yAxis->draw(renderer);
	zAxis->draw(renderer);
}

const LinePtr Axis::getXAxis() const
{
	return xAxis;
}

const LinePtr Axis::getYAxis() const
{
	return yAxis;
}

const LinePtr Axis::getZAxis() const
{
	return zAxis;
}
