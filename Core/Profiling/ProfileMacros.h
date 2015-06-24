#pragma once

#include "RAIIFunctionProfiler.h"
#include "FunctionSignatureMacros.h"

#if UNKNOWN_ENGINE_ENABLE_PROFILING
	#define PROFILE_FUNCTION() UnknownEngine::Core::Profiling::RAIIFunctionProfiler __function_profiler__(UNKNOWN_ENGINE_PRETTY_FUNCTION)
	#define PROFILE_CHECKPOINT(name) Core::Profiling::ProfileManager::getSingleton()->getProfileInstance()->checkPoint(#name)
#else
	#define PROFILE_FUNCTION()
	#define PROFILE_CHECKPOINT(name)
#endif
