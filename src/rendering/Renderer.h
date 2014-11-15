/*
 * Render.h
 *
 *  Created on: 11 Oct 2014
 *      Author: garoe
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <vector>

// Include GLEW
#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ShaderLoader.h"

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	void resetScreen();

	const glm::vec3& getCamLookAtVector() const;

	const glm::vec3& getCamLookAtRightVector() const;

	void updateCameraPosition(const glm::vec3& offset);

	void updateLookAt(float horizontalAngleOffset, float verticalAngleOffset);

	const glm::mat4& getViewProjectionMatrix() const;

	glm::vec3 getWorldCoordFromScreen(const glm::vec3& screenCoord);

	GLuint getMVPlocation() const;
	GLuint getProgramId() const;

private:
	void loadDefaultShaders();
	void updateView();

private:
	ShaderLoader shaderLoader;
	GLuint programID;

	GLuint MVPlocation;

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 viewProjection;

	glm::vec3 camPosition;
	glm::vec3 camLookAt;
	glm::vec3 camLookAtVector;
	glm::vec3 camRightVector;
	glm::vec3 camUp;

	// Initial horizontal angle : toward -Z
	float horizontalAngle;
	// Initial vertical angle : none
	float verticalAngle;

};

#endif /* RENDERER_H_ */
