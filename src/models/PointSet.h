/*
 * PointSet.h
 *
 *  Created on: 31 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_MODELS_POINTSET_H_
#define SRC_MODELS_POINTSET_H_

#include "Drawable.h"
#include "Point.h"
#include <vector>

class PointSet: public Drawable {
public:
	PointSet(const unsigned int capacity = 100);
	virtual ~PointSet();

	void draw(Renderer& renderer) const;

	void addPoint(const glm::vec3& p);

	void removeAllPoints();

	const glm::vec3& getLastVertex() const;

	unsigned int getTotalSize() const;

private:
	std::vector<PointPtr> pointVec;
	static glm::vec3 empty;
};

typedef boost::shared_ptr<PointSet> PointSetPtr;

#endif /* SRC_MODELS_POINTSET_H_ */
