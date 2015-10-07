#pragma once

#include <Core/Scene/ComponentDesc.h>
#include <Core/State/Synchronizable.h>
#include <Utils/Common/String.h>

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
			using Utils::Common::RawString;
			using Tasks::ITask;
			using Scene::IComponent;
			using Scene::ComponentDesc;
			using State::Synchronizable;

			class ISubsystem : public Synchronizable
			{
				public:
					virtual ~ISubsystem(){}
					virtual RawString getName() const = 0;

					virtual IComponent* createComponent(ComponentDesc& desc) = 0;
					virtual void destroyComponent(IComponent* component) = 0;
			};
		}
	}
}
