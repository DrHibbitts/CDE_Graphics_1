/*
 * DrawableObject.cpp
 *
 *  Created on: 11 Oct 2014
 *      Author: garoe
 */

#include "VertexObject.h"

VertexObject::VertexObject() {
	vao = 0;
	vbo = 0;
	ebo = 0;
	cbo = 0;
}

VertexObject::~VertexObject() {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &cbo);
	glDeleteVertexArrays(1, &vao);
}

void VertexObject::draw(Renderer& renderer) const {
	sendDataToShader();
	glm::mat4 MVP = renderer.getViewProjectionMatrix() * modelMat;

	glUniformMatrix4fv(renderer.getMVPlocation(), 1, GL_FALSE, &(MVP[0][0]));

	// Draw count vertices in mode starting at first
	//glDrawArrays(param.getMode(), param.getFirst(), param.getCount());
	// Draw with indices: mode, count, type, index array buffer offset
	glDrawElements(primitivePar.getMode(), primitivePar.getCount(),
	GL_UNSIGNED_INT, (void*) 0);
}

void VertexObject::translate(const glm::vec3& translation) {
	modelMat = glm::translate(modelMat, translation);
}

void VertexObject::rotate(float angle, const glm::vec3& rotationAxis) {
	modelMat = glm::rotate(modelMat, angle, rotationAxis);
}

const glm::mat4& VertexObject::getModelMat() const {
	return modelMat;
}

const std::vector<glm::vec3>& VertexObject::getVertices() const {
	return vertices;
}

const std::vector<unsigned int>& VertexObject::getIndices() const {
	return indices;
}

const std::vector<glm::vec3>& VertexObject::getColors() const {
	return colors;
}

const PrimitiveParameter& VertexObject::getPrimitivePar() const {
	return primitivePar;
}

void VertexObject::setUniformColor(const glm::vec3& color) {
	colors.assign(colors.size(), color);

	updateBuffers();
}

void VertexObject::generateBuffers() {
	// Generate a VAO for the Mesh and bind it as the active one.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Generate a VBO and bind it for holding vertex data.
	glGenBuffers(1, &vbo);
	//glBindBuffer( GL_ARRAY_BUFFER, vbo);

	// Generate an EBO and bind it for holding vertex indices.
	glGenBuffers(1, &ebo);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Generate an CBO and bind it for holding vertex indices.
	glGenBuffers(1, &cbo);
	//glBindBuffer( GL_ARRAY_BUFFER, cbo);
}

void VertexObject::populateBuffers() const {
	const unsigned int vboSize = vertices.size() * sizeof(glm::vec3);
	const unsigned int eboSize = indices.size() * sizeof(glm::vec3);

	glBindBuffer( GL_ARRAY_BUFFER, vbo);
	// Populate the VBO.
	glBufferData( GL_ARRAY_BUFFER, vboSize, &(vertices[0]), GL_STATIC_DRAW);

	glBindBuffer( GL_ARRAY_BUFFER, cbo);
	// Populate the VBO.
	glBufferData( GL_ARRAY_BUFFER, vboSize, &(colors[0]), GL_STATIC_DRAW);

	// Populate the EBO.
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, eboSize, &(indices[0]),
	GL_STATIC_DRAW);
}

void VertexObject::initVAO() const {
	// Set the organisation of the vertex and normals data in the VBO.
	glBindVertexArray(vao);
	glBindBuffer( GL_ARRAY_BUFFER, vbo);
}

void VertexObject::sendDataToShader() const {
	// Bind VAO and Buffers as the active ones.
	glBindVertexArray(vao);

	//Enable vertex buffer
	glEnableVertexAttribArray(0);
	glBindBuffer( GL_ARRAY_BUFFER, vbo);
	//Set vertex buffer structure
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	//Enable color buffer
	glEnableVertexAttribArray(1);
	glBindBuffer( GL_ARRAY_BUFFER, cbo);
	//Set color buffer structure
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	//Enable element buffer
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo);
}

void VertexObject::updateBuffers() const {
	populateBuffers();
	initVAO();
}

void VertexObject::setModelMat(const glm::mat4& modelMat) {
	this->modelMat = modelMat;
}
