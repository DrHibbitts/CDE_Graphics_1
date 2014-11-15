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

	void setCentre(const glm::vec3& centre);
	void setWidth(double width);
	void setHeight(double height);
private:
	void init();

private:
	double centre;
	double width;
	double eight;
};

typedef boost::shared_ptr<Cube> CubePtr;

#endif /* SRC_RENDERING_DRAWABLES_CUBE_H_ */
