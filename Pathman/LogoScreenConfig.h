#pragma once

#include "Config.h"

class Game;

class LogoScreenConfig : Config
{
public:
	LogoScreenConfig(Game* game, const irr::io::path& filename);
	~LogoScreenConfig(void);

	irr::video::ITexture* LogoTexture;
	irr::u32 Duration;
	irr::u32 ScaleTime;
	
private:
	/*!
		Implementation of Config.
	*/
	void OnNode(const irr::core::stringw& name);
};