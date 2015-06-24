#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Messages
		{
			class IMessageTypeMetaInfo
			{
				public:
					virtual ~IMessageTypeMetaInfo(){}
					virtual const char* getName() = 0;
			};
		}
	}
}
