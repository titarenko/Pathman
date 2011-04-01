#pragma once

#include <irrlicht.h>
#include "LevelConfig.h"

class Game;
class Level;

/*!
	Represents board: a set of cells (wall elements), obstacles and coins.
*/
class Board
{
public:
	/*!
		Constructs board entity.
		@param level Level instance.
		@param config Level's config.
	*/
	Board(Level* level, const LevelConfig& config);
	~Board(void);

	/*!
		Returns parent scene node for all board's elements.
	*/
	irr::scene::ISceneNode* getRootNode() const;

	/*!
		Returns true if requested movement is possible for any movable.
		@param position Index of source cell.
		@param direction Desired direction.
	*/
	bool canMove(irr::u32 position, E_DIRECTION direction) const;

	/*!
		Returns destination cell for requested movement or invalid value.
		"Invalid value" means illegal index (greater or equal to cells count).
		@param position Index of source cell.
		@param direction Desired direction.
	*/
	irr::u32 getDestinationCell(
		irr::u32 position, E_DIRECTION direction) const;

	/*!
		Returns "physical" position of center of the cell.
		@param cell Index of the cell to obtain position for.
	*/
	irr::core::vector3df getPosition(irr::u32 cell);

	/*!
		Collects coin (if possible): removes it from scene and return true.
		@param cell Cell's index to find and collect coin from.
	*/
	bool collectCoin(irr::u32 cell);

	/*!
		Returns number of coins left.
	*/
	irr::u32 getCoinsCount() const;

	/*!
		Returns full width (all cells) of board in world's units.
	*/
	irr::f32 getWidth() const;

	/*!
		Returns full height (all cells) of board in world's units.
	*/
	irr::f32 getHeight() const;

	/*!
		Returns minimal distance between cells' centers.
	*/
	irr::f32 getMinimalDistance() const;

	/*!
		Obtains maximal distance between cell's centers (squared).
	*/
	irr::f32 getMaximalDistanceSquared() const;

	/*!
		Obtains array of available directions for given position.
		@param position Index of source cell.
	*/
	irr::core::array<E_DIRECTION> getAvailableDirections(
		irr::u32 position) const;

private:
	Game* _game;

	irr::u32 _width;
	irr::u32 _height;

	irr::f32 _minimalDistance;
	irr::f32 _maximalDistanceSquared;

	irr::scene::ISceneNode* _rootNode;	
	irr::core::array<irr::core::rectf> _cells;
	irr::core::array<irr::u32> _obstacles;
	irr::core::array<irr::u32> _coins;
	irr::core::array<irr::scene::ISceneNode*> _coinNodes;

	/*!
		Helper for adding cell's content.
	*/
	irr::scene::IAnimatedMeshSceneNode* addCellContent(irr::u32 cell, 
		irr::scene::IAnimatedMesh* mesh, irr::f32 yOffset = 0);
};