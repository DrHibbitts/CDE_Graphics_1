/*
 * Render.cpp
 *
 *  Created on: 11 Oct 2014
 *      Author: garoe
 */

#include "Renderer.h"

Renderer::Renderer()
{
	// Dark blue background
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	loadDefaultShaders();

	// Get a handle for our "MVP" uniform
	MatrixID = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45º Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	//Projection = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, 0.0f, 100.0f);
	// Or, for an ortho camera :
	Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates

	// Camera matrix, position, look at vector, up vector
	View = glm::lookAt(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0));

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices

	glGenBuffers(1, &vertexBuffer);

	glGenBuffers(1, &colorBuffer);

	glGenBuffers(1, &indexBuffer);
}

Renderer::~Renderer()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteVertexArrays(1, &indexBuffer);
	glDeleteProgram(programID);
}

void Renderer::resetScreen()
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	// Use our shader
	glUseProgram(programID);
}

void Renderer::drawPrimitive(const std::vector<glm::vec3>& vertices,
		const std::vector<unsigned int> indices,
		const std::vector<glm::vec3>& colors, const glm::mat4& Model,
		const PrimitiveParameter& param)
{
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP = Projection * View * Model;
	// Send our transformation to the currently bound shader,
	// in the "MVP" uniform
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	setUpBuffer(0, vertexBuffer, vertices);

	setUpBuffer(1, colorBuffer, colors);

	setUpIndexBuffer(indexBuffer, indices);

	// Draw count vertices in mode starting at first
	//glDrawArrays(param.getMode(), param.getFirst(), param.getCount());
	// Draw with indices: mode, count, type, index array buffer offset
	glDrawElements(param.getMode(), param.getCount(), GL_UNSIGNED_INT,
			(void*) 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Renderer::loadDefaultShaders()
{
	// Create and compile our GLSL program from the shaders
	programID = shaderLoader.loadShaderProgram(
			"../CDE_Graphics_1/src/vertexShader.glsl",
			"../CDE_Graphics_1/src/fragmentShader.glsl");
}

void Renderer::setUpBuffer(GLuint index, GLuint bufferType,
		const std::vector<glm::vec3>& bufferData)
{
	glEnableVertexAttribArray(index);
	glBindBuffer(GL_ARRAY_BUFFER, bufferType);
	glBufferData(GL_ARRAY_BUFFER, bufferData.size() * sizeof(glm::vec3),
			&bufferData[0], GL_STATIC_DRAW);
	//index matches shader num, size, type, not normalize, stride, buffer offset
	glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
}

void Renderer::setUpIndexBuffer(GLuint bufferType,
		const std::vector<unsigned int>& bufferData)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferType);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferData.size() * sizeof(glm::vec3),
			&bufferData[0], GL_STATIC_DRAW);
}
