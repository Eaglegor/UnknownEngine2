#pragma once

#include <MessageSystem/IMessageTypeMetaInfo.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Messages
		{
			template<typename T>
			class MessageTypeMetaInfo : public IMessageTypeMetaInfo
			{
				public:
					// Only template specializations are allowed
					MessageTypeMetaInfo() = delete;
			};
		}
	}
}
