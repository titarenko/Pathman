#include "Menu.h"
#include "EGameEvent.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;
using namespace gui;
using namespace scene;

/*!
	Helper struct that represents menu's button.
*/
struct Button
{
	/*!
		Constructs button as a plane node and text node with shared root node.
		@param game Game instance.
		@param config Configuration (texture, size, etc).
		@param index Index of the button (from 0 to count - 1).
	*/
	Button(Game* game, const MenuConfig& config, s32 index)
	{
		ISceneManager* scene = game->getDevice()->getSceneManager();
		Root = scene->addEmptySceneNode();

		scene->addTextSceneNode(
			config.Font,
			config.Buttons[index].Text.c_str(),
			config.FontColor,
			Root)->setPosition(vector3df(0, 10, 0));

		SMaterial material;

		material.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;
		material.setTexture(0, config.ButtonTextures.Default);

		Plane = scene->addMeshSceneNode(
			scene->getGeometryCreator()->createPlaneMesh(
				dimension2df(
					(f32) config.ButtonSize.Width, 
					(f32) config.ButtonSize.Height),
				dimension2du(1, 1), &material, dimension2df(1, 1)
			), Root);
	};

	ISceneNode* Root;
	ISceneNode* Plane;
};

/*!
	Helper struct that represents menu's column - a subset of menu buttons.
*/
struct Column
{
	/*!
		Constructs column as a set of buttons with shared root node.
		@param game Game instance.
		@param config Configuration (texture, size, etc).
		@param index Index of the column (from 0 to count - 1).
	*/
	Column(Game* game, const MenuConfig& config, s32 index)
	{
		u32 buttonsCount = config.Buttons.size()/config.ColumnsCount;

		f32 extent = config.ButtonSize.Height + config.Margin*2.0f;
		f32 offset = extent*(buttonsCount - 1)*0.5f;

		Root = game->getDevice()->getSceneManager(
			)->addEmptySceneNode();

		Buttons.reallocate(buttonsCount);
		for (u32 i = 0; i < buttonsCount; ++i) {

			Button button(game, config, index*buttonsCount + i);

			button.Root->setParent(Root);
			button.Root->setPosition(
				vector3df(0, 100, offset - extent*i));

			Buttons.push_back(button);
		}
	}

	ISceneNode* Root;
	array<Button> Buttons;
};

Menu::Menu(Game* game, const StageInfo& stage)
	: Stage(game, stage, "menu")
	, _config(game, stage.ConfigFilename)
{
	createOrthoCamera();
	createBackground();

	f32 extent = _config.ButtonSize.Width + _config.Margin*2.0f;
	f32 offset = (_config.ColumnsCount - 1)*extent*0.5f;

	for (u32 i = 0; i < _config.ColumnsCount; ++i) {

		Column column(_game, _config, i);

		column.Root->setParent(_rootNode);
		column.Root->setPosition(vector3df(extent*i - offset, 0, 0));

		for (u32 j = 0; j < column.Buttons.size(); ++j)
			_buttons.push_back(column.Buttons[j].Plane);
	}

	_clickSound = new Sound(game, _config.SoundFilenames.Click);
	_selectSound = new Sound(game, _config.SoundFilenames.Select);

	activateButton(0, true);
}

Menu::~Menu(void)
{
	delete _clickSound;
	delete _selectSound;
}

bool Menu::OnEvent(const SEvent& event)
{
	if (isActivationEvent(Game::ToGameEvent(event)))
		activateButton(0);

	if (_state == ES_ACTIVE && event.EventType == EET_KEY_INPUT_EVENT &&
		event.KeyInput.PressedDown)
		switch (event.KeyInput.Key) {

		case KEY_UP: 
		case KEY_LEFT:
			activateButton(_activeButtonIndex - 1);
			return true;

		case KEY_RIGHT:
		case KEY_DOWN:
			activateButton(_activeButtonIndex + 1);
			return true;

		case KEY_RETURN:
			clickButton();
			return true;

		}

	if (_state == ES_FADING_IN)
		_game->getDevice()->getCursorControl()->setVisible(true);

	if (_state == ES_ACTIVE && event.EventType == EET_MOUSE_INPUT_EVENT) {
		if (event.MouseInput.ButtonStates & 
				(EMIE_LMOUSE_PRESSED_DOWN | 
				EMIE_MMOUSE_PRESSED_DOWN | 
				EMIE_RMOUSE_PRESSED_DOWN))
			clickButton(event.MouseInput.X, event.MouseInput.Y);
		else
			activateButton(event.MouseInput.X, event.MouseInput.Y);
		return true;
	}

	return Stage::OnEvent(event);
}

s32 Menu::coordinatesToIndex(s32 x, s32 y)
{
	ISceneCollisionManager* collision = _game->getDevice(
		)->getSceneManager()->getSceneCollisionManager();

	ISceneNode* node = collision->getSceneNodeFromScreenCoordinatesBB(
		vector2d<s32>(x, y), 0, false, _rootNode);

	return _buttons.linear_search(node);
}

void Menu::activateButton(s32 index, bool ignorePrevious)
{
	if (!ignorePrevious && _activeButtonIndex != index)
		_selectSound->play();

	if (index < 0)
		index += _buttons.size();
	
	if (index >= (s32) _buttons.size())
		index -= _buttons.size();	

	if (!ignorePrevious)
		_buttons[_activeButtonIndex]->getMaterial(0).setTexture(0,
			_config.ButtonTextures.Default);

	_buttons[_activeButtonIndex = index]->getMaterial(
		0).setTexture(0, _config.ButtonTextures.Active);
}

void Menu::activateButton(s32 x, s32 y)
{
	s32 index = coordinatesToIndex(x, y);
	if (index != -1)
		activateButton(index);
}

void Menu::clickButton()
{
	_clickSound->play();

	_buttons[_activeButtonIndex]->getMaterial(0).setTexture(
		0, _config.ButtonTextures.Clicked);
	deactivate(_config.Buttons[_activeButtonIndex].Event);
}

void Menu::clickButton(s32 x, s32 y)
{
	s32 index = coordinatesToIndex(x, y);
	if (index != -1) {
		activateButton(index);
		clickButton();
	}
}

void Menu::update()
{
}