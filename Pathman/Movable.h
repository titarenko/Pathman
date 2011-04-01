#pragma once

#include <irrlicht.h>
#include "EDirection.h"
#include "Sound.h"

class Level;

/*!
	Represents movable entity.
*/
class Movable
{
public:
	/*!
		Creates new movable within level.
		@param level Level instance.
		@param node Movable's node (will be removed from scene on deletion).
		@param position Movable's cell index.
		@param speed Movable's speed in units per second.
		@param hitSoundFilename Path to sound file that will be played if
		movable entity was reached obstacle.
	*/
	Movable(Level* level, 
		irr::scene::IAnimatedMeshSceneNode* node, 
		irr::u32 position, irr::f32 speed, 
		const irr::io::path& hitSoundFilename);
	~Movable(void);

	/*!
		Moves entity (if possible) using provided direction.
	*/
	void move(E_DIRECTION direction);

	/*!
		Updates state of movable entity.
	*/
	virtual void update();

	/*!
		Obtains current position as index of board's cell.
	*/
	irr::u32 getPosition() const;

	/*!
		Returns true if movable is not moving.
	*/
	bool isStopped() const;

	/*!
		Obtains assiciated scene node.
	*/
	irr::scene::IAnimatedMeshSceneNode* getNode() const;

protected:
	Level* _level;

	/*!
		Called each time when movable has reached new position.
		That position (index of board's cell) is passed as argument.
		Should be implemented by descendants.
	*/
	virtual void OnPosition(irr::u32 position) = 0;

private:
	irr::scene::IAnimatedMeshSceneNode* _node;
	irr::scene::ISceneNodeAnimator* _animator;

	irr::u32 _position;
	irr::f32 _speed;

	E_DIRECTION _requestedDirection;
	
	Sound* _hitSound;
	bool _hitSoundPlayed;

	/*!
		Returns animator for scene node to perform movement.
	*/
	irr::scene::ISceneNodeAnimator* getAnimator();

	/*!
		Obtains angle (in degrees) for given direction.
	*/
	irr::f32 getAngle(E_DIRECTION direction);
};