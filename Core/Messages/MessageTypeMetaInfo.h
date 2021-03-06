#pragma once

#include <MessageSystem/IMessageType.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Messages
		{
			template<typename T>
			class MessageType : public IMessageTypeMetaInfo
			{
				public:
					// Only template specializations are allowed
					MessageTypeMetaInfo() = delete;
			};
		}
	}
}
