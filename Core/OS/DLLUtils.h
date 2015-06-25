#pragma once

#include <OS_export.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace OS
		{
			class DLLUtils
			{
				public:
					OS_EXPORT
					static void* loadLibrary(const char* filename);
					
					OS_EXPORT
					static void* getFunctionAddress(void* library_handle, const char* name);
					
					OS_EXPORT
					static bool unloadLibrary(void* library_handle);
					
					OS_EXPORT
					static const char* getLastLoadError();
			};
		}
	}
}
