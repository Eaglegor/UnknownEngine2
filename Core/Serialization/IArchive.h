#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Serialization
		{
			class Serializable;

			struct SerializationResult
			{
				bool success;
			};

			struct DeserializationResult
			{
				bool success;
			};

			class IArchive
			{
				public:
					virtual ~IArchive(){}
					SerializationResult pack(Serializable &object);
					DeserializationResult unpack(Serializable &out_object);
			};
		}
	}
}
