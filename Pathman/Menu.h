#pragma once

#include "Stage.h"
#include "MenuConfig.h"
#include "Sound.h"

/*!
	Represents menu as a set of buttons.
*/
class Menu : Stage
{
public:
	/*!
		Initializes menu using provided info.
		@param game Game instance.
		@param stage Contains path to config file.
	*/
	Menu(Game* game, const StageInfo& stage);
	~Menu(void);

	/*!
		Implementation of IEventReceiver.
	*/
	virtual bool OnEvent(const irr::SEvent& event);

private:
	MenuConfig _config;
	irr::core::array<irr::scene::ISceneNode*> _buttons;
	int _activeButtonIndex;
	Sound* _clickSound;
	Sound* _selectSound;

	/*!
		Translates mouse coordinates to index of button (if possible).
		Returns -1 if no button is under mouse cursor.
		@param x Mouse's horizontal coordinate.
		@param y Mouse's vertical coordinate.
	*/
	irr::s32 coordinatesToIndex(irr::s32 x, irr::s32 y);

	/*!
		Changes button appearance to active while 
		sets previous active button appearance to default 
		(if ignorePrevious is not false).
		@param index Button's index (from 0 to count - 1).
		@param ignorePrevious Don't touch previous active button.
	*/
	void activateButton(irr::s32 index, bool ignorePrevious = false);

	/*!
		Obatins button by mouse coordinates (if possible) and activates it.
		@param x Mouse's horizontal coordinate.
		@param y Mouse's vertical coordinate.
	*/
	void activateButton(irr::s32 x, irr::s32 y);

	/*!
		Changes button appearance and broadcasts button's event.
	*/
	void clickButton();

	/*!
		Obatins button by mouse coordinates (if possible) and clicks it.
		@param x Mouse's horizontal coordinate.
		@param y Mouse's vertical coordinate.
	*/
	void clickButton(irr::s32 x, irr::s32 y);

	/*!
		Implementation of Stage.
	*/
	void update();
};