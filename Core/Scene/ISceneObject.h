#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			class IComponent;

			class ISceneObject
			{
			public:
				virtual ~ISceneObject(){}

				virtual IComponent* getComponent(const char* name) = 0;

				virtual void addComponent(IComponent* component) = 0;

				virtual void removeComponent(const char* name) = 0;
				virtual void removeComponent(IComponent* component) = 0;
			};
		}
	}
}