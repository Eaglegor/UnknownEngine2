#include <iostream>
#include <TypeMetaInfo.h>

class TestClass
{
	public:
		int getP1()
		{
			return p1;
		}
		
		void setP1(const int &val)
		{
			p1 = val;
		}
		
		float getP2()
		{
			return p2;
		}
		
		void setP2(const float &val)
		{
			p2 = val;
		}
		
		const char* getP3()
		{
			return p3.c_str();
		}
		
		void setP3(const char* val)
		{
			p3 = val;
		}
		
	private:
		int p1;
		float p2;
		std::string p3;
};

template<>
class TypeMetaInfo<TestClass> : public TypeMetaInfoBase<TestClass>
{
	public:
		TypeMetaInfo():TypeMetaInfoBase<TestClass>("TestClass", sizeof(TestClass)){
			addProperty("p1", &TestClass::getP1, &TestClass::setP1);
			addProperty("p2", &TestClass::getP2, &TestClass::setP2);
			addProperty("p3", &TestClass::getP3, &TestClass::setP3);
		}
		
		template<typename... Args>
		void construct(void* memory, Args... &&args)
		{
			new (memory) TestClass(std::forward<Args>(args)...);
		}
		
		void destruct(void* memory)
		{
			delete static_cast<TestClass>(memory);
		}
}
