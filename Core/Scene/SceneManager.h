#pragma once

#include <Utils/Common/Singleton.h>
#include <Utils/Common/String.h>
#include <Utils/DataStructures/UnsafeUnorderedMap.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			class ISceneObject;
			
			using Utils::DataStructures::UnsafeUnorderedMap;
			using Utils::Common::String;
			using Utils::Common::RawString;

			class SceneManager : public Utils::Common::Singleton < SceneManager >
			{
			public:
				virtual ~SceneManager(){}

				ISceneObject* createSceneObject(const RawString &name);
				ISceneObject* getSceneObject(const RawString &name);
				void destroySceneObject(const RawString &name);
				void destroySceneObject(ISceneObject* sceneObject);

				void clearScene();
				
			private:
				UnsafeUnorderedMap<String, ISceneObject*> scene_objects;
			};
		}
	}
}