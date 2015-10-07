#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Messages
		{
			class IMessageType;

			class IMessage
			{
				public:
					virtual ~IMessage(){}
					virtual IMessageType* getType() = 0;
			};
		}
	}
}
