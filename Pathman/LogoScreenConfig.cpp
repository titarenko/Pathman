#include "LogoScreenConfig.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;

LogoScreenConfig::LogoScreenConfig(Game* game, const path& filename)
	: Config(game, filename)
{
	while (next());
}

LogoScreenConfig::~LogoScreenConfig(void)
{
}

void LogoScreenConfig::OnNode(const stringw& name)
{
	if (name == "logoScreen") {

		LogoTexture = read<ITexture*>("logoTexture");
		Duration = read<u32>("duration");
		ScaleTime = read<u32>("scaleTime");
		
	}
}