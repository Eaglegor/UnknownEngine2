#pragma once

#include <Utils/Common/Singleton.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Subsystems
		{
			class ISubsystem;
		}

		namespace Messages
		{
			class IMessage;
		}

		namespace Scene
		{
			class IComponent;
			class ISceneObject;
		}

		namespace Memory
		{
			using Subsystems::ISubsystem;
			using Messages::IMessage;
			using Scene::IComponent;
			using Scene::ISceneObject;

			class MemoryManager : public Utils::Common::Singleton<MemoryManager>
			{
			public:
				virtual ~MemoryManager(){}
				
				template<typename T, typename... Arg>
				T* newSubsystem(Arg... arg)
				{
					static_assert(std::is_base_of<ISubsystem, T>::value, "MemoryManager::new{X} is called for wrong object type {X}");
					return new T(arg);
				}

				template<typename T>
				void deleteSubsystem(T* subsystem)
				{
					static_assert(std::is_base_of<ISubsystem, T>::value, "MemoryManager::delete{X} is called for wrong object type {X}");
					delete T;
				}

				template<typename T, typename... Arg>
				T* newSceneObject(Arg... arg)
				{
					static_assert(std::is_base_of<ISceneObject, T>::value, "MemoryManager::new{X} is called for wrong object type {X}");
					return new T(arg);
				}

				template<typename T>
				void deleteSceneObject(T* scene_object)
				{
					static_assert(std::is_base_of<ISceneObject, T>::value, "MemoryManager::delete{X} is called for wrong object type {X}");
					delete T;
				}

				template<typename T, typename... Arg>
				T* newComponent(Arg... arg)
				{
					static_assert(std::is_base_of<IComponent, T>::value, "MemoryManager::new{X} is called for wrong object type {X}");
					return new T(arg);
				}

				template<typename T>
				void deleteComponent(T* component)
				{
					static_assert(std::is_base_of<ISubsystem, T>::value, "MemoryManager::delete{X} is called for wrong object type {X}");
					delete T;
				}

				template<typename T, typename... Arg>
				T* newMessage(Arg... arg)
				{
					static_assert(std::is_base_of<IMessage, T>::value, "MemoryManager::new{X} is called for wrong object type {X}");
					return new T(arg);
				}

				template<typename T>
				void deleteMessage(T* message)
				{
					static_assert(std::is_base_of<ISubsystem, T>::value, "MemoryManager::delete{X} is called for wrong object type {X}");
					delete T;
				}

			private:
				
			};

		}
	}
}