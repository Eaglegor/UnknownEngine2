#pragma once

#include <Utils/DataStructures/UnsafeUnorderedMap.h>
#include <Utils/Common/String.h>
#include "SubsystemPredicate.h"

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
			class ISubsystemFactory;
			class SubsystemDesc;

			class SubsystemsManager
			{
			public:
				ISubsystem* createSubsystem(const RawString &name, const SubsystemDesc &desc);
				void destroySubsystem(const RawString &name);

				ISubsystem* getSubsystem(const RawString &name) const;
				ISubsystem* findSubsystemIf(const SubsystemPredicate &predicate);

				void addSubsystemFactory(const RawString &name, ISubsystemFactory* factory) const;
				void removeSubsystemFactory(const RawString &name);
				
			private:
				UnsafeUnorderedMap<String, ISubsystem*> subsystems;
				UnsafeUnorderedMap<String, ISubsystemFactory*> subsystem_factories;
			};
		}
	}
}