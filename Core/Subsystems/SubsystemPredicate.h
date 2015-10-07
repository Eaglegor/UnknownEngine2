#pragma once

#include <functional>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Subsystems
		{
			class ISubsystem;

			using SubsystemPredicate = std::function<bool(ISubsystem*)>;
		}
	}
}