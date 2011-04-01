#include "GameConfig.h"
#include "Game.h"
#include "XmlReader.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;

GameConfig::GameConfig(Game* game, const char* filename)
	: Config(game, new XmlReader(filename))
{
	while (next());
}

void GameConfig::OnNode(const stringw& name)
{
	if (name == "screen") {

		Screen.DriverType = (E_DRIVER_TYPE) read<u32>("driverType");

		Screen.Width = read<u32>("width");
		Screen.Height = read<u32>("height");
		Screen.Bpp = read<u32>("bpp");

		Screen.Windowed = read<bool>("windowed");
		Screen.Caption = read<stringw>("caption");

		_game->createDevice(*this);

	} else if (name == "performance") {

		Performance.Sleep = read<u32>("sleep");

	} else if (name == "assets") {

		_game->addAssets(read<path>("path"));

	} else if (name == "stage") {

		StageInfo stage;

		stage.Type = (E_STAGE_TYPE) read<u32>("type");
		stage.ConfigFilename = read<path>("configFilename");

		Stages.push_back(stage);
	}
}