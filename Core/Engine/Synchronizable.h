#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		class Synchronizable
		{
			public:
				virtual ~Synchronizable(){};
				virtual void synchronize() = 0;
		};
	}
}
