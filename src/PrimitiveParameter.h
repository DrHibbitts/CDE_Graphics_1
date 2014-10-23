/*
 * DrawPrimitive.h
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_PRIMITIVEPARAMETER_H_
#define SRC_PRIMITIVEPARAMETER_H_

#include <GL/glew.h>

class PrimitiveParameter {
public:
	PrimitiveParameter();
	PrimitiveParameter(GLenum mode, GLint first, GLsizei count);
	virtual ~PrimitiveParameter();

	GLenum getMode() const;
	GLint getFirst() const;
	GLsizei getCount() const;

	void setValues(GLenum mode, GLint first, GLsizei count);
private:
	GLenum mode;
	GLint first;
	GLsizei count;

};

#endif /* SRC_PRIMITIVEPARAMETER_H_ */
