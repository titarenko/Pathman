#pragma once

#include "Movable.h"
#include "LevelConfig.h"
#include "Sound.h"

class Game;

/*!
	Represents main character (MC) entity.
*/
class MainCharacter : public Movable
{
public:
	/*!
		Constructs new main character.
		@param level Level instance.
		@param node MC's scene node.
		@param config Level's config.
	*/
	MainCharacter(Level* level, 
		irr::scene::IAnimatedMeshSceneNode* node,
		const LevelConfig& config);
	~MainCharacter(void);

	/*!
		Returns true if MC is visible to others (enemies, for example).
	*/
	bool isVisible() const;

	/*!
		Injures MC: if MC is visible, lives count will be decremented.
	*/
	void injure();

	/*!
		Obtains current value of lives counter.
	*/
	irr::u32 getLivesCount() const;
	/*!
		Obtains current value of counter of gathered coins.
	*/
	irr::u32 getCoinsCount() const;

protected:
	/*!
		Implementation of Movable.
	*/
	void OnPosition(irr::u32 position);

private:
	Game* _game;

	irr::u32 _coinsCount;
	irr::u32 _livesCount;

	irr::u32 _time;
	irr::u32 _invisibilityTime;

	Sound* _coinSound;
	Sound* _deathSound;
};