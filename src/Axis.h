/*
 * Axis.h
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_AXIS_H_
#define SRC_AXIS_H_

#include "Drawable.h"
#include "Line.h"

class Axis: public Drawable
{
public:
	Axis();
	virtual ~Axis();

	void draw(Renderer& renderer) const;

	const LinePtr getXAxis() const;
	const LinePtr getYAxis() const;
	const LinePtr getZAxis() const;

private:
	LinePtr xAxis;
	LinePtr yAxis;
	LinePtr zAxis;
};

typedef boost::shared_ptr<Axis> AxisPtr;

#endif /* SRC_AXIS_H_ */
