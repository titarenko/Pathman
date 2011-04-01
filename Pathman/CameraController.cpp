#include <cmath>
#include "CameraController.h"
#include "Game.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace gui;
using namespace scene;

static irr::f32 MIN_COORDINATE_VALUE = 0.1f;
static irr::f32 MAX_COORDINATE_VALUE = 0.9f;

static irr::f32 MIN_THETA_VALUE = 0.001f*PI;
static irr::f32 MAX_THETA_VALUE = 0.999f*PI;

CameraController::CameraController(Game* game,
	ICameraSceneNode* camera, 
	const path& configFilename)
	: _game(game)
	, _camera(camera)
	, _config(game, configFilename)
{
	_cameraRadius = _config.CameraRadius;
	_cameraAngles =_config.CameraAngles;
}

CameraController::~CameraController(void)
{
}

void CameraController::refresh()
{
	closeCursorPosition();
	_previousMousePosition = _game->getDevice(
		)->getCursorControl()->getRelativePosition();
	refreshPosition();
}

bool CameraController::closeCoordinate(f32& value)
{
	if (value < MIN_COORDINATE_VALUE) {
		value = MAX_COORDINATE_VALUE;
		return true;
	}

	if (value > MAX_COORDINATE_VALUE) {
		value = MIN_COORDINATE_VALUE;
		return true;
	}

	return false;
}

void CameraController::refreshPosition()
{
	_camera->setPosition(vector3df(
		_cameraRadius*sinf(_cameraAngles.Y)*cosf(_cameraAngles.X),
		_cameraRadius*cosf(_cameraAngles.Y),
		_cameraRadius*sinf(_cameraAngles.Y)*sinf(_cameraAngles.X)));
}

void CameraController::closeCursorPosition()
{
	ICursorControl* cursor = _game->getDevice()->getCursorControl();
	vector2df position = cursor->getRelativePosition();

	if (closeCoordinate(position.X) ||
		closeCoordinate(position.Y)) {
		cursor->setPosition(position);
		_previousMousePosition = position;
	}
}

bool CameraController::OnEvent(const SEvent& event)
{
	closeCursorPosition();

	if (event.EventType == EET_MOUSE_INPUT_EVENT) {

		if (event.MouseInput.Event == EMIE_MOUSE_MOVED) {
			ICursorControl* cursor = _game->getDevice()->getCursorControl();
			vector2df position = cursor->getRelativePosition();

			vector2df delta = position - _previousMousePosition;
			_previousMousePosition = position;

			_cameraAngles += 
				vector2df(delta.X, delta.Y)*_config.MouseSensitivity;

			if (_cameraAngles.Y > MAX_THETA_VALUE)
				_cameraAngles.Y = MAX_THETA_VALUE;
			if (_cameraAngles.Y < MIN_THETA_VALUE)
				_cameraAngles.Y = MIN_THETA_VALUE;

			refreshPosition();

			return true;
		}

		if (event.MouseInput.Event == EMIE_MOUSE_WHEEL) {
			_cameraRadius += 
				event.MouseInput.Wheel*_config.WheelSensitivity;

			if (_cameraRadius > _config.MaxCameraRadius)
				_cameraRadius = _config.MaxCameraRadius;
			if (_cameraRadius < _config.MinCameraRadius)
				_cameraRadius = _config.MinCameraRadius;

			refreshPosition();

			return true;
		}

	}

	return false;
}