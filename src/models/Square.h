/*
 * Square.h
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_SQUARE_H_
#define SRC_SQUARE_H_

#include "VertexObject.h"

class Square: public VertexObject {
public:
	Square();
	virtual ~Square();

	// v2 - v3
	// v0 - v1
	//Create a square using the vertices in the above order
	Square(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2,
			const glm::vec3& v3);

	void setColors(const glm::vec3& c0, const glm::vec3& c1,
			const glm::vec3& c2, const glm::vec3& c3);
	void setVertices(const glm::vec3& v0, const glm::vec3& v1,
			const glm::vec3& v2, const glm::vec3& v3);

private:
	void init();
};
typedef boost::shared_ptr<Square> SquarePtr;
#endif /* SRC_SQUARE_H_ */
