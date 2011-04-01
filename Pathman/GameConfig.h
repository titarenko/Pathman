#pragma once

#include "Config.h"
#include "StageInfo.h"

class Game;

class GameConfig : Config
{
public:
	/*!
		Reads settings from provided file.
		@param game Game instance.
		@param filename Path to file with settings.
	*/
	GameConfig(Game* game, const char* filename);

	/*!
		Screen config.
	*/
	struct 
	{
		irr::video::E_DRIVER_TYPE DriverType;
		irr::u32 Width;
		irr::u32 Height;
		irr::u32 Bpp;
		bool Windowed;
		irr::core::stringw Caption;
	} Screen;

	struct
	{
		/*!
			Determines how long game will do nothing after each frame.
			Influences maximal FPS (FPS <= 1/Sleep).
		*/
		irr::u32 Sleep;
	} Performance;

	/*!
		Info about each stage of the game.
	*/
	irr::core::array<StageInfo> Stages;

private:
	/*!
		Implementation of Config.
	*/
	void OnNode(const irr::core::stringw& name);
};