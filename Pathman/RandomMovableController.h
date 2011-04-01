#pragma once

#include "MovableController.h"

class Board;

/*!
	Controller that forces controlled object to behave randomly.
*/
class RandomMovableController : MovableController
{
public:
	/*!
		Constructs controller.
		@param board Board instance.
		@param turnProbability Probability (from 0 to 1 inclusively) 
		of change of direction.
		@param movable Controlled object (can be set up later).
	*/
	RandomMovableController(Board* board, 
		irr::f32 turnProbability, Movable* movable = NULL);
	~RandomMovableController(void);

	/*!
		Implementation of IController.
	*/

	void refresh();

	bool OnEvent(const irr::SEvent& event);

private:
	Board* _board;
	irr::f32 _turnProbability;
};