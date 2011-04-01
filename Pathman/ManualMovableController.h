#pragma once

#include "MovableController.h"
#include "EDirection.h"

class Movable;

/*!
	Controls movable treating keyboard events 
	as changes of direction for controlled object.
*/
class ManualMovableController : MovableController
{
public:
	/*!
		Constructs controller using provided keymap.
		@param controls Keymap.
		@param movable Controlled object (can be set up later).
	*/
	ManualMovableController(
		irr::core::map<irr::EKEY_CODE, E_DIRECTION>& controls,
		Movable* movable = NULL);
	~ManualMovableController(void);

	/*! 
		Implementation of IController.
	*/

	void refresh();

	bool OnEvent(const irr::SEvent& event);

private:
	irr::core::map<irr::EKEY_CODE, E_DIRECTION> _controls;
};