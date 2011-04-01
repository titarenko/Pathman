#include "CameraControllerConfig.h"

using namespace irr;
using namespace core;
using namespace io;

CameraControllerConfig::CameraControllerConfig(Game* game, const path& filename)
	: Config(game, filename)
{
	while (next());
}

CameraControllerConfig::~CameraControllerConfig(void)
{
}

void CameraControllerConfig::OnNode(const stringw& name)
{
	if (name == "mouseSensitivity") {

		MouseSensitivity.X = read<f32>("horizontal");
		MouseSensitivity.Y = read<f32>("vertical");

	} else if (name == "wheelSensitivity") {

		WheelSensitivity = read<f32>("value");

	} else if (name == "cameraAngles") {

		CameraAngles.X = read<f32>("fi");
		CameraAngles.Y = read<f32>("theta");

	} else if (name == "cameraRadius") {

		CameraRadius = read<f32>("value");
		MinCameraRadius = read<f32>("min");
		MaxCameraRadius = read<f32>("max");
		
	}
}