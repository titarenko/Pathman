#include "RandomMovableController.h"
#include "Game.h"
#include "Board.h"
#include "Movable.h"
#include "Random.h"

using namespace irr;
using namespace core;

RandomMovableController::RandomMovableController(Board* board, 
	f32 turnProbability, Movable* movable)
	: MovableController(movable)
	, _board(board)
	, _turnProbability(turnProbability)
{
	Random::SetSeed();
}

RandomMovableController::~RandomMovableController(void)
{
}

void RandomMovableController::refresh()
{
}

bool RandomMovableController::OnEvent(const SEvent& event)
{
	if (Game::ToGameEvent(event) == EGE_FRAME_ENDED && 
		_movable->isStopped() &&
		Random::GetNumber() < _turnProbability) {

		array<E_DIRECTION> directions = 
			_board->getAvailableDirections(_movable->getPosition());

		_movable->move(directions[Random::GetNumber(directions.size())]);

	}
	return false;
}