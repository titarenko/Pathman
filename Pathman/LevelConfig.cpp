#include "LevelConfig.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;
using namespace scene;
using namespace gui;

LevelConfig::LevelConfig(Game* game, const path& filename)
	: Config(game, filename)
{
	while (next());
	
	Coins.sort();
	Obstacles.sort();
}

LevelConfig::~LevelConfig(void)
{
}

void LevelConfig::OnNode(const stringw& name)
{
	readCamera(name);
	readEnvironment(name);
	readBoard(name);
	readCharacters(name);
	readControllers(name);
}

void LevelConfig::readCamera(const stringw& name)
{
	if (name == "camera") {

		Camera.Fov = read<f32>("fov");
		
		Camera.Near = read<f32>("near");
		Camera.Far = read<f32>("far");

	}
}

void LevelConfig::readEnvironment(const stringw& name)
{
	if (name == "environment") {

		Environment.Back = read<ITexture*>("back");
		Environment.Bottom = read<ITexture*>("bottom");
		Environment.Front = read<ITexture*>("front");
		Environment.Left = read<ITexture*>("left");
		Environment.Right = read<ITexture*>("right");
		Environment.Top = read<ITexture*>("top");

	} else if (name == "sound") {

		stringw type = read<stringw>("type");
		path filename = read<path>("filename");

		if (type == "hit")
			SoundFilenames.Hit = filename;
		if (type == "coin")
			SoundFilenames.Coin = filename;
		if (type == "death")
			SoundFilenames.Death = filename;

	} else if (name == "key") {

		stringw type = read<stringw>("type");
		EKEY_CODE code = (EKEY_CODE) read<u32>("code");

		if (type == "pause")
			PauseKey = code;
		else if (type == "abort")
			AbortKey = code;

	}
}

void LevelConfig::readBoard(const stringw& name)
{
	if (name == "board") {

		Board.Width = read<u32>("width");
		Board.Height = read<u32>("height");

		readModel(Models.Floor);

	} else if (name == "coins") {

		readModel(Models.Coin);

		CoinRotationSpeed = read<f32>("rotationSpeed");

	} else if (name == "coin") {

		Coins.push_back(read<u32>("position"));

	} else if (name == "obstacles") {

		readModel(Models.Obstacle);

	} else if (name == "obstacle") {

		Obstacles.push_back(read<u32>("position"));

	}
}

void LevelConfig::readCharacters(const stringw& name)
{
	if (name == "mainCharacter") {

		MainCharacter.ControllerId = read<u32>("controllerId");

		readModel(Models.MainCharacter);

		MainCharacter.Position = read<u32>("position");
		MainCharacter.LivesCount = read<u32>("livesCount");
		MainCharacter.InvisibilityTime = read<u32>("invisibilityTime");
		MainCharacter.Speed = read<f32>("speed");

	} else if (name == "enemies") {

		readModel(Models.Enemy);

	} else if (name == "enemy") {

		LevelConfig::Enemy enemy;

		enemy.ControllerId = read<u32>("controllerId");
		enemy.Position = read<u32>("position");
		enemy.Speed = read<f32>("speed");
		
		Enemies.push_back(enemy);

	}
}

void LevelConfig::readControllers(const stringw& name)
{
	if (name == "manualMovableController") {

		MovableController controller;
		controller.Type = EMCT_MANUAL;
		MovableControllers.set(read<u32>("id"), controller);

	} else if (name == "randomMovableController") {

		MovableController controller;
		controller.Type = EMCT_RANDOM;
		controller.Parameter.TurnProbability = read<f32>("turnProbability");
		MovableControllers.set(read<u32>("id"), controller);

	} else if (name == "walkingMovableController") {

		MovableController controller;
		controller.Type = EMCT_WALKING;
		controller.Parameter.WaypointsSetId = read<u32>("waypointsSetId");
		MovableControllers.set(read<u32>("id"), controller);

	} else if (name == "pursuingMovableController") {

		MovableController controller;
		controller.Type = EMCT_PURSUING;
		MovableControllers.set(read<u32>("id"), controller);

	} else if (name == "waypoint") {

		u32 setId = read<u32>("setId");
		if (WaypointsSets.find(setId) == WaypointsSets.end())
			WaypointsSets[setId] = list<E_DIRECTION>();
		WaypointsSets[setId].push_back((E_DIRECTION) read<u32>("direction"));

	} else if (name == "control") {

		Controls.set(
			(EKEY_CODE) read<u32>("key"),
			(E_DIRECTION) read<u32>("direction"));

	}
}

void LevelConfig::readModel(LevelConfig::Model& model)
{
	model.Mesh = read<IAnimatedMesh*>("model");
	model.AnimationSpeed = read<f32>("animationSpeed");
	model.AnisotropicFiltering = read<bool>("anisotropicFiltering");

	if (model.AnisotropicFiltering)
		model.Mesh->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
}