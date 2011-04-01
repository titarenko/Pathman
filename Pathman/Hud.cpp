#include "Hud.h"
#include "Game.h"
#include "Level.h"
#include "Board.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace gui;
using namespace video;
using namespace scene;

static const f32 MIN_OPACITY = 0.01f;

Hud::Hud(Level* level, const path& configFilename)
	: _game(level->getGame())
	, _config(_game, configFilename)
	, _pauseIndicated(false)
{
	createLabel(&_livesCountLabel, _config.LivesCountLabel);
	createLabel(&_coinsCountLabel, _config.CoinsCountLabel);
	createLabel(&_pauseIndicatorLabel, _config.PauseIndicatorLabel);

	_minimap = _game->getDevice()->getGUIEnvironment(
		)->addImage(rect<s32>(
			position2d<s32>(_config.Minimap.X, _config.Minimap.Y),
			dimension2d<s32>(_config.Minimap.Width, _config.Minimap.Height)));
	_minimap->setColor(SColorf(1, 1, 1, _config.Minimap.Opacity).toSColor());

	if (_showMinimap = _game->getDevice()->getVideoDriver(
		)->queryFeature(EVDF_RENDER_TO_TARGET) && 
		_config.Minimap.Opacity >= MIN_OPACITY) {
		
		_minimapTexture = _game->getDevice()->getVideoDriver(
			)->addRenderTargetTexture(dimension2d<u32>(
					_config.Minimap.RTTWidth, 
					_config.Minimap.RTTHeight));
		
		_minimapCamera = _game->getDevice()->getSceneManager(
			)->addCameraSceneNode(NULL, vector3df(0, 5000, 0), 
			vector3df(), -1, false);

		matrix4 matrix;
		matrix.buildProjectionMatrixOrthoLH(
			level->getBoard()->getWidth(), 
			level->getBoard()->getHeight(), -20000, 20000);
		_minimapCamera->setProjectionMatrix(matrix, true);
		_minimapCamera->setUpVector(vector3df(-1, 0, 0));

		_minimap->setImage(_minimapTexture);
		_minimap->setScaleImage(true);
	}

	show(false);
}

Hud::~Hud(void)
{
	if (_showMinimap)
		_minimapCamera->remove();
}

void Hud::activate()
{
	_previousCamera = _game->getDevice(
		)->getSceneManager()->getActiveCamera();
	_game->enableAdditionalRender(_showMinimap);
	show(true);
}

void Hud::deactivate()
{
	_game->enableAdditionalRender(false);
	show(false);
}

void Hud::show(bool show)
{
	_livesCountLabel->setVisible(show);
	_coinsCountLabel->setVisible(show);
	_pauseIndicatorLabel->setVisible(show && _pauseIndicated);
	_minimap->setVisible(show && _showMinimap);
}

void Hud::setLivesCount(u32 count)
{
	_livesCountLabel->setText(
		(_config.LivesCountLabel.Prefix + stringw(count)).c_str());
}

void Hud::setCoinsCount(u32 count)
{
	_coinsCountLabel->setText(
		(_config.CoinsCountLabel.Prefix + stringw(count)).c_str());
}

void Hud::showPauseIndicator(bool show)
{
	_pauseIndicatorLabel->setVisible((_pauseIndicated = show) &&
		_livesCountLabel->isVisible());
}

bool Hud::OnEvent(const SEvent& event)
{
	if (!_showMinimap)
		return false;

	ISceneManager* scene;
	IVideoDriver* video;

	switch (Game::ToGameEvent(event)) {
	
	case EGE_ADDITIONAL_RENDER_STARTING:
		scene = _game->getDevice()->getSceneManager();
		video = _game->getDevice()->getVideoDriver();

		_previousCamera = scene->getActiveCamera();
		scene->setActiveCamera(_minimapCamera);
		video->setRenderTarget(_minimapTexture);

		show(false);
		break;

	case EGE_ADDITIONAL_RENDER_FINISHED:
		scene = _game->getDevice()->getSceneManager();
		video = _game->getDevice()->getVideoDriver();

		scene->setActiveCamera(_previousCamera);
		video->setRenderTarget(NULL);

		show(true);
		break;

	}

	return false;
}

void Hud::createLabel(IGUIStaticText** label, const HudConfig::Label& config)
{
	*label = _game->getDevice()->getGUIEnvironment()->addStaticText(
		config.Prefix.c_str(), rect<s32>(vector2d<s32>(config.X, config.Y),
		dimension2du(config.Width, config.Height)), false, false);

	IGUIStaticText& text = **label;

	text.setOverrideFont(config.Font);
	text.setOverrideColor(config.FontColor);
	text.setTextAlignment(EGUIA_UPPERLEFT, EGUIA_CENTER);
	text.setVisible(false);
}