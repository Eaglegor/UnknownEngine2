#pragma once

#include <utility>

namespace UnknownEngine
{
	namespace Utils
	{
		namespace Common
		{
			template<typename T, typename... CtorArgs>
			class Singleton
			{
				public:
					static T* createInstance ( CtorArgs && ... args )
					{
						if ( instance ) return instance;
						instance = new T ( std::forward<CtorArgs> ( args )... );
						return instance;
					}

					static T* getSingleton()
					{
						return instance;
					}

					static void destroyInstance()
					{
						delete instance;
						instance = nullptr;
					}

				protected:
					Singleton() {}

					virtual ~Singleton() {}

					explicit Singleton ( const Singleton& rhs ) = delete;

					static T* instance;
			};
		}
	} /* namespace Core */
} /* namespace UnknownEngine */
