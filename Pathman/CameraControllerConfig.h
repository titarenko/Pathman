#pragma once

#include "Config.h"

class Game;

class CameraControllerConfig : Config
{
public:
	CameraControllerConfig(Game* game, const irr::io::path& filename);
	~CameraControllerConfig(void);

	irr::core::vector2df MouseSensitivity;
	irr::f32 WheelSensitivity;

	/*!
		Camera angles (fi and theta) in radians.
	*/
	irr::core::vector2df CameraAngles;

	/*!
		Camera radius: distance from the center of the board to camera.
	*/
	irr::f32 CameraRadius;
	irr::f32 MinCameraRadius;
	irr::f32 MaxCameraRadius;

private:

	/*!
		Implementation of the Config.
	*/
	void OnNode(const irr::core::stringw& name);
};