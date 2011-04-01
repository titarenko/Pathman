#include "XmlReader.h"
#include "InitializationException.h"

using namespace irr;
using namespace core;
using namespace io;

XmlReader::XmlReader(const char* filename)
#ifdef _IRR_WINDOWS_
	: _reader(createIrrXMLReaderUTF16(filename))
#else
	: _reader(createIrrXMLReaderUTF32(filename))
#endif
{
	if (!_reader)
		throw InitializationException("_reader");
}

XmlReader::~XmlReader(void)
{
	delete _reader;
}

bool XmlReader::next()
{
	if (!_reader)
		return false;

	bool result;
	while ((result = _reader->read()) && 
		_reader->getNodeType() == EXN_ELEMENT_END);

	if (!result) {
		delete _reader;
		_reader = 0;
	}

	return result;
}

stringw XmlReader::getNodeName()
{
	return stringw(_reader->getNodeName());
}

stringw XmlReader::getAttributeValue(const stringw& name)
{
#ifdef _IRR_WINDOWS_
	return stringw(_reader->getAttributeValue((const char16*) name.c_str()));
#else
	return stringw(_reader->getAttributeValue((const char32*) name.c_str()));
#endif
}

int XmlReader::getAttributeValueAsInt(const stringw& name)
{
#ifdef _IRR_WINDOWS_
	return _reader->getAttributeValueAsInt((const char16*) name.c_str());
#else
	return _reader->getAttributeValueAsInt((const char32*) name.c_str());
#endif
}

float XmlReader::getAttributeValueAsFloat(const stringw& name)
{
#ifdef _IRR_WINDOWS_
	return _reader->getAttributeValueAsFloat((const char16*) name.c_str());
#else
	return _reader->getAttributeValueAsFloat((const char32*) name.c_str());
#endif
}