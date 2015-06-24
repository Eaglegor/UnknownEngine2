#pragma once

namespace UnknownEngine
{
	namespace Core
	{
		namespace Tasks
		{
			class ITask
			{
				public:
					virtual ~ITask(){}
					virtual void operator() = 0;
			};
		}
	}
}
