/*
 * Cube.h
 *
 *  Created on: 15 Nov 2014
 *      Author: garoe
 */

#ifndef SRC_RENDERING_DRAWABLES_CUBE_H_
#define SRC_RENDERING_DRAWABLES_CUBE_H_

#include "VertexObject.h"

class Cube: public VertexObject {
public:
	Cube();
	Cube(const glm::vec3& centre, double width, double height);
	virtual ~Cube();

	void setWidth(double width);
	void setHeight(double height);
private:
	void init();
	void calculateNormals();
	void setInidices();

private:
	glm::vec3 centre;
	double width;
	double height;
	std::vector<glm::vec3> indexVec3;
};

typedef boost::shared_ptr<Cube> CubePtr;

#endif /* SRC_RENDERING_DRAWABLES_CUBE_H_ */
