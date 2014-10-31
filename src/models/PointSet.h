/*
 * PointSet.h
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_MODELS_POINTSET_H_
#define SRC_MODELS_POINTSET_H_

#include "VertexObject.h"

class PointSet: public VertexObject {
public:
	PointSet(const unsigned int capacity = 500);
	virtual ~PointSet();

	void addPoint(const glm::vec3& p);

	void removeAllPoints();
private:
	void resizeDataVectors();

	unsigned int originalCapacity;
};

typedef boost::shared_ptr<PointSet> PointSetPtr;

#endif /* SRC_MODELS_POINTSET_H_ */
