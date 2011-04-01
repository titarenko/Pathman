#pragma once

#include "IConfigReader.h"
#include <irrlicht.h>

/*!
	Represents xml reader that uses Irrlicht's filesystem.
*/
class VirtualXmlReader : public IConfigReader
{
public:
	VirtualXmlReader(irr::io::IXMLReader* reader);
	~VirtualXmlReader(void);

	/*!
		Implementation of the IConfigReader.
	*/

	virtual bool next();

	virtual irr::core::stringw getNodeName();

	virtual irr::core::stringw getAttributeValue(
		const irr::core::stringw& name);
	virtual int getAttributeValueAsInt(
		const irr::core::stringw& name);
	virtual float getAttributeValueAsFloat(
		const irr::core::stringw& name);

private:
	irr::io::IXMLReader* _reader;
};