#include "DLLUtils.h"
#include <dlfcn.h>
#include <link.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace OS
		{
			void* DLLUtils::loadLibrary(const char* filename)
			{
				return dlopen(filename, RTLD_LAZY);
			}

			void* DLLUtils::getFunctionAddress(void* library_handle, const char* name)
			{
				return dlsym(library_handle, name);
			}

			bool DLLUtils::unloadLibrary(void* library_handle)
			{
				return dlclose(library_handle);
			}

			const char* DLLUtils::getLastLoadError()
			{
				return dlerror();
			}
		}
	}
}
