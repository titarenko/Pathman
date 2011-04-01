#include "PursuingMovableController.h"
#include "Game.h"
#include "Board.h"
#include "Movable.h"

using namespace irr;
using namespace core;

PursuingMovableController::PursuingMovableController(
	Board* board, Movable* target, Movable* movable)
	: MovableController(movable)
	, _board(board)
	, _target(target)
{
}

PursuingMovableController::~PursuingMovableController(void)
{
}

void PursuingMovableController::refresh()
{
	_previousTargetPosition = _target->getPosition();
}

bool PursuingMovableController::OnEvent(const SEvent& event)
{
	if (Game::ToGameEvent(event) == EGE_FRAME_ENDED &&
		_movable->isStopped()) {

		// assumes we are in the best position and should not move
		u32 destinationCell = _movable->getPosition();
		vector3df destinationPosition = _board->getPosition(destinationCell);
		E_DIRECTION direction = ED_NONE;

		// computes position of our target
		vector3df targetPosition = _board->getPosition(
			_target->getPosition());
		
		// computes initial value of metric for finding best position
		f32 minimalDistance = 
			destinationPosition.getDistanceFromSQ(targetPosition);
		if (sqrtf(minimalDistance) > _board->getMinimalDistance())
			minimalDistance = _board->getMaximalDistanceSquared();

		// checks: is better position exists
		// if exists then uses it
		array<E_DIRECTION> directions = getAvailableDirections();
		for (u32 i = 0; i < directions.size(); ++i) {
			
			u32 destinationCell = _board->getDestinationCell(
				_movable->getPosition(), directions[i]);
			vector3df destinationPosition = 
				_board->getPosition(destinationCell);

			f32 distance = 
				destinationPosition.getDistanceFromSQ(targetPosition);

			if (distance < minimalDistance) {
				direction = directions[i];
				minimalDistance = distance;
			}
			
		}

		// adds current position to the list of used
		// to prevent up-down or left-right jittering when target 
		// is behind the obstacle
		_usedPositions.push_back(_movable->getPosition());

		// moves controlled entity
		_movable->move(direction);

	}
	return false;
}

array<E_DIRECTION> PursuingMovableController::getAvailableDirections()
{
	u32 targetPosition = _target->getPosition();

	if (_previousTargetPosition != targetPosition) {
		_usedPositions.clear();
		_previousTargetPosition = targetPosition;
	}

	u32 position = _movable->getPosition();
	array<E_DIRECTION> directions = _board->getAvailableDirections(position);

	for (u32 i = 0; i < directions.size(); ++i) {
		u32 destination = _board->getDestinationCell(position, directions[i]);
		if (_usedPositions.linear_search(destination) != -1) {
			directions.erase(i--, 1);
		}
	}

	return directions;
}