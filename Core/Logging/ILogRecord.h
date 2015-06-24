#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Logging
		{
			class ILogRecord
			{
				public:
					virtual ~ILogRecord(){}
					virtual std::string toString() const = 0;
			};
		}
	}
}
