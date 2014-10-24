/*
 * DrawableObject.h
 *
 *  Created on: 11 Oct 2014
 *      Author: garoe
 */

#ifndef DRAWABLEOBJECT_H_
#define DRAWABLEOBJECT_H_

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include <boost/shared_ptr.hpp>

#include "Drawable.h"
#include "PrimitiveParameter.h"

//Abstract class that agglutinates all the common methods and attributes of
//simple objects: Line, Triangle, Square
class VertexObject: public Drawable {
public:
	VertexObject();
	virtual ~VertexObject() = 0;

	void draw(Renderer& renderer) const;

	void translate(const glm::vec3& translation);
	void rotate(float angle, const glm::vec3& rotationAxis);

	const glm::mat4& getModelMat() const;
	const std::vector<glm::vec3>& getVertices() const;
	const std::vector<unsigned int>& getIndices() const;
	const std::vector<glm::vec3>& getColors() const;
	const PrimitiveParameter& getPrimitivePar() const;

	//Set a color for all the vertices
	void setUniformColor(const glm::vec3& color);
	void setModelMat(const glm::mat4& modelMat);

protected:
	void generateBuffers();
	void populateBuffers() const;
	void initVAO() const;
	void sendDataToShader() const;
	void updateBuffers() const;

protected:
	//Model matrix defines the object transformation
	glm::mat4 modelMat;
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<glm::vec3> colors;

	//OpenGL parameters holder object
	PrimitiveParameter primitivePar;

	//Common object and buffers needed for OpenGL rendering
	// VAO : Vertex Attributes Array.
	GLuint vao;

	// VBO : Vertex buffer object
	GLuint vbo;

	// EBO : Elements-Buffer object.
	GLuint ebo;

	// CBO : Color buffer object
	GLuint cbo;
};

typedef boost::shared_ptr<VertexObject> VertexObjectPtr;

#endif /* DRAWABLEOBJECT_H_ */
