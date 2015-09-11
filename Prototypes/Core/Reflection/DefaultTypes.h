#include "TypeMetaInfo.h"

template<>
class TypeMetaInfo<int> : public TypeMetaInfoBase<int>
{
	public:
		TypeMetaInfo():TypeMetaInfoBase<TestClass>("int", sizeof(int)){}
}

template<>
class TypeMetaInfo<float> : public TypeMetaInfoBase<float>
{
	public:
		TypeMetaInfo():TypeMetaInfoBase<TestClass>("float", sizeof(float)){}
}

template<>
class TypeMetaInfo<char> : public TypeMetaInfoBase<char>
{
	public:
		TypeMetaInfo():TypeMetaInfoBase<TestClass>("char", sizeof(char)){}
}