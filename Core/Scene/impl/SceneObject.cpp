#pragma once
#include "SceneObject.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			virtual const RawString &guid SceneObject::getName() const
			{
				return name.c_str();
			}
			
			virtual IComponent* SceneObject::getComponent(const RawString &name) const
			{
				auto iter = components->find(name);
				if(iter == components.end()) return nullptr;
				
				return iter->second;
			}

			virtual void SceneObject::addComponent(IComponent* component)
			{
				components.emplace(component->getName(), component);
			}

			virtual void SceneObject::removeComponent(const RawString &name)
			{
				components.erase(name);
			}
			
			virtual void SceneObject::removeComponent(IComponent* component)
			{
				removeComponent(component->getName());
			}
		}
	}
}