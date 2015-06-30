#include "SceneManager.h"
#include "ISceneObject.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			ISceneObject* SceneManager::createSceneObject(const char* name)
			{
				return nullptr;
			}

			ISceneObject* SceneManager::getSceneObject(const char* name)
			{
				return nullptr;
			}

			void SceneManager::destroySceneObject(const char* name)
			{

			}

			void SceneManager::destroySceneObject(ISceneObject* sceneObject)
			{

			}

			void SceneManager::clear()
			{

			}
		}
	}
}