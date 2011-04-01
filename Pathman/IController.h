#pragma once

#include <irrlicht.h>

/*!
	Represents interface for controller: 
	entity for controlling any game entity such as camera, enemy, etc.
*/
class IController : public irr::IEventReceiver
{
public:
	/*!
		Should be called before controller use.
		(For example at stage activation.)
	*/
	virtual void refresh() = 0;
};