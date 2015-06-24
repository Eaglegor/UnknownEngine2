#pragma once

#include <Core/State/Synchronizable.h>

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
			class ISubsystem : public State::Synchronizable
			{
				public:
					virtual ~ISubsystem(){}
					virtual const char* getName() = 0;
					virtual Tasks::ITask* getPrimaryTask() = 0;
			};
		}
	}
}
