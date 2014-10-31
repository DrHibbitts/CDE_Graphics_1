/*
 * DrawPrimitive.h
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_PRIMITIVEPARAMETER_H_
#define SRC_PRIMITIVEPARAMETER_H_

#include <GL/glew.h>

//Container class for OpenGL draw calls
class PrimitiveParameter {
public:
	PrimitiveParameter();
	PrimitiveParameter(GLenum mode, GLint first, GLsizei count);
	virtual ~PrimitiveParameter();

	GLenum getMode() const;

	GLint getFirst() const;

	GLsizei getCount() const;
	void setCount(GLsizei count);

	void setValues(GLenum mode, GLint first, GLsizei count);

private:
	//Draw mode: GL_POINTS, GL_LINE, GL_TRIANGLE, etc
	GLenum mode;

	//Index of the first element in the buffer, no need to start in the first
	GLint first;

	//Number of vertices to be used
	GLsizei count;

};

#endif /* SRC_PRIMITIVEPARAMETER_H_ */
