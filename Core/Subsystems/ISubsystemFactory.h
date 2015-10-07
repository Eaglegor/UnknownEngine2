#pragma once

#include <Utils/Common/String.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Subsystems
		{
			class ISubsystem;
			class SubsystemDesc;

			class ISubsystemFactory
			{
			public:
				virtual ~ISubsystemFactory() {}

				virtual ISubsystem* createSubsystem(const SubsystemDesc &desc) = 0;
				virtual void destroySubsystem(ISubsystem* subsystem) = 0;
			};
		}
	}
}