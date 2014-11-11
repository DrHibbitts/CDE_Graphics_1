/*
 * Point.h
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_MODELS_POINT_H_
#define SRC_MODELS_POINT_H_

#include "VertexObject.h"

class Point: public VertexObject {
public:
	Point();
	Point(const glm::vec3& v);
	virtual ~Point();

	void setVertex(const glm::vec3& v);
private:
	void init();
};

typedef boost::shared_ptr<Point> PointPtr;

#endif /* SRC_MODELS_POINT_H_ */
