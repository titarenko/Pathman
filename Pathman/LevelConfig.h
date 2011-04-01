#pragma once

#include <map>
#include "Config.h"
#include "EDirection.h"
#include "EMovableControllerType.h"

/*!
	Represents level config: contains a lot of settings 
	not only for level as high level entity, but also for
	the most of level entities such as board, a set of enemies etc.
	(You can think that it is in some extent over-saturated but
	decision to store almost all level-related information in one place 
	was taken to prevent creation of tens of small files in the 
	solution folder to represent tiny configs for level entities.)
*/
class LevelConfig : Config
{
public:
	/*!
		Reads config using provided path.
		@param game Game instance.
		@param filename Path to config file.
	*/
	LevelConfig(Game* game, const irr::io::path& filename);
	~LevelConfig(void);

	irr::EKEY_CODE AbortKey;
	irr::EKEY_CODE PauseKey;

	struct
	{
		irr::f32 Fov;
		irr::f32 Near;
		irr::f32 Far;
	} Camera;

	struct
	{
		irr::video::ITexture* Front;
		irr::video::ITexture* Back;
		irr::video::ITexture* Left;
		irr::video::ITexture* Right;
		irr::video::ITexture* Top;
		irr::video::ITexture* Bottom;
	} Environment;

	/*!
		Size of the board in cells.
	*/
	struct
	{
		irr::u32 Width;
		irr::u32 Height;
	} Board;

	struct Model
	{
		irr::scene::IAnimatedMesh* Mesh;
		irr::f32 AnimationSpeed;
		bool AnisotropicFiltering;
	};

	struct
	{
		Model Floor;
		Model Obstacle;
		Model Coin;
		Model Enemy;
		Model MainCharacter;
	} Models;

	irr::f32 CoinRotationSpeed;

	/*!
		Indices of the cells with obstacles.
	*/
	irr::core::array<irr::u32> Obstacles;

	/*!
		Indices of the cells with coins.
	*/
	irr::core::array<irr::u32> Coins;

	struct
	{
		irr::io::path Hit;
		irr::io::path Coin;
		irr::io::path Death;
	} SoundFilenames;
	
	struct
	{
		irr::u32 ControllerId;
		irr::u32 Position;
		irr::u32 LivesCount;
		irr::u32 InvisibilityTime;
		irr::f32 Speed;
	} MainCharacter;

	struct Enemy
	{
		irr::u32 ControllerId;
		irr::u32 Position;
		irr::f32 Speed;
	};

	irr::core::array<Enemy> Enemies;

	struct MovableController
	{
		E_MOVABLE_CONTROLLER_TYPE Type;
		union
		{
			irr::u32 WaypointsSetId;
			irr::f32 TurnProbability;
		} Parameter;
	};

	irr::core::map<irr::u32, MovableController> MovableControllers;

	std::map<irr::u32, irr::core::list<E_DIRECTION>> WaypointsSets;

	irr::core::map<irr::EKEY_CODE, E_DIRECTION> Controls;

private:
	/*!
		Implementation of Config.
	*/
	void OnNode(const irr::core::stringw& name);

	void readCamera(const irr::core::stringw& name);
	void readEnvironment(const irr::core::stringw& name);
	void readBoard(const irr::core::stringw& name);
	void readCharacters(const irr::core::stringw& name);
	void readControllers(const irr::core::stringw& name);

	void readModel(Model& model);
};