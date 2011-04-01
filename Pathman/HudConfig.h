#pragma once

#include "Config.h"

class Game;

class HudConfig : Config
{
public:
	HudConfig(Game* game, const irr::io::path& filename);
	~HudConfig(void);

	struct Label
	{
		irr::s32 X;
		irr::s32 Y;
		irr::u32 Width;
		irr::u32 Height;
		irr::core::stringw Prefix;
		irr::gui::IGUIFont* Font;
		irr::video::SColor FontColor;
	};

	Label CoinsCountLabel;
	Label LivesCountLabel;
	Label PauseIndicatorLabel;

	struct
	{
		irr::f32 Opacity;

		irr::u32 X;
		irr::u32 Y;
		irr::u32 Width;
		irr::u32 Height;

		/*!
			Render target texture width.
		*/
		irr::u32 RTTWidth;

		/*!
			Render target texture height.
		*/
		irr::u32 RTTHeight;
	} Minimap;

private:
	/*!
		Implementation of Config.
	*/
	void OnNode(const irr::core::stringw& name);

	void readLabel(Label& label);
};