#pragma once

#include <Utils/Common/String.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			class IComponent;
			
			using Utils::Common::RawString;

			class ISceneObject
			{
			public:
				virtual ~ISceneObject(){}
				
				virtual const RawString getName() const = 0;

				virtual IComponent* getComponent(const RawString &name) const = 0;

				virtual void addComponent(IComponent* component) = 0;

				virtual void removeComponent(const RawString &name) = 0;
				virtual void removeComponent(IComponent* component) = 0;
			};
		}
	}
}