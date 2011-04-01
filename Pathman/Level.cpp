#include "Level.h"
#include "Hud.h"
#include "Board.h"
#include "MainCharacter.h"
#include "Enemy.h"
#include "CameraController.h"
#include "ManualMovableController.h"
#include "RandomMovableController.h"
#include "PursuingMovableController.h"
#include "WalkingMovableController.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;
using namespace gui;
using namespace scene;

Level::Level(Game* game, const StageInfo& stage)
	: Stage(game, stage, "level")
	, _config(LevelConfig(_game, stage.ConfigFilename))
	, _paused(false)
{
	// camera
	createCamera();

	// skybox
	_game->getDevice()->getSceneManager()->addSkyBoxSceneNode(
		_config.Environment.Top, _config.Environment.Bottom,
		_config.Environment.Left, _config.Environment.Right,
		_config.Environment.Front, _config.Environment.Back, _rootNode);
	
	// entities
	createBoard();
	createMainCharacter();
	createEnemies();

	// hud
	_hud = new Hud(this, stage.ConfigFilename);
}

Level::~Level(void)
{
	delete _hud;

	removeControllers();	
	removeCamera();
	removeBoard();
	removeMainCharacter();
	removeEnemies();
}

Game* Level::getGame() const
{
	return _game;
}

Board* Level::getBoard() const
{
	return _board;
}

MainCharacter* Level::getMainCharacter() const
{
	return _mainCharacter;
}

void Level::refreshStatistics()
{
	if (!_board->getCoinsCount())
		deactivate(EGE_LEVEL_SUCCEEDED);

	u32 lives = _mainCharacter->getLivesCount();
	if (!lives)
		deactivate(EGE_LEVEL_FAILED);

	_hud->setLivesCount(lives);
	_hud->setCoinsCount(_mainCharacter->getCoinsCount());
}

bool Level::OnEvent(const SEvent& event)
{
	if (_state == ES_ACTIVE && 
		event.EventType == EET_KEY_INPUT_EVENT && 
		event.KeyInput.PressedDown) {

		if (event.KeyInput.Key == _config.AbortKey) {
			deactivate(EGE_LEVEL_ABORTED);
			return true;
		}
		else if (event.KeyInput.Key == _config.PauseKey) {
			togglePaused();
			return true;
		}

	}

	if (Game::ToGameEvent(event) == EGE_LEVEL_REQUESTED) {
		removeCamera();
		removeBoard();
		removeMainCharacter();
		removeEnemies();
	
		removeControllers();
		
		createCamera();
		createBoard();
		createMainCharacter();
		createEnemies();

		_paused = false;
	}

	if (_state == ES_FADING_IN) {
		for (u32 i = 0; i < _controllers.size(); ++i)
			_controllers[i]->refresh();		
		_hud->activate();
		refreshStatistics();
	}

	if (_state == ES_FADING_OUT)
		_hud->deactivate();

	if (_state == ES_ACTIVE) {
		if (_hud->OnEvent(event))
			return true;
		for (u32 i = 0; i < _controllers.size(); ++i)
			if (_controllers[i]->OnEvent(event))
				return true;
	}

	return Stage::OnEvent(event);
}

void Level::togglePaused()
{
	_hud->showPauseIndicator(_paused = !_paused);
}

void Level::update()
{
	if (_paused)
		return;

	_mainCharacter->getNode()->getMaterial(0).MaterialType = 
		_mainCharacter->isVisible() ? EMT_SOLID : EMT_TRANSPARENT_VERTEX_ALPHA;
	
	_mainCharacter->update();
	for (u32 i = 0; i < _enemies.size(); ++i)
		_enemies[i]->update();
}

IAnimatedMeshSceneNode* Level::createNode(
	const LevelConfig::Model& model, u32 position)
{
	IAnimatedMeshSceneNode* node = _game->getDevice()->getSceneManager(
		)->addAnimatedMeshSceneNode(model.Mesh, _rootNode, 
		-1, _board->getPosition(position));
	node->setAnimationSpeed(model.AnimationSpeed);
	return node;
}

MovableController* Level::createController(
	const LevelConfig::MovableController& config)
{
	switch (config.Type) {

	case EMCT_MANUAL:
		return (MovableController*) new ManualMovableController(
			_config.Controls);

	case EMCT_PURSUING:
		return (MovableController*) new PursuingMovableController(
			_board, _mainCharacter);

	case EMCT_RANDOM:
		return (MovableController*) new RandomMovableController(
			_board, config.Parameter.TurnProbability);

	case EMCT_WALKING:
		return (MovableController*) new WalkingMovableController(
			_config.WaypointsSets[config.Parameter.WaypointsSetId]);

	default:
		throw NotImplementedException();

	}
}

void Level::createCamera()
{
	_camera = _game->getDevice()->getSceneManager(
		)->addCameraSceneNode(_rootNode, 
		vector3df(1), vector3df(), -1, false);

	_camera->setFOV(_config.Camera.Fov);

	_camera->setNearValue(_config.Camera.Near);
	_camera->setFarValue(_config.Camera.Far);

	_controllers.push_back((IController*) new CameraController(
		_game, _camera, _stageInfo.ConfigFilename));
}

void Level::createBoard()
{
	_board = new Board(this, _config);
	_board->getRootNode()->setParent(_rootNode);
}

void Level::createMainCharacter()
{
	_mainCharacter = new MainCharacter(this, createNode(
		_config.Models.MainCharacter, _config.MainCharacter.Position), 
		_config);

	MovableController* controller = createController(
		_config.MovableControllers[_config.MainCharacter.ControllerId]);
	controller->setMovable(_mainCharacter);

	_controllers.push_back(controller);
}

void Level::createEnemies()
{
	for (u32 i = 0; i < _config.Enemies.size(); ++i) {
		LevelConfig::Enemy& enemy = _config.Enemies[i];

		Enemy* enemyEntity = new Enemy(this, createNode(
			_config.Models.Enemy, enemy.Position), _config, i);

		_enemies.push_back(enemyEntity);

		MovableController* controller = createController(
			_config.MovableControllers[enemy.ControllerId]);
		controller->setMovable(enemyEntity);

		_controllers.push_back(controller);
	}
}

void Level::removeControllers()
{
	for (u32 i = 0; i < _controllers.size(); ++i)
		delete _controllers[i];
	_controllers.clear();
}

void Level::removeCamera()
{
	_camera->remove();
}

void Level::removeBoard()
{
	delete _board;
}

void Level::removeMainCharacter()
{
	delete _mainCharacter;
}

void Level::removeEnemies()
{
	for (u32 i = 0; i < _enemies.size(); ++i)
		delete _enemies[i];
	_enemies.clear();
}