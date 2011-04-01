#include "MainCharacter.h"
#include "Game.h"
#include "Level.h"
#include "Board.h"

using namespace irr;
using namespace io;
using namespace scene;

MainCharacter::MainCharacter(Level* level, 
	IAnimatedMeshSceneNode* node, const LevelConfig& config)
	: Movable(level, node, config.MainCharacter.Position, 
		config.MainCharacter.Speed, config.SoundFilenames.Hit)
	, _game(level->getGame())
	, _livesCount(config.MainCharacter.LivesCount)
	, _invisibilityTime(config.MainCharacter.InvisibilityTime)
	, _coinsCount(0)
	, _time(level->getGame()->getDevice()->getTimer()->getTime())
{
	_coinSound = new Sound(level->getGame(), config.SoundFilenames.Coin);
	_deathSound = new Sound(level->getGame(), config.SoundFilenames.Death);
}

MainCharacter::~MainCharacter(void)
{
	delete _coinSound;
	delete _deathSound;
}

bool MainCharacter::isVisible() const
{
	return _game->getDevice()->getTimer()->getTime() - 
		_time > _invisibilityTime;
}

void MainCharacter::injure()
{
	if (isVisible()) {
		--_livesCount;
		_deathSound->play();
		_time = _game->getDevice()->getTimer()->getTime();
		_level->refreshStatistics();
	}
}

u32 MainCharacter::getLivesCount() const
{
	return _livesCount;
}

u32 MainCharacter::getCoinsCount() const
{
	return _coinsCount;
}

void MainCharacter::OnPosition(u32 position)
{
	bool result = _level->getBoard()->collectCoin(position);
	if (result) {
		++_coinsCount;
		_coinSound->play(false);
		_level->refreshStatistics();
	}
}