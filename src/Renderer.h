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
#include "PrimitiveParameter.h"

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();

	void resetScreen();

	//Use the first three vertices to draw a triangle
	void drawPrimitive(const std::vector<glm::vec3>& vertices,
			const std::vector<unsigned int> indices,
			const std::vector<glm::vec3>& colors, const glm::mat4& Model,
			const PrimitiveParameter& param);

	const glm::mat4& getViewProjectionMatrix() const;
	GLuint getMvPlocation() const;

private:
	void loadDefaultShaders();
	//TODO BufferData should be called only when the object is created
	void setUpBuffer(GLuint index, GLuint bufferType,
			const std::vector<glm::vec3>& bufferData);

	void setUpIndexBuffer(GLuint bufferType,
			const std::vector<unsigned int>& bufferData);

private:
	ShaderLoader shaderLoader;
	GLuint programID;
	GLuint VertexArrayID;
	GLuint MVPlocation;
	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint indexBuffer;
	glm::mat4 View;
	glm::mat4 Projection;
	glm::mat4 ViewProjection;
};

#endif /* RENDERER_H_ */
