#pragma once

#include "HudConfig.h"

class Game;
class Level;

/*!
	Represents heads-up display: set of labels and minimap.
*/
class Hud : irr::IEventReceiver
{
public:
	/*!
		Constructs HUD.
		Warning! It is important to call activate/deactivate
		before/after use of HUD.
		@param level Level instance.
		@param configFilename Path to config file.
	*/
	Hud(Level* level, const irr::io::path& configFilename);
	~Hud(void);

	/*!
		Activates HUD (prepares UI & rendering pipeline).
	*/
	void activate();

	/*!
		Deactivates HUD (affects UI & rendering pipeline).
	*/
	void deactivate();

	/*!
		Makes HUD visible or invisible depending on argument.
		@param show Visibility flag.
	*/
	void show(bool show);

	void setLivesCount(irr::u32 count);
	void setCoinsCount(irr::u32 count);
	void showPauseIndicator(bool show);

	/*!
		Implementation of IEventReceiver.
	*/
	bool OnEvent(const irr::SEvent& event);

private:
	Game* _game;
	HudConfig _config;

	irr::gui::IGUIStaticText* _livesCountLabel;
	irr::gui::IGUIStaticText* _coinsCountLabel;
	irr::gui::IGUIStaticText* _pauseIndicatorLabel;

	bool _pauseIndicated;

	irr::scene::ICameraSceneNode* _minimapCamera;
	irr::scene::ICameraSceneNode* _previousCamera;
	irr::video::ITexture* _minimapTexture;

	irr::gui::IGUIImage* _minimap;

	bool _showMinimap;

	void createLabel(irr::gui::IGUIStaticText** label, 
		const HudConfig::Label& config);
};