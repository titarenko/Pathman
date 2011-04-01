#pragma once

#include "IController.h"

class Movable;

/*!
	Represents base class for controller with movable
	as controlled object.
*/
class MovableController : public IController
{
public:
	/*!
		Constructs controller for given object.
		@param movable Controlled object (can be set up later).
	*/
	MovableController(Movable* movable = NULL);
	~MovableController(void);

	/*!
		Sets controlled object.
	*/
	void setMovable(Movable* movable);

protected:
	Movable* _movable;
};