#pragma once

#include <Core/Scene/ComponentDesc.h>
#include <Core/State/Synchronizable.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			class IComponent;
		}

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

					virtual Scene::IComponent* createComponent(Scene::ComponentDesc& desc) = 0;
					virtual void destroyComponent(Scene::IComponent* component) = 0;


			};
		}
	}
}
