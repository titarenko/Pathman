#include "MovableController.h"

MovableController::MovableController(Movable* movable)
	: _movable(movable)
{
}

MovableController::~MovableController(void)
{
}

void MovableController::setMovable(Movable* movable)
{
	_movable = movable;
}