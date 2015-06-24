#pragma once

#include "DLLUtils.h"
#include <dlfcn.h>
#include <link.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace OS
		{
			static void* DLLUtils::loadLibrary(const char* filename)
			{
				return dlopen(filename, RTLD_LAZY);
			}

			static void* DLLUtils::getFunctionAddress(void* library_handle, const char* name)
			{
				return dlsym(library_handle, name);
			}

			static bool DLLUtils::unloadLibrary(void* library_handle)
			{
				return dlclose(library_handle);
			}

			static const char* DLLUtils::getLastLoadError()
			{
				return dlerror();
			}
		}
	}
}
