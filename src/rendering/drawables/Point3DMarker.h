/*
 * Point3DMarker.h
 *
 *  Created on: 16 Nov 2014
 *      Author: garoe
 */

#ifndef SRC_RENDERING_DRAWABLES_POINT3DMARKER_H_
#define SRC_RENDERING_DRAWABLES_POINT3DMARKER_H_

#include "Drawable.h"
#include "Cube.h"

class Point3DMarker: public Drawable {
public:
	Point3DMarker();
	virtual ~Point3DMarker();

	void draw(Renderer& renderer) const;

	void translate(const glm::vec3& translation);
	void rotate(float angle, const glm::vec3& rotationAxis);

	void setUniformColor(const glm::vec3& color);

	glm::vec3 getCurrentPosition() const;
private:
	CubePtr xLine, yLine, zLine;
};

typedef boost::shared_ptr<Point3DMarker> Point3DMarkerPtr;

#endif /* SRC_RENDERING_DRAWABLES_POINT3DMARKER_H_ */
