#pragma once

#include <Utils/DataStructures/UnsafeUnorderedMap.h>
#include <Utils/Common/String.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Subsystems
		{
			using Utils::Common::String;
			using Utils::Common::RawString;
			using Utils::DataStructures::UnsafeUnorderedMap;

			class ISubsystem;

			class SubsystemsManager
			{
			public:
				ISubsystem* createSubsystem(const RawString &name);

				void addSubsystemFactory(const RawString &name, ISubsystemsFactory* factory);
				
			private:
				UnsafeUnorderedMap<String, ISubsystem*> subsystems;
			};
		}
	}
}