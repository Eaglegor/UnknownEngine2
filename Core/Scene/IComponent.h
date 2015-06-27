#pragma once

#include <Core/State/Synchronizable.h>
#include "ComponentType.h"

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

			class IComponent : public State::Synchronizable
			{
			public:
				virtual ~IComponent(){}

				virtual const char* getName() = 0;
				virtual Subsystems::ISubsystem* getParentSubsystem() = 0;
				virtual ComponentType getType() = 0;

				virtual ISceneObject* getParentSceneObject() = 0;
			};
		}
	}
}