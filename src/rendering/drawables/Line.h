/*
 * Line.h
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#ifndef LINE_H_
#define LINE_H_

#include "VertexObject.h"

class Line: public VertexObject {
public:
	Line();
	//Create a line from v0 to v1
	Line(const glm::vec3& v0, const glm::vec3& v1);
	virtual ~Line();

	void setColors(const glm::vec3& c0, const glm::vec3& c1);
	void setVertices(const glm::vec3& v0, const glm::vec3& v1);
private:
	void init();
};

typedef boost::shared_ptr<Line> LinePtr;

#endif /* LINE_H_ */
