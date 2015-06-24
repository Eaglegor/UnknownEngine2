#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace State
		{
			class Synchronizable
			{
				public:
					virtual ~Synchronizable(){}
					virtual void synchronize() = 0;
			};
		}
	}
}
