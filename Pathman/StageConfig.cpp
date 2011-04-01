#include "StageConfig.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;

StageConfig::StageConfig(Game* game, const path& filename, 
	const stringw& nodeName)
	: Config(game, filename)
	, _nodeName(nodeName)
{
	while (next());
}

StageConfig::~StageConfig(void)
{
}

void StageConfig::OnNode(const stringw& name)
{
	if (name == _nodeName) {

		BackgroundTexture = read<ITexture*>("backgroundTexture");
		FadeTime = read<u32>("fadeTime");

		DefaultDeactivationEvent = 
			(E_GAME_EVENT) read<u32>("defaultDeactivationEvent");

		BackgroundSoundFilename = read<path>("backgroundSound");
		LoopBackgroundSound = read<bool>("loopBackgroundSound");

	} else if (name == "activationEvent") {

		ActivationEvents.push_back((E_GAME_EVENT) read<u32>("value"));

	}
}