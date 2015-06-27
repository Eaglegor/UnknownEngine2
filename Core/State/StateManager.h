#pragma once

#include <Utils/Common/Singleton.h>
#include "SynchronizationState.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Subsystems
		{
			class ISubsystem;
		}

		namespace State
		{
			class StateManager : public Utils::Common::Singleton<StateManager>
			{
			public:
				virtual ~StateManager(){}

				SynchronizationState getSynchronizationState(const Subsystems::ISubsystem* subsystem) const;
				void setSynchronizationState(const Subsystems::ISubsystem* subsystem, const SynchronizationState &state);
			};
		}
	}
}