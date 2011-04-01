#pragma once

#include "Config.h"
#include "EStageType.h"
#include "EGameEvent.h"

class Game;

class StageConfig : Config
{
public:
	StageConfig(Game* game, const irr::io::path& filename,
		const irr::core::stringw& nodeName);
	~StageConfig(void);

	/*!
		When any of these events is happened 
		stage should be started (activated).
	*/
	irr::core::array<E_GAME_EVENT> ActivationEvents;

	/*!
		Event that should be broadcasted when stage 
		has been deactivated (finished).
	*/
	E_GAME_EVENT DefaultDeactivationEvent;

	irr::video::ITexture* BackgroundTexture;
	irr::u32 FadeTime;

	irr::io::path BackgroundSoundFilename;
	bool LoopBackgroundSound;

private:
	irr::core::stringw _nodeName;

	/*!
		Implementation of Config.
	*/
	void OnNode(const irr::core::stringw& name);
};