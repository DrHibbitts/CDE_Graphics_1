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
	nbo = 0;
	bufferType = GL_STATIC_DRAW;
}

VertexObject::~VertexObject() {
	destroyBuffers();
}

void VertexObject::draw(Renderer& renderer) const {
	sendDataToShader(renderer);

	//Draw count objects of mode type
	glDrawElements(primitivePar.getMode(), primitivePar.getCount(),
	GL_UNSIGNED_INT, (void*) 0);

	//Left here for reference, alternative drawing method
	//Used in earlier stages of the application
	//glDrawArrays(param.getMode(), param.getFirst(), param.getCount());

	//Clean up the binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexObject::generateBuffers() {
	// Generate a VAO for the Mesh and bind it as the active one.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Generate a VBO and bind it for holding vertex data.
	glGenBuffers(1, &vbo);

	// Generate an EBO and bind it for holding vertex indices.
	glGenBuffers(1, &ebo);
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Generate an CBO and bind it for holding vertex indices.
	glGenBuffers(1, &cbo);

	//Generate a NBO
	glGenBuffers(1, &nbo);
}

void VertexObject::populateBuffers() const {
	const unsigned int vboSize = vertices.size() * sizeof(glm::vec3);
	const unsigned int eboSize = indices.size() * sizeof(unsigned int);
	//Writes vertex, color and index data in the buffers, should only be called
	//once at object creation for efficiency purposes

	//Activate vbo
	glBindBuffer( GL_ARRAY_BUFFER, vbo);
	// Populate the VBO.
	glBufferData( GL_ARRAY_BUFFER, vboSize, &(vertices[0]), bufferType);

	glBindBuffer( GL_ARRAY_BUFFER, cbo);
	// Populate the VBO.
	glBufferData( GL_ARRAY_BUFFER, vboSize, &(colors[0]), bufferType);

	//Activate nbo
	glBindBuffer( GL_ARRAY_BUFFER, nbo);
	// Populate the NBO.
	glBufferData( GL_ARRAY_BUFFER, vboSize, &(normals[0]), bufferType);

	// Populate the EBO.
	glBufferData( GL_ELEMENT_ARRAY_BUFFER, eboSize, &(indices[0]), bufferType);

	//Clean up the binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexObject::initVAO() const {
	// Set the organisation of the vertex and normals data in the VBO.
	glBindVertexArray(vao);
	glBindBuffer( GL_ARRAY_BUFFER, vbo);
	//Clean up the binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexObject::sendDataToShader(Renderer& renderer) const {
	// Bind VAO and Buffers as the active ones.
	glBindVertexArray(vao);

	//Enable vertex buffer
	glEnableVertexAttribArray(0);
	glBindBuffer( GL_ARRAY_BUFFER, vbo);
	//Set vertex buffer structure
	// Buffer index, components per vertex, data type, normalised, offset for
	// interleaving, offset for first element
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	//Enable color buffer
	glEnableVertexAttribArray(1);
	glBindBuffer( GL_ARRAY_BUFFER, cbo);
	//Set color buffer structure
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	//Enable normal buffer
	glEnableVertexAttribArray(2);
	glBindBuffer( GL_ARRAY_BUFFER, nbo);
	//Set normal buffer structure
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	//Enable element buffer
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ebo);

	renderer.sendModelMatToShader(modelMat);
}

void VertexObject::updateBuffers() const {
	populateBuffers();
	initVAO();
}

glm::vec3 VertexObject::getCurrentPosition() const {
	return glm::vec3(modelMat * glm::vec4(centroid, 1));
}

void VertexObject::destroyBuffers() const {
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &cbo);
	glDeleteBuffers(1, &nbo);
	glDeleteVertexArrays(1, &vao);
}

void VertexObject::setModelMat(const glm::mat4& modelMat) {
	this->modelMat = modelMat;
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
