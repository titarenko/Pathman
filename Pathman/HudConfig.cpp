#include "HudConfig.h"

using namespace irr;
using namespace io;
using namespace core;
using namespace gui;
using namespace video;

HudConfig::HudConfig(Game* game, const path& filename)
	: Config(game, filename)
{
	while (next());
}

HudConfig::~HudConfig(void)
{
}

void HudConfig::OnNode(const stringw& name)
{
	if (name == "coinsCountLabel") {

		readLabel(CoinsCountLabel);

	} else if (name == "livesCountLabel") {

		readLabel(LivesCountLabel);

	} else if (name == "pauseIndicatorLabel") {

		readLabel(PauseIndicatorLabel);

	} else if (name == "minimap") {

		Minimap.Opacity = read<f32>("opacity");

		Minimap.X = read<s32>("x");
		Minimap.Y = read<s32>("y");

		Minimap.Width = read<u32>("width");
		Minimap.Height = read<u32>("height");

		Minimap.RTTWidth = read<u32>("rttWidth");
		Minimap.RTTHeight = read<u32>("rttHeight");

	}
}

void HudConfig::readLabel(HudConfig::Label& label)
{
	label.Prefix = read<stringw>("prefix");

	label.X = read<s32>("x");
	label.Y = read<s32>("y");

	label.Width = read<u32>("width");
	label.Height = read<u32>("height");

	label.Font = read<IGUIFont*>("font");
	label.FontColor = read<SColor>("fontColor");
}