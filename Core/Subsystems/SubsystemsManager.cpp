#include "SubsystemsManager.h"
#include "ISubsystemFactory.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Subsystems
		{
			ISubsystem * SubsystemsManager::createSubsystem(const RawString & name, const SubsystemDesc & desc)
			{
				auto iter = subsystem_factories.find(name);
				if (iter == subsystem_factories.end()) return nullptr;
				ISubsystem* subsystem = iter->second->createSubsystem(desc);
				subsystems.emplace(name, subsystem);
				return subsystem;
			}
			void SubsystemsManager::destroySubsystem(const RawString & name)
			{
				auto iter = subsystems.find(name);
				if (iter == subsystems.end()) return;
				auto factory_iter = subsystem_factories.find(name);
				if (factory_iter == subsystem_factories.end()) return; // FATAL ERROR
				factory_iter->second->destroySubsystem(iter->second);
				subsystems.erase(iter);
			}

			ISubsystem * SubsystemsManager::getSubsystem(const RawString & name) const
			{
				auto iter = subsystems.find(name);
				if (iter == subsystems.end()) return nullptr;
				return iter->second;
			}

			ISubsystem * SubsystemsManager::findSubsystemIf(const SubsystemPredicate & predicate)
			{
				for (auto &iter : subsystems)
				{
					if (predicate(iter.second)) return iter.second;
				}
				return nullptr;
			}

			void SubsystemsManager::addSubsystemFactory(const RawString & name, ISubsystemFactory * factory) const
			{
				subsystem_factories.emplace(name, factory);
			}

			void SubsystemsManager::removeSubsystemFactory(const RawString & name)
			{
				auto iter = subsystems.find(name);
				if (iter != subsystems.end())
				{
					destroySubsystem(name);
				}
				subsystem_factories.erase(name);
			}
		}
	}
}