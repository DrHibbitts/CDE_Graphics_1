/*
 * Triangle.cpp
 *
 *  Created on: 11 Oct 2014
 *      Author: garoe
 */

#include "Triangle.h"

Triangle::Triangle()
{
	init();
}

Triangle::Triangle(const glm::vec3& v0, const glm::vec3& v1,
		const glm::vec3& v2)
{
	init();
	setVertices(v0, v1, v2);
}

void Triangle::draw(Renderer& renderer) const
{
	sendDataToShader();
	glm::mat4 MVP = renderer.getViewProjectionMatrix() * modelMat;

	glUniformMatrix4fv(renderer.getMvPlocation(), 1, GL_FALSE, &(MVP[0][0]));

	// Draw count vertices in mode starting at first
	//glDrawArrays(param.getMode(), param.getFirst(), param.getCount());
	// Draw with indices: mode, count, type, index array buffer offset
	glDrawElements(primitivePar.getMode(), primitivePar.getCount(),
	GL_UNSIGNED_INT, (void*) 0);
}

void Triangle::setVertices(const glm::vec3& v0, const glm::vec3& v1,
		const glm::vec3& v2)
{
	vertices[0] = v0;
	vertices[1] = v1;
	vertices[2] = v2;

	updateBuffers();
}

void Triangle::setColors(const glm::vec3& c0, const glm::vec3& c1,
		const glm::vec3& c2)
{
	colors[0] = c0;
	colors[1] = c1;
	colors[2] = c2;

	updateBuffers();
}

void Triangle::init()
{
	generateBuffers();

	vertices.resize(3);
	colors.resize(3);
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	primitivePar.setValues(GL_TRIANGLES, 0, 3);
}
