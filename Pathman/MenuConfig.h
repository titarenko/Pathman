#pragma once

#include "Config.h"
#include "EGameEvent.h"

class Game;

class MenuConfig : Config
{
public:
	MenuConfig(Game* game, const irr::io::path& filename);
	~MenuConfig(void);

	irr::u32 ColumnsCount;

	/*!
		Distance in one dimension between adjacent elements.
	*/
	irr::u32 Margin;

	struct
	{
		irr::u32 Width;
		irr::u32 Height;
	} ButtonSize;

	struct 
	{
		irr::video::ITexture* Default;
		irr::video::ITexture* Active;
		irr::video::ITexture* Clicked;
	} ButtonTextures;

	struct Button
	{
		/*!
			Event that should be broadcasted when button is clicked.
		*/
		E_GAME_EVENT Event;
		irr::core::stringw Text;
	};

	irr::gui::IGUIFont* Font;
	irr::video::SColor FontColor;

	irr::core::array<Button> Buttons;

	struct
	{
		irr::io::path Click;
		irr::io::path Select;
	} SoundFilenames;
	
private:
	/*!
		Implementation of Config.
	*/
	void OnNode(const irr::core::stringw& name);
};