#pragma once

#include <Core/State/Synchronizable.h>
#include "ComponentType.h"

#include <Utils/Common/String.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Subsystems
		{
			class ISubsystem;
		}

		namespace Scene
		{
			class ISceneObject;

			using Subsystems::ISubsystem;
			using Utils::Common::RawString;

			class IComponent : public State::Synchronizable
			{
			public:
				virtual ~IComponent(){}

				virtual RawString getName() = 0;
				virtual Subsystems::ISubsystem* getParentSubsystem() = 0;
				virtual IComponentType* getType() = 0;

				virtual ISceneObject* getParentSceneObject() = 0;
			};
		}
	}
}