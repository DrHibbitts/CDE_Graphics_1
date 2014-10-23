/*
 * Render.cpp
 *
 *  Created on: 11 Oct 2014
 *      Author: garoe
 */

#include "Renderer.h"

Renderer::Renderer() {
	// Grey background
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);

	loadDefaultShaders();

	// Get a handle for our "MVP" uniform
	MVPlocation = glGetUniformLocation(programID, "MVP");

	// Projection matrix : 45º Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	//Projection = glm::ortho(0.0f, 1024.0f, 768.0f, 0.0f, 0.0f, 100.0f);
	// Or, for an ortho camera :

	Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates

	// Camera matrix, position, look at vector, up vector
	View = glm::lookAt(glm::vec3(0, 0, -3), glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0));
}

Renderer::~Renderer() {
	glDeleteProgram(programID);
}

void Renderer::resetScreen() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	//TODO Check is current program is the same, then do not load the shader again
	// Use our shader
	glUseProgram(programID);

	ViewProjection = Projection * View;
}

const glm::mat4& Renderer::getViewProjectionMatrix() const {
	return ViewProjection;
}

void Renderer::loadDefaultShaders() {
	// Create and compile our GLSL program from the shaders
	try {
		programID = shaderLoader.loadShaderProgram(
				"../CDE_Graphics_1/src/vertexShader.glsl",
				"../CDE_Graphics_1/src/fragmentShader.glsl");
		return;
	} catch (std::runtime_error& e) {
	}

	//Try a different path for the Shaders
	programID = shaderLoader.loadShaderProgram("../src/vertexShader.glsl",
			"../src/fragmentShader.glsl");
}

GLuint Renderer::getMVPlocation() const {
	return MVPlocation;
}
