#include "Board.h"
#include "Level.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

Board::Board(Level* level, const LevelConfig& config)
	: _game(level->getGame())
	, _rootNode(level->getGame()->getDevice()->getSceneManager()->addEmptySceneNode())
	, _width(config.Board.Width)
	, _height(config.Board.Height)
	, _obstacles(config.Obstacles)
	, _coins(config.Coins)
{
	ISceneManager* scene = level->getGame()->getDevice()->getSceneManager();

	vector3df cellSize = config.Models.Floor.Mesh->getBoundingBox().getExtent();

	f32 width = cellSize.X, fullWidth = width*config.Board.Width, 
		xOffset = fullWidth*0.5f;
	f32 height = cellSize.Z, fullHeight = height*config.Board.Height,
		yOffset = fullHeight*0.5f;

	_minimalDistance = width < height ? width : height;
	_maximalDistanceSquared = fullWidth*fullWidth + fullHeight*fullHeight;

	_cells.reallocate(config.Board.Width*config.Board.Height);
	for (u32 i = 0; i < config.Board.Width; ++i)
		for (u32 j = 0; j < config.Board.Height; ++j) {
			f32 x = width*i - xOffset, y = height*j - yOffset;
			_cells.push_back(rectf(x, y, x + width, y + height));
		}

	for (u32 i = 0; i < _cells.size(); ++i) {
		addCellContent(i, config.Models.Floor.Mesh, -cellSize.Y);
	}

	for (u32 i = 0; i < config.Obstacles.size(); ++i) {
		addCellContent(config.Obstacles[i], config.Models.Obstacle.Mesh);
	}

	_coinNodes.reallocate(_coins.size());
	for (u32 i = 0; i < config.Coins.size(); ++i) {

		IAnimatedMeshSceneNode* node = addCellContent(
			config.Coins[i], config.Models.Coin.Mesh);

		ISceneNodeAnimator* animator = scene->createRotationAnimator(
			vector3df(0, config.CoinRotationSpeed, 0));

		node->setAnimationSpeed(config.Models.Coin.AnimationSpeed);
		node->addAnimator(animator);

		animator->drop();
		
		_coinNodes.push_back(node);
	}
}

Board::~Board(void)
{
	_rootNode->removeAll();
}

ISceneNode* Board::getRootNode() const
{
	return _rootNode;
}

bool Board::canMove(u32 position, E_DIRECTION direction) const
{
	u32 destination = getDestinationCell(position, direction);
	if (_obstacles.binary_search(destination) != -1)
		return false;
	return destination < _cells.size();
}

u32 Board::getDestinationCell(u32 position, E_DIRECTION direction) const
{
	u32 cell;

	switch (direction) {

	case ED_UP:
		return position - _width;

	case ED_DOWN:
		return position + _width;

	case ED_LEFT:
		cell = position % _width;
		// if position is not at left boundary or movement can't be performed
		return cell ? position - 1 : -1;

	case ED_RIGHT:
		// if position is not at right boundary or movement can't be performed
		cell = position % _width;
		return cell != _width - 1 ? position + 1 : -1;

	case ED_NONE:
		return position;

	default:
		return -1;

	}
}

vector3df Board::getPosition(u32 cell)
{
	vector2df center = _cells[cell].getCenter();
	return vector3df(center.X, 0, center.Y);
}

bool Board::collectCoin(u32 cell)
{
	s32 index = _coins.binary_search(cell);
	if (index != -1) {
		_coinNodes[index]->remove();
		_coinNodes.erase(index, 1);
		_coins.erase(index, 1);
		return true;
	}
	return false;
}

u32 Board::getCoinsCount() const
{
	return _coins.size();
}

f32 Board::getWidth() const
{
	return _cells[0].getWidth()*_width;
}

f32 Board::getHeight() const
{
	return _cells[0].getHeight()*_height;
}

f32 Board::getMinimalDistance() const
{
	return _minimalDistance;
}

f32 Board::getMaximalDistanceSquared() const
{
	return _maximalDistanceSquared;
}

array<E_DIRECTION> Board::getAvailableDirections(u32 position) const
{
	array<E_DIRECTION> result(4);

	if (canMove(position, ED_UP))
		result.push_back(ED_UP);
	if (canMove(position, ED_DOWN))
		result.push_back(ED_DOWN);

	if (canMove(position, ED_LEFT))
		result.push_back(ED_LEFT);
	if (canMove(position, ED_RIGHT))
		result.push_back(ED_RIGHT);

	return result;
}

IAnimatedMeshSceneNode* Board::addCellContent(u32 cell, IAnimatedMesh* mesh, f32 yOffset)
{
	vector2df center = _cells[cell].getCenter();
	return _game->getDevice()->getSceneManager(
		)->addAnimatedMeshSceneNode(mesh, _rootNode, -1, 
		vector3df(center.X, yOffset, center.Y));
}