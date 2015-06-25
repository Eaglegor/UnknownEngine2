#include "DLLUtils.h"
#include <windows.h>
#include <string>

namespace UnknownEngine
{
	namespace Core
	{
		namespace OS
		{
			static std::string lastError;

			void* DLLUtils::loadLibrary(const char* filename)
			{
				return LoadLibrary(filename);
			}

			void* DLLUtils::getFunctionAddress(void* library_handle, const char* name)
			{
				return reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HINSTANCE>(library_handle), name));
			}

			bool DLLUtils::unloadLibrary(void* library_handle)
			{
				return FreeLibrary(reinterpret_cast<HINSTANCE>(library_handle)) != 0;
			}

			const char* DLLUtils::getLastLoadError()
			{
				lastError = "Error code: " + std::to_string(GetLastError());
				return lastError.c_str();
			}
		}
	}
}
