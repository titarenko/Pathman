#pragma once

#include <irrlicht.h>
#include "EStageType.h"

struct StageInfo
{
	E_STAGE_TYPE Type;
	irr::core::stringw ConfigFilename;
};