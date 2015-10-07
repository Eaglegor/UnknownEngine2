#include <unordered_map>

namespace UnknownEngine
{
	namespace Utils
	{
		namespace DataStructures
		{
			template<typename K, typename V>
			using UnsafeUnorderedMap = std::unordered_map<K, V>;
		}
	}
}