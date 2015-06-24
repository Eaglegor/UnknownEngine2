#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Messages
		{
			class IMessage
			{
				public:
					virtual ~IMessage(){}
					virtual IMessageTypeMetaInfo* getTypeInfo();
			};
		}
	}
}
