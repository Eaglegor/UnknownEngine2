#pragma once

#include "IMessageType.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Messages
		{
			template<typename T>
			class MessageType : public IMessageType
			{
				public:
					// Only template specializations are allowed
					MessageType() = delete;
			};
		}
	}
}
