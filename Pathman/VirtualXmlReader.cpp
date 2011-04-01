#include "VirtualXmlReader.h"
#include "InitializationException.h"

using namespace irr;
using namespace core;
using namespace io;

VirtualXmlReader::VirtualXmlReader(IXMLReader* reader)
	: _reader(reader)
{
	if (!_reader)
		throw InitializationException("_reader");
}

VirtualXmlReader::~VirtualXmlReader(void)
{
	_reader->drop();
}

bool VirtualXmlReader::next()
{
	if (!_reader)
		return false;

	bool result;
	while ((result = _reader->read()) && 
		_reader->getNodeType() == EXN_ELEMENT_END);

	if (!result) {
		_reader->drop();
		_reader = 0;
	}

	return result;
}

stringw VirtualXmlReader::getNodeName()
{
	return stringw(_reader->getNodeName());
}

stringw VirtualXmlReader::getAttributeValue(const stringw& name)
{
	return stringw(_reader->getAttributeValue(name.c_str()));
}

int VirtualXmlReader::getAttributeValueAsInt(const stringw& name)
{
	return _reader->getAttributeValueAsInt(name.c_str());
}

float VirtualXmlReader::getAttributeValueAsFloat(const stringw& name)
{
	return _reader->getAttributeValueAsFloat(name.c_str());
}