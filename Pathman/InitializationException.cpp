#include "InitializationException.h"

using namespace irr;
using namespace core;

InitializationException::InitializationException(const stringw& message)
	: _message(message)
{
}

InitializationException::~InitializationException(void)
{
}

const stringw& InitializationException::getMessage() const
{
	return _message;
}