#pragma once
#include "../ISceneObject.h"
#include <Utils/Common/String.h>
#include <Utils/DataStructures/UnsafeUnorderedMap.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			using Utils::DataStructures::UnsafeUnorderedMap;
			using Utils::Common::RawString;
			using Utils::Common::String;
			
			class SceneObject : public ISceneObject
			{
				public:
					virtual const RawString& getName() const final override;

					virtual IComponent* getComponent(const RawString &name) const final override;

					virtual void addComponent(IComponent* component) final override;

					virtual void removeComponent(const RawString &name) final override;
					virtual void removeComponent(IComponent* component) final override;
					
				private:
					UnsafeUnorderedMap<String, IComponent*> components;
					String name;
			};
		}
	}
}
