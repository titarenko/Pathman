#include "Random.h"
#include <cstdlib>
#include <ctime>

using namespace irr;

void Random::SetSeed()
{
	SetSeed((u32) time(NULL));
}

void Random::SetSeed(u32 seed)
{
	srand(seed);
}

f32 Random::GetNumber()
{
	return rand()/(f32) RAND_MAX;
}

s32 Random::GetNumber(s32 max)
{
	return (s32) rand()%max;
}