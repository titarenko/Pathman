#include "Game.h"
#include "GameConfig.h"
#include "InitializationException.h"
#include "NotImplementedException.h"
#include "LogoScreen.h"
#include "Menu.h"
#include "Level.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;
using namespace gui;
using namespace scene;

Game::Game(const char* configFilename)
	: _device(NULL)
	, _additionalRender(false)
{
	// reads config and forces game instance to create device
	GameConfig config(this, configFilename);
	_sleepValue = config.Performance.Sleep;

	// creates stages
	_stages.reallocate(config.Stages.size());
	for (int i = 0; i < (int) config.Stages.size(); ++i)
		_stages.push_back(createStage(config.Stages[i]));

	broadcastEvent(EGE_APPLICATION_STARTED);
}

Game::~Game(void)
{
	for (u32 i = 0; i < _stages.size(); ++i)
		delete _stages[i];
	_soundEngine->drop();
	_device->drop();
}

bool Game::OnEvent(const SEvent& event)
{
	// processes important events out of turn
	switch (ToGameEvent(event)) {

	case EGE_SOUND_ALLOWED:
		enableSound(_soundAllowed = true);
		break;

	case EGE_SOUND_PROHIBITED:
		enableSound(_soundAllowed = false);
		break;

	case EGE_EXIT_REQUESTED:
		broadcastEvent(EGE_APPLICATION_FINISHED);
		break;

	case EGE_APPLICATION_FINISHED:
		_device->closeDevice();
		break;

	}

	// lets each stage to process current event
	for (u32 i = 0; i < _stages.size(); ++i)
		if (_stages[i]->OnEvent(event))
			return true;

	return false;
}

void Game::createDevice(const GameConfig& config)
{
	// creates Irrlicht's device
	if (!_device)
		_device = ::createDevice(
		config.Screen.DriverType,
		dimension2d<u32>(config.Screen.Width, config.Screen.Height),
		config.Screen.Bpp,
		!config.Screen.Windowed,
		false,
		false,
		this);
	if (!_device)
		throw InitializationException("_device");

	// common settings
	_device->setWindowCaption(config.Screen.Caption.c_str());
	_device->getSceneManager()->setAmbientLight(SColorf(SColor(0xFFFFFFFF)));

	// creates IrrKlang's sound engine
	_soundEngine = irrklang::createIrrKlangDevice();
	if (!_soundEngine)
		throw InitializationException("_soundEngine");
}

IrrlichtDevice* Game::getDevice() const 
{
	return _device;
}

irrklang::ISoundEngine* Game::getSoundEngine() const
{
	return _soundEngine;
}

void Game::addAssets(const path& path)
{
	_device->getFileSystem()->addFileArchive(
		path, true, true, EFAT_UNKNOWN, "VidIvDiefboiljIlcofs");
}

void Game::broadcastEvent(E_GAME_EVENT event)
{
	SEvent userEvent;

	userEvent.EventType = EET_USER_EVENT;
	userEvent.UserEvent.UserData1 = event;

	OnEvent(userEvent);
}

bool Game::update()
{
	bool result = _device->run();
	if (result) {
		if (_device->isWindowActive()) {
			enableSound(true);

			IVideoDriver* video = _device->getVideoDriver();
			IGUIEnvironment* gui = _device->getGUIEnvironment();
			ISceneManager* scene = _device->getSceneManager();

			video->beginScene();

			if (_additionalRender) {
				broadcastEvent(EGE_ADDITIONAL_RENDER_STARTING);
				scene->drawAll();
				gui->drawAll();
				broadcastEvent(EGE_ADDITIONAL_RENDER_FINISHED);
			}
			
			scene->drawAll();
			gui->drawAll();

			// prepares next frame while current is
			// being rendered by the GPU
			broadcastEvent(EGE_FRAME_ENDED);

			video->endScene();
			
			// prevents excessive CPU usage
			// (do we need 1000 FPS? I don't think so,
			// as for me, 60 is enough)
			if (_sleepValue)
				_device->sleep(_sleepValue);
		} 
		// prevents CPU usage if window is not active 
		// (user switched to another one and is not playing)
		else {
			enableSound(false);
			_device->yield();
		}
	}
	return result;
}

E_GAME_EVENT Game::ToGameEvent(const SEvent& event)
{
	return event.EventType == EET_USER_EVENT
		? (E_GAME_EVENT) event.UserEvent.UserData1
		: EGE_NULL;
}

void Game::enableAdditionalRender(bool enable)
{
	_additionalRender = enable;
}

void Game::enableSound(bool enable)
{
	if (!_soundAllowed && enable)
		return;

	if (_soundEnabled != enable)
		_soundEngine->setSoundVolume(_soundEnabled = enable ? 1 : 0);
}

IEventReceiver* Game::createStage(const StageInfo& stage)
{
	switch (stage.Type) {

	case EST_LOGO:
		return (IEventReceiver*) new LogoScreen(this, stage);

	case EST_MENU:
		return (IEventReceiver*) new Menu(this, stage);

	case EST_LEVEL:
		return (IEventReceiver*) new Level(this, stage);

	default:
		throw NotImplementedException();

	}
}