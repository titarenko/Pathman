#pragma once

#include <irrlicht.h>

/*!
	Set of methods for generating random objects.
*/
class Random
{
public:
	/*!
		Initializes RNG using current time as seed.
	*/
	static void SetSeed();

	/*!
		Initializes RNG.
		@param seed Seed to initialize RNG.
	*/
	static void SetSeed(irr::u32 seed);

	/*!
		Returns random number from 0.0 to 1.0 inclusively.
	*/
	static irr::f32 GetNumber();

	/*!
		Returns random signed integer number from 0 to max exclusively.
		@param max Upper boundary value.
	*/
	static irr::s32 GetNumber(irr::s32 max);
};