#include "Movable.h"
#include "Level.h"
#include "Board.h"

using namespace irr;
using namespace io;
using namespace core;
using namespace scene;

Movable::Movable(Level* level, IAnimatedMeshSceneNode* node, 
	u32 position, f32 speed, const path& hitSoundFilename)
	: _level(level)
	, _node(node)
	, _position(position)
	, _speed(speed)
	, _requestedDirection(ED_NONE)
	, _animator(0)
	, _hitSoundPlayed(false)
{
	_hitSound = new Sound(level->getGame(), hitSoundFilename);
}

Movable::~Movable(void)
{
	delete _hitSound;
	_node->remove();
}

void Movable::move(E_DIRECTION direction)
{
	_requestedDirection = direction;
}

void Movable::update()
{
	if (isStopped()) {
		OnPosition(_position);

		Board* board = _level->getBoard();
		if (board->canMove(_position, _requestedDirection)) {
			if (_animator = getAnimator()) {

				_node->removeAnimators();
				_node->addAnimator(_animator);
				_animator->drop();

				_node->setRotation(vector3df(
					0, getAngle(_requestedDirection), 0));

				_position = board->getDestinationCell(
					_position, _requestedDirection);

				_hitSoundPlayed = false;
			}
		}
		else if (!_hitSoundPlayed) {
			_hitSound->play();
			_hitSoundPlayed = true;
		}
	}
}

u32 Movable::getPosition() const
{
	return _position;
}

bool Movable::isStopped() const
{
	return !_animator || _animator->hasFinished();
}

IAnimatedMeshSceneNode* Movable::getNode() const
{
	return _node;
}

ISceneNodeAnimator* Movable::getAnimator()
{
	Board* board = _level->getBoard();
	Game* game = _level->getGame();

	return board->canMove(_position, _requestedDirection)
		? game->getDevice()->getSceneManager()->createFlyStraightAnimator(
			board->getPosition(_position), board->getPosition(
				board->getDestinationCell(_position, _requestedDirection)),
			(u32) (1000/_speed))
		: NULL;
}

f32 Movable::getAngle(E_DIRECTION direction)
{
	switch (direction) {

	case ED_UP:
		return 90;

	case ED_DOWN:
		return -90;

	case ED_LEFT:
	default:
		return 0;

	case ED_RIGHT:
		return 180;

	}
}