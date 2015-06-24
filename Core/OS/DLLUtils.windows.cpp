#include "DLLUtils.h"
#include <windows.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace OS
		{
			static void* DLLUtils::loadLibrary(const char* filename)
			{
				return LoadLibrary(filename);
			}

			static void* DLLUtils::getFunctionAddress(void* library_handle, const char* name)
			{
				return GetProcAddress(reinterpret_cast<HMODULE>(library_handle), name);
			}

			static bool DLLUtils::unloadLibrary(void* library_handle)
			{
				return FreeLibrary(reinterpret_cast<HMODULE>(library_handle));
			}

			static const char* DLLUtils::getLastLoadError()
			{
				return GetLastError();
			}
		}
	}
}
