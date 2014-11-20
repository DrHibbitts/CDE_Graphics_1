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

#include <boost/shared_ptr.hpp>

#include "ShaderLoader.h"

class Renderer {
public:
	Renderer();
	virtual ~Renderer();

	void resetScreen();

	void resetCamera();

	const glm::vec3& getCamLookAtVector() const;

	const glm::vec3& getCamLookAtRightVector() const;

	const glm::vec3& getCamUpVector() const;

	void updateCameraPosition(const glm::vec3& offset);

	void updateCameraOrientation(float horizontalAngleOffset,
			float verticalAngleOffset);

	void sendModelMatToShader(const glm::mat4& modelMat) const;

	const glm::mat4& getViewProjectionMatrix() const;

	glm::vec3 getWorldCoordFromScreen(const glm::vec3& screenCoord);

	GLuint getMVPlocation() const;
	GLuint getProgramId() const;

private:
	void loadDefaultShaders();
	void updateView();

private:
	ShaderLoader shaderLoader;
	//Shader location in the GPU
	GLuint programID;

	//Matrices locations in the GPU
	GLuint MVPlocation;
	GLuint Vlocation;
	GLuint Mlocation;

	//Ligh position in the GPU
	GLuint LightID;

	//Model View Projection matrices
	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 viewProjection;

	//Camera attributes
	glm::vec3 camPosition;
	glm::vec3 camLookAtVector;
	glm::vec3 camRightVector;
	glm::vec3 camUp;
	//Camera horizontal angle
	float horizontalAngle;
	//Camera vertical angle
	float verticalAngle;
};

typedef boost::shared_ptr<Renderer> RendererPtr;

#endif /* RENDERER_H_ */
