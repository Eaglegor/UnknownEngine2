#include <iostream>
#include <unordered_map>
#include <functional>

class A
{
public:
	void simpleMethod()
	{
		std::cout << "A::simpleMethod() called" << std::endl;
	}
	
	void simplePMethod(int a)
	{
		std::cout << "A::simplePMethod() called. a = " << a << std::endl;
	}
	
	float simpleRMethod()
	{
		std::cout << "A::simpleRMethod() called" << std::endl;
		return 0.0f;
	}
	
	char simplePRMethod(char c)
	{
		std::cout << "A::simplePRMethod() called" << std::endl;
		return c;
	}
	
	void setA(const int& a)
	{
		this->a = a;
	}
	
	int getA()
	{
		return a;
	}
	
	void setB(const float& b)
	{
		this->b = b;
	}
	
	float getB()
	{
		return b;
	}
	
private:
	int a;
	float b;
};

class IProperty;
class IFunction;

class ITypeMetaInfo
{
public:
	virtual ~ITypeMetaInfo(){}
	virtual const char* getName() = 0;
	
	virtual std::unordered_map<std::string, IProperty*>& getProperties() = 0;
	virtual std::unordered_map<std::string, IFunction*>& getMethods() = 0;
	
	virtual IProperty* getProperty(const char* name) = 0;
	virtual IFunction* getMethod(const char* name) = 0;
};

class BaseTypeMetaInfo : public ITypeMetaInfo
{
public:
		virtual IFunction* getMethod ( const char* name )
		{
			return nullptr;
		}
		
		virtual std::unordered_map< std::string, IFunction* >& getMethods()
		{
			return methods;
		}
		
		virtual IProperty* getProperty ( const char* name )
		{
			auto iter = properties.find(name);
			if(iter == properties.end()) return nullptr;
			return iter->second;
		}
		
		virtual std::unordered_map< std::string, IProperty* >& getProperties()
		{
			return properties;
		}
	
protected:
	void addProperty(const char* name, IProperty* property)
	{
		properties.emplace(name, property);
	}
	
	void addMethod(const char* name, IFunction* method)
	{
		methods.emplace(name, method);
	}
	
private:
	std::unordered_map<std::string, IProperty*> properties;
	std::unordered_map<std::string, IFunction*> methods;
};

template<typename Class, typename T>
class Property;


template<typename T>
class TypeMetaInfo : public ITypeMetaInfo
{
public:
	TypeMetaInfo() = delete;
	
	static const char* staticGetName(){return "UNKNOWN_TYPE";}
};

class IProperty
{
public:
	virtual ~IProperty(){}
	virtual ITypeMetaInfo* getTypeMetaInfo() = 0;
	
	template<typename Class, typename T>
	Property<Class, T>* cast()
	{
		ITypeMetaInfo* meta_info = getTypeMetaInfo();
		if(TypeMetaInfo<T>::staticGetName() == meta_info->getName())
		{
			return static_cast<Property<Class, T>*>(this);
		}
		return nullptr;
	}
};

template<typename Class, typename T>
class Property : public IProperty
{
public:
	Property(Class *owner, std::function<void(Class &, const T&)> setter, std::function<T (Class &)> getter):
	setter(setter),
	getter(getter),
	owner(owner),
	type_meta_info(owner)
	{}
	
	ITypeMetaInfo* getTypeMetaInfo(){return &type_meta_info;}
	
	void setValue(const T& val)
	{
		setter(*owner, val);
	}
	
	T getValue()
	{
		return getter(*owner);
	}
	
	IProperty* getField(const char* name)
	{
		return type_meta_info->getProperty(name);
	}
	
private:
	std::function<void (Class &, const T&)> setter;
	std::function<T (Class&)> getter;
	Class *owner;
	
	TypeMetaInfo<T> type_meta_info;
};

template<>
class TypeMetaInfo<A> : public BaseTypeMetaInfo
{
public:
	TypeMetaInfo(A* object):
	object(object),
	prop_a(object, [](A& obj, const int& v){obj.setA(v);}, [](A& obj){return obj.getA();}),
	prop_b(object, [](A& obj, const float& v){obj.setB(v);}, [](A& obj){return obj.getB();})
	{
		addProperty("a", prop_a);
		addProperty("b", prop_b);
	}
	
	const char* getName(){return staticGetName();}
	static const char* staticGetName(){return "A";}
	
private:
	A* object;
	Property<A, int> prop_a;
	Property<A, float> prop_b;
};


int main()
{
	
	
	return 0;
}