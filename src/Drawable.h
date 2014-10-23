/*
 * Drawable.h
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_DRAWABLE_H_
#define SRC_DRAWABLE_H_

#include "boost/shared_ptr.hpp"

#include "Renderer.h"

class Drawable {
public:
	inline virtual ~Drawable() {
	}
	;
	virtual void draw(Renderer& renderer) const = 0;
};

typedef boost::shared_ptr<Drawable> DrawablePtr;

#endif /* SRC_DRAWABLE_H_ */
