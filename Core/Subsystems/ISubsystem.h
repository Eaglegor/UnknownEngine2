#pragma once

#include <Synchronizable.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Tasks
		{
			class ITask;
		}

		namespace Subsystems
		{
			class ISubsystem : public Synchronizable
			{
				public:
					virtual ~ISubsystem(){}
					virtual const char* getName() = 0;
					virtual Tasks::ITask* getPrimaryTask() = 0;
			};
		}
	}
}
