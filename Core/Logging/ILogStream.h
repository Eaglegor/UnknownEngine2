#pragma once

#include "ILogRecord.h"

namespace UnknownEngine
{
	namespace Core
	{
		namespace Logging
		{
			class ILogStream
			{
				public:
					virtual ~ILogStream(){}
					virtual ILogStream& operator<<(const ILogRecord& record) = 0;
			};
		}
	}
}
