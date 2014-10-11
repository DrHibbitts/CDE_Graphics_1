/*
 * Triangle.h
 *
 *  Created on: 11 Oct 2014
 *      Author: garoe
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "VertexObject.h"

class Triangle: public VertexObject
{
public:
	Triangle();
	Triangle(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2);

	void draw(Renderer& renderer) const;

	void setColors(const glm::vec3& c0, const glm::vec3& c1,
			const glm::vec3& c2);
	void setVertices(const glm::vec3& v0, const glm::vec3& v1,
			const glm::vec3& v2);
private:
	void init();
};

typedef boost::shared_ptr<Triangle> TrianglePtr;

#endif /* TRIANGLE_H_ */
