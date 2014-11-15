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
	projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

	//Orthographic projection, left, right, bottom, top, zNear, zFar
	//Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);

	// Camera is looking towards Z, and up vector is Y
	horizontalAngle = 0.0f;
	verticalAngle = 0.0f;

	// Camera matrix, camera position, look at position, normalised up vector
	camPosition = glm::vec3(0, 0, -13);

	updateView();
}

Renderer::~Renderer() {
}

void Renderer::resetScreen() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Update ViewProjection matrix
	viewProjection = projection * view;
}

const glm::mat4& Renderer::getViewProjectionMatrix() const {
	return viewProjection;
}

const glm::vec3& Renderer::getCamLookAtVector() const {
	return camLookAtVector;
}

const glm::vec3& Renderer::getCamLookAtRightVector() const {
	return camRightVector;
}

void Renderer::updateCameraPosition(const glm::vec3& offset) {
	camPosition += offset;

	view = glm::lookAt(camPosition, camPosition + camLookAtVector, camUp);
}

void Renderer::updateLookAt(float horizontalAngleOffset,
		float verticalAngleOffset) {
	horizontalAngle += horizontalAngleOffset;
	verticalAngle += verticalAngleOffset;
	updateView();
}

GLuint Renderer::getMVPlocation() const {
	return MVPlocation;
}

GLuint Renderer::getProgramId() const {
	return programID;
}

glm::vec3 Renderer::getWorldCoordFromScreen(const glm::vec3& screenCoord) {
	//TODO Viewport should be given by Window
	glm::vec3 aux = glm::unProject(screenCoord, view, projection,
			glm::vec4(0, 0, 1024, 768));
	//TODO REALLY IMPORTANT This will not work on 3D
	aux.y = -aux.y;
	aux.z = 0;
	return aux;
}

void Renderer::updateView() {
	camLookAtVector = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

	camRightVector = glm::vec3(sin(horizontalAngle - M_PI_2), 0,
			cos(horizontalAngle - M_PI_2));

	camUp = glm::cross(camRightVector, camLookAtVector);

	view = glm::lookAt(camPosition, camPosition + camLookAtVector, camUp);
}

void Renderer::loadDefaultShaders() {
	// Create and compile our GLSL program from the shaders
	try {
		programID = shaderLoader.loadShaderProgram(
				"../CDE_Graphics_1/src/rendering/vertexShader.glsl",
				"../CDE_Graphics_1/src/rendering/fragmentShader.glsl");
		return;
	} catch (std::runtime_error& e) {
	}

	//Try a different path for the Shaders
	programID = shaderLoader.loadShaderProgram(
			"../src/rendering/vertexShader.glsl",
			"../src/rendering/fragmentShader.glsl");
}
