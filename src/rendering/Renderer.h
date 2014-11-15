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

	void rotateCamera();

	void translateCamera(const glm::vec3& offset);

	void zoomCamera();

	const glm::mat4& getViewProjectionMatrix() const;

	glm::vec3 getWorldCoordFromScreen(const glm::vec3& screenCoord);

	GLuint getMVPlocation() const;
	GLuint getProgramId() const;

private:
	void updateView();

	void loadDefaultShaders();

private:
	ShaderLoader shaderLoader;
	GLuint programID;

	GLuint MVPlocation;

	glm::mat4 View;
	glm::mat4 Projection;
	glm::mat4 ViewProjection;

	glm::vec3 camPosition;
	glm::vec3 camLookAt;
	glm::vec3 camUp;
};

#endif /* RENDERER_H_ */
