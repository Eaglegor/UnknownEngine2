#include "../SceneManager.h"
#include "ISceneObject.h"
#include "SceneObject.h"
#include <Utils/DataStructures/UnsafeVector.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			using Utils::DataStructures::UnsafeVector;
			
			ISceneObject* SceneManager::createSceneObject(const RawString &name)
			{
				ISceneObject* scene_object = new SceneObject(name);
				scene_objects.emplace(name, scene_object);
				return scene_object;
			}

			ISceneObject* SceneManager::getSceneObject(const RawString &name)
			{
				auto iter = scene_objects->find(name);
				if(iter == scene_objects.end()) return nullptr;
				
				return iter->second;
			}

			void SceneManager::destroySceneObject(const RawString &name)
			{
				auto iter = scene_objects->find(name);
				ISceneObject* obj = iter->second;
				scene_objects.erase(iter);
				delete obj;
			}

			void SceneManager::destroySceneObject(ISceneObject* sceneObject)
			{
				destroySceneObject(sceneObject->getName());
			}

			void SceneManager::clearScene()
			{
				UnsafeVector<ISceneObject*> scene_object_refs(scene_objects.size());
				scene_objects.clear();
				for(ISceneObject* scene_object : scene_object_refs)
				{
					delete scene_object;
				}
			}
		}
	}
}