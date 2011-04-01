#pragma once

#include "IController.h"
#include "CameraControllerConfig.h"

class Game;

/*!
	Creates camera controller: mouse movements 
	change camera angles and wheel movement changes camera radius.
*/
class CameraController : IController
{
public:
	/*!
		Creates camera controller.
		@param game Game instance.
		@param camera Camera to control.
		@param configFilename Path to config file with controller's settings.
	*/
	CameraController(Game* game, 
		irr::scene::ICameraSceneNode* camera,
		const irr::io::path& configFilename);
	~CameraController(void);

	/*!
		Implementation of IController.
	*/

	void refresh();

	bool OnEvent(const irr::SEvent& event);

private:
	Game* _game;
	irr::scene::ICameraSceneNode* _camera;
	CameraControllerConfig _config;

	irr::core::vector2df _previousMousePosition;
	irr::core::vector2df _cameraAngles;
	irr::f32 _cameraRadius;

	bool closeCoordinate(irr::f32& value);
	void refreshPosition();
	void closeCursorPosition();
};