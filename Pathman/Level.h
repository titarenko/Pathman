#pragma once

#include "Stage.h"
#include "LevelConfig.h"
#include "IController.h"

class Hud;
class Board;
class MainCharacter;
class Enemy;
class MovableController;

/*!
	Represents game level. This is actually "game itself":
	board, obstacels, coins, main character, environment etc.
*/
class Level : Stage
{
public:
	/*!
		Initializes level using provided info.
		@param game Game instance.
		@param stage Contains path to config file.
	*/
	Level(Game* game, const StageInfo& stage);
	~Level(void);

	Game* getGame() const;

	Board* getBoard() const;
	MainCharacter* getMainCharacter() const;

	/*!
		Refreshes HUD and checks win and loss conditions.
	*/
	void refreshStatistics();

	/*!
		Implementation of IEventReceiver.
	*/
	virtual bool OnEvent(const irr::SEvent& event);

private:
	LevelConfig _config;
	
	Hud* _hud;
	Board* _board;
	MainCharacter* _mainCharacter;
	irr::core::array<Enemy*> _enemies;

	irr::core::array<IController*> _controllers;
	
	bool _paused;

	/*!
		Pauses or resumes level.
	*/
	void togglePaused();

	/*!
		Implementation of Stage.
	*/
	void update();

	/*!
		Helper for creating scene nodes for characters.
	*/
	irr::scene::IAnimatedMeshSceneNode* createNode(
		const LevelConfig::Model& model, irr::u32 position);

	/*!
		Helper for creating controllers for characters.
	*/
	MovableController* createController(
		const LevelConfig::MovableController& config);	

	void createCamera();
	void createBoard();
	void createMainCharacter();
	void createEnemies();

	void removeControllers();

	void removeCamera();
	void removeBoard();
	void removeMainCharacter();
	void removeEnemies();
};