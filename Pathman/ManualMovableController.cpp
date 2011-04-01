#include "ManualMovableController.h"
#include "MainCharacter.h"

using namespace irr;
using namespace core;
using namespace io;

ManualMovableController::ManualMovableController(
	map<EKEY_CODE, E_DIRECTION>& controls,
	Movable* movable)
	: MovableController(movable)
{
	// Irrlicht map's copy constructor is not available, 
	// so copy operation is performed manually
	map<EKEY_CODE, E_DIRECTION>::Iterator it = controls.getIterator();
	while (!it.atEnd()) {
		_controls.set(it->getKey(), it->getValue());
		it++;
	}
}

ManualMovableController::~ManualMovableController(void)
{
}

void ManualMovableController::refresh()
{
}

bool ManualMovableController::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_KEY_INPUT_EVENT && 
		event.KeyInput.PressedDown &&
		_controls.find(event.KeyInput.Key)) {
		_movable->move(_controls[event.KeyInput.Key]);
		return true;
	}
	return false;
}