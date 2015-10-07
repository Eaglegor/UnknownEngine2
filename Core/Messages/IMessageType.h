#pragma once

#include <Core/Reflection/IMetaType.h>

namespace UnknownEngine
{
	namespace Core
	{
		namespace Messages
		{
			using Reflection::IMetaType;
			using Reflection::ReflectableObjectType;

			enum class MessagePurpose
			{
				EVENT,
				REQUEST
			};

			class IMessageType : public IMetaType
			{
			public:
				virtual MessagePurpose getPurpose() = 0;
			};
		}
	}
}
