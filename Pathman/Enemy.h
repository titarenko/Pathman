#pragma once

#include "Movable.h"
#include "LevelConfig.h"

/*!
	Represents enemy entity.
*/
class Enemy : public Movable
{
public:
	/*!
		Constructs new enemy within level.
		@param level Level instance.
		@param node Enemy's scene node.
		@param config Level's config.
		@param index Enemy index (from 0 to count - 1).
	*/
	Enemy(Level* level, 
		irr::scene::IAnimatedMeshSceneNode* node, 
		const LevelConfig& config, irr::u32 index);
	~Enemy(void);

	/*!
		Implementation of Movable.
	*/
	void update();

protected:
	/*!
		Implementation of Movable.
	*/
	void OnPosition(irr::u32 position);
};