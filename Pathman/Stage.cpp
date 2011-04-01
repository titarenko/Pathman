#include "Stage.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

Stage::Stage(Game* game, const StageInfo& stage, const stringw& nodeName)
	: _game(game)
	, _stageInfo(stage)
	, _stageConfig(game, stage.ConfigFilename, nodeName)
	, _state(ES_INACTIVE)
{
	_deactivationEvent = _stageConfig.DefaultDeactivationEvent;

	_rootNode = _game->getDevice()->getSceneManager()->addEmptySceneNode();
	_rootNode->setVisible(false);

	_fader = _game->getDevice()->getGUIEnvironment()->addInOutFader();
	_fader->setVisible(false);

	_backgroundSound = new Sound(_game,
		_stageConfig.BackgroundSoundFilename, 
		_stageConfig.LoopBackgroundSound);
}

Stage::~Stage(void)
{
	delete _backgroundSound;
}

bool Stage::OnEvent(const SEvent& event)
{
	E_GAME_EVENT gameEvent = Game::ToGameEvent(event);

	switch (_state) {

	case ES_INACTIVE:
		if (isActivationEvent(gameEvent)) {
			_game->getDevice()->getSceneManager()->setActiveCamera(_camera);
			_game->getDevice()->getCursorControl()->setVisible(false);

			_rootNode->setVisible(true);
			_fader->setVisible(true);

			_state = ES_FADING_IN;
			_fader->fadeIn(_stageConfig.FadeTime);
		}
		break;

	case ES_FADING_IN:
		if (_fader->isReady()) {
			_state = ES_ACTIVE;
			_backgroundSound->play();
		}
		break;

	case ES_ACTIVE:
		if (gameEvent == EGE_FRAME_ENDED)
			update();
		break;

	case ES_FADING_OUT:
		if (_fader->isReady()) {
			_state = ES_INACTIVE;
			_backgroundSound->stop();

			_rootNode->setVisible(false);
			_fader->setVisible(false);
			
			_game->broadcastEvent(_deactivationEvent);
		}
		break;

	}

	return false;
}

void Stage::deactivate()
{
	deactivate(_stageConfig.DefaultDeactivationEvent);
}

void Stage::deactivate(E_GAME_EVENT deactivationEvent)
{
	_deactivationEvent = deactivationEvent;
	_state = ES_FADING_OUT;
	_fader->fadeOut(_stageConfig.FadeTime);
}

void Stage::createOrthoCamera()
{
	dimension2d<u32> screenSize = _game->getDevice(
		)->getVideoDriver()->getScreenSize();

	matrix4 matrix;
	matrix.buildProjectionMatrixOrthoLH(
		(f32) screenSize.Width, (f32) screenSize.Height, -1000, 1000);

	_camera = _game->getDevice()->getSceneManager()->addCameraSceneNode(
		NULL, vector3df(0, 1000, 0), vector3df(), -1, false);
	_camera->setProjectionMatrix(matrix, true);
	_camera->setUpVector(vector3df(0, 0, 1));
}

void Stage::createBackground()
{
	dimension2d<u32> screenSize = _game->getDevice(
		)->getVideoDriver()->getScreenSize();
	dimension2d<f32> screenSizeF32 = dimension2d<f32>( 
		(f32) screenSize.Width, (f32) screenSize.Height);

	ISceneManager* scene = _game->getDevice()->getSceneManager();
	const IGeometryCreator* geometry = scene->getGeometryCreator();

	SMaterial material;
	material.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;

	dimension2d<u32> textureSize = _stageConfig.BackgroundTexture->getSize();
	dimension2d<f32> textureRepeats = dimension2d<f32>(
		screenSizeF32.Width/textureSize.Width, 
		screenSizeF32.Height/textureSize.Height);

	material.setTexture(0, _stageConfig.BackgroundTexture); 
	scene->addMeshSceneNode(geometry->createPlaneMesh(
		screenSizeF32, dimension2d<u32>(1, 1), &material, textureRepeats),
		_rootNode);
}

bool Stage::isActivationEvent(E_GAME_EVENT event)
{
	return _stageConfig.ActivationEvents.binary_search(event) != -1;
}