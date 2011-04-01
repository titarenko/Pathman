#include "Enemy.h"
#include "Level.h"
#include "Board.h"
#include "MainCharacter.h"

using namespace irr;
using namespace core;
using namespace scene;

Enemy::Enemy(Level* level, IAnimatedMeshSceneNode* node, 
	const LevelConfig& config, u32 index)
	: Movable(level, node, config.Enemies[index].Position, 
		config.Enemies[index].Speed, config.SoundFilenames.Hit)
{
}

Enemy::~Enemy(void)
{
}

void Enemy::update()
{
	MainCharacter* character = _level->getMainCharacter();
	Board* board = _level->getBoard();

	vector3df characterPosition = board->getPosition(
		character->getPosition());
	vector3df enemyPosition = board->getPosition(getPosition());

	if (characterPosition.getDistanceFrom(
		enemyPosition) < board->getMinimalDistance())
		character->injure();

	Movable::update();
}

void Enemy::OnPosition(u32 position)
{
}