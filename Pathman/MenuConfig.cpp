#include "MenuConfig.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;
using namespace gui;

MenuConfig::MenuConfig(Game* game, const path& filename)
	: Config(game, filename)
{
	while (next());
}

MenuConfig::~MenuConfig(void)
{
}

void MenuConfig::OnNode(const stringw& name)
{
	if (name == "menu") {

		ColumnsCount = read<u32>("columnsCount");

		Margin = read<u32>("margin");

		ButtonSize.Width = read<u32>("buttonWidth");
		ButtonSize.Height = read<u32>("buttonHeight");

		ButtonTextures.Default = read<ITexture*>("defaultButtonTexture");
		ButtonTextures.Active = read<ITexture*>("activeButtonTexture");
		ButtonTextures.Clicked = read<ITexture*>("clickedButtonTexture");

		Font = read<IGUIFont*>("font");
		FontColor = read<SColor>("fontColor");

	} else if (name == "button") {

		MenuConfig::Button button;

		button.Event = (E_GAME_EVENT) read<u32>("event");
		button.Text = read<stringw>("text");

		Buttons.push_back(button);

	} else if (name == "buttons") {

		SoundFilenames.Click = read<path>("clickSound");
		SoundFilenames.Select = read<path>("selectSound");

	}
}