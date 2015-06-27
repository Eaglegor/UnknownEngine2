#pragma once

#include <Utils/Common/Singleton.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Scene
		{
			class ISceneObject;

			class SceneManager : public Utils::Common::Singleton < SceneManager >
			{
			public:
				virtual ~SceneManager(){}

				ISceneObject* createSceneObject(const char* name);
				ISceneObject* getSceneObject(const char* name);
				void destroySceneObject(const char* name);
				void destroySceneObject(ISceneObject* sceneObject);

				void clear();
			};
		}
	}
}