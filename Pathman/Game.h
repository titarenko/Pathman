#pragma once

#include <irrlicht.h>
#include <irrKlang.h>
#include "StageInfo.h"
#include "EGameEvent.h"

class GameConfig;

/*!
	Represents root object of the game.
*/
class Game : irr::IEventReceiver
{
public:
	/*!
		Initializes game using provided config.
		@param configFilename Path to the config file.
	*/
	Game(const char* configFilename);

	/*!
		Deallocates resources.
	*/
	~Game(void);

	/*!
		Implementation of irr::IEventReceiver.
	*/
	virtual bool OnEvent(const irr::SEvent& event);	

	/*!
		Creates Irrlicht's root object using data from provided config
		as well as IrrKlang's root object.
	*/
	void createDevice(const GameConfig& config);

	/*!
		Returns pointer to the Irrlicht's root object.
	*/
	irr::IrrlichtDevice* getDevice() const;

	/*!
		Returns pointer to the IrrKlang's root object.
	*/
	irrklang::ISoundEngine* getSoundEngine() const;

	/*!
		Add assets pack to the Irrlicht's filesystem.
		@param filename Path to folder or archive file with assets.
	*/
	void addAssets(const irr::io::path& filename);

	/*!
		Broadcast event to all stages of the game.
	*/
	void broadcastEvent(E_GAME_EVENT event);

	/*!
		Updates game. Must be called until false is returned 
		in order to run the game.
	*/
	bool update();

	/*!
		Converts Irrlicht's user event to the game event.
		(Game events are broadcasted using Irrlicht's user event system.)
	*/
	static E_GAME_EVENT ToGameEvent(const irr::SEvent& event);

	/*!
		Enables additional render: scene will be rendered twice per frame.
		Special events shall be broadcasted before rendering additional 
		time and after to allow stages to perform needed changes.
	*/
	void enableAdditionalRender(bool enable);

	/*!
		Enables or disables sounds.
	*/
	void enableSound(bool enable);

private:
	irr::IrrlichtDevice* _device;
	irrklang::ISoundEngine* _soundEngine;

	irr::core::array<irr::IEventReceiver*> _stages;
	irr::u32 _sleepValue;
	bool _additionalRender;

	bool _soundEnabled;
	bool _soundAllowed;

	irr::IEventReceiver* createStage(const StageInfo& stage);
};