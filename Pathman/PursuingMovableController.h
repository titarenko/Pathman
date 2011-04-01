#pragma once

#include "MovableController.h"
#include "EDirection.h"

class Board;
class Movable;

/*!
	Represents controller that forces controlled to pursue the target.
*/
class PursuingMovableController : MovableController
{
public:
	/*!
		Creates controller.
		@param board Board instance.
		@param target Target movable.
		@param movable Controlled movable (can be set up later).
	*/
	PursuingMovableController(Board* board, 
		Movable* target, Movable* movable = NULL);
	~PursuingMovableController(void);

	/*!
		Implementation of IController.
	*/

	void refresh();

	bool OnEvent(const irr::SEvent& event);

private:
	Board* _board;
	Movable* _target;

	irr::u32 _previousTargetPosition;
	irr::core::array<irr::u32> _usedPositions;

	irr::core::array<E_DIRECTION> getAvailableDirections();
};