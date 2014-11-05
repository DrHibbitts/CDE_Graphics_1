/*
 * Drawable.h
 *
 *  Created on: 12 Oct 2014
 *      Author: garoe
 */

#ifndef SRC_DRAWABLE_H_
#define SRC_DRAWABLE_H_

#include "boost/shared_ptr.hpp"

#include "../rendering/Renderer.h"

//Abstract class that defines a common interface to be rendered
//Any subclass of Drawable can be rendered by Window
class Drawable {
public:
	inline virtual ~Drawable() {
	}
	;
	virtual void draw(Renderer& renderer) const = 0;
};

typedef boost::shared_ptr<Drawable> DrawablePtr;

//TODO Add model matrix and getter and setters????

#endif /* SRC_DRAWABLE_H_ */
