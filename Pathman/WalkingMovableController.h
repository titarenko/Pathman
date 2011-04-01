#pragma once

#include "MovableController.h"
#include "EDirection.h"

/*!
	Controller that forces controlled object to behave very straightforward
	walking along a predetermined route. 
*/
class WalkingMovableController : MovableController
{
public:
	/*!
		Creates controller.
		@param directions A set of directions defining 
		controlled object's behaviour.
		@param movable Controlled object (can be set up later).
	*/
	WalkingMovableController(
		const irr::core::list<E_DIRECTION>& directions,
		Movable* movable = NULL);
	~WalkingMovableController(void);

	/*!
		Implementation of IController.
	*/

	void refresh();

	bool OnEvent(const irr::SEvent& event);

private:
	irr::core::list<E_DIRECTION> _directions;
	irr::core::list<E_DIRECTION>::ConstIterator _iterator;
};