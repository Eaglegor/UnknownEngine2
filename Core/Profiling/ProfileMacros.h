#pragma once

#include "FunctionSignatureMacros.h"

#if UNKNOWNENGINE_ENABLE_PROFILING
	#define PROFILE_FUNCTION_START() Core::Profiling::ProfileManager::getSingleton()->getProfileInstance()->startFunction(UNKNOWN_ENGINE_PRETTY_FUNCTION)
	#define PROFILE_FUNCTION_CHECKPOINT(name) Core::Profiling::ProfileManager::getSingleton()->getProfileInstance()->checkPoint(#name)
	#define PROFILE_FUNCTION_END() Core::Profiling::ProfileManager::getSingleton()->getProfileInstance()->endFunction(UNKNOWN_ENGINE_PRETTY_FUNCTION)
#else
	#define PROFILE_FUNCTION_START()
	#define PROFILE_FUNCTION_CHECKPOINT(, name)
	#define PROFILE_FUNCTION_END()
#endif
