#pragma once

#include <OS_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace OS
		{
			class OS_EXPORT DLLUtils
			{
				public:
					static void* loadLibrary(const char* filename);
					static void* getFunctionAddress(void* library_handle, const char* name);
					static bool unloadLibrary(void* library_handle);
					static const char* getLastLoadError();
			};
		}
	}
}
