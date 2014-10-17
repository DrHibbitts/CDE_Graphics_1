/*
 * DrawableObject.h
 *
 *  Created on: 11 Oct 2014
 *      Author: garoe
 */

#ifndef DRAWABLEOBJECT_H_
#define DRAWABLEOBJECT_H_

// Include GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "Drawable.h"
#include "PrimitiveParameter.h"

class VertexObject: public Drawable
{
public:
	VertexObject();
	virtual ~VertexObject() = 0;

	void translate(const glm::vec3& translation);
	void rotate(float angle, const glm::vec3& rotationAxis);

	const glm::mat4& getModelMat() const;
	const std::vector<glm::vec3>& getVertices() const;
	const std::vector<unsigned int>& getIndices() const;
	const std::vector<glm::vec3>& getColors() const;
	const PrimitiveParameter& getPrimitivePar() const;

	void setUniformColor(const glm::vec3& color);

protected:
	void generateBuffers();
	void populateBuffers() const;
	void initVAO() const;
	void sendDataToShader() const;
	void updateBuffers() const;

protected:
	glm::mat4 modelMat;
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> colors;
	PrimitiveParameter primitivePar;

	// VAO : Vertex Attributes Array.
	GLuint vao;

	// VBO : Vertex buffer object for transformed vertex data, first coordinate
	// is vertex position second is vertex color
	GLuint vbo;

	// EBO : Elements-Buffer object.
	GLuint ebo;

	// CBO : Color buffer object
	GLuint cbo;
};

typedef boost::shared_ptr<VertexObject> VertexObjectPtr;

#endif /* DRAWABLEOBJECT_H_ */
