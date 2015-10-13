#include "SceneObject.h"
#include "../IComponent.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			SceneObject::SceneObject(const RawString & name):
			name(name)
			{
			}

			const RawString SceneObject::getName() const
			{
				return name.c_str();
			}
			
			IComponent* SceneObject::getComponent(const RawString &name) const
			{
				auto iter = components.find(name);
				if(iter == components.end()) return nullptr;
				
				return iter->second;
			}

			void SceneObject::addComponent(IComponent* component)
			{
				components.emplace(component->getName(), component);
			}

			void SceneObject::removeComponent(const RawString &name)
			{
				components.erase(name);
			}
			
			void SceneObject::removeComponent(IComponent* component)
			{
				removeComponent(component->getName());
			}
		}
	}
}