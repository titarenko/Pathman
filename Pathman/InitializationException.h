#pragma once

#include <irrlicht.h>

/*!
	Thrown when something hasn't been properly initalized.
*/
class InitializationException
{
public:
	InitializationException(const irr::core::stringw& message);
	~InitializationException(void);

	const irr::core::stringw& getMessage() const;

private:
	const irr::core::stringw& _message;
};