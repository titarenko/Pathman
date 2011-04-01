#pragma once

#include <irrlicht.h>

/*!
	Represents interface of the config reader.
*/
class IConfigReader
{
public:
	/*!
		Moves to the next node.
		Returns false if no more nodes left.
	*/
	virtual bool next() = 0;

	/*!
		Returns name of the current node.
	*/
	virtual irr::core::stringw getNodeName() = 0;

	/*!
		Returns value (as string) of the attribute with specified name.
	*/
	virtual irr::core::stringw getAttributeValue(
		const irr::core::stringw& name) = 0;

	/*!
		Returns value (as int) of the attribute with specified name.
	*/
	virtual int getAttributeValueAsInt(
		const irr::core::stringw& name) = 0;

	/*!
		Returns value (as float) of the attribute with specified name.
	*/
	virtual float getAttributeValueAsFloat(
		const irr::core::stringw& name) = 0;
};