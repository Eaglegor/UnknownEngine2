#include <unordered_map>
#include <iostream>


class Methods{};
class Properties{};

enum class ClassType
{
	PRIMITIVE,
	CLASS,
	ARRAY
};

class IMetaType
{
	public:
		virtual ClassType getClassType() const = 0;
		virtual size_t getTypeId() const = 0;
		virtual size_t getSize() const = 0;
		virtual const char* getTypeName() const = 0;
		virtual const Methods& getMethods() const = 0;
		virtual const Properties& getProperties() const = 0;
		virtual const IMetaType* getBaseType() const = 0;
		virtual bool isDerivedFrom(IMetaType* type) const = 0;
};


class TypeIdManager
{
	public:
		int getTypeId(const char* name)
		{
			auto iter = mappings.find(name);
			if(iter == mappings.end())
			{
				int val = counter++;
				mappings.emplace(name, val);
				return val;
			}
			return iter->second;
		}
		
	private:
		int counter = 0;
		std::unordered_map<std::string, size_t> mappings;
};

 TypeIdManager type_id_manager;

class A
{
	public:
		int intProperty;
};

class B
{
	public:
		float floatProperty;
};

class C : public B
{
	public:
		int int2Property;
};

class D : public C
{
	public:
		int int3Property;
};

template<typename T>
class MetaType
{
	virtual ~MetaType(){}
	MetaType() = delete;
};


class IProperty
{
	public:
		virtual const IMetaType& getType() = 0;
		virtual void* getRawData() = 0;
		
		virtual void setValue(const IProperty* property) = 0;
};

template<typename T>
class Property
{
	public:
		Property(IProperty* property):
		property(property)
		{
		}
		
		void setValue(const T &val)
		{
			T& var = *static_cast<T*>(property->getRawData());
			var = val;
		}
		
		T getValue()
		{
			const T& var = *static_cast<T*>(property->getRawData());
			return var;
		}
		
		void setValue(const IProperty* property);
		
	private:
		IProperty* property;
};

template<typename T>
Property<T> property_cast(IProperty* property)
{
	const IMetaType& meta_type = property->getType();
	MetaType<T> desired_type;
	if(meta_type == desired_type || meta_type.isDerivedFrom(desired_type))
	{
		return Property<T>(property);
	}
}

template<typename T>
void Property<T>::setValue(const IProperty* property)
{
	Property<T> donor = property_cast<T>(property);
	setValue(donor.getValue());
}

template<typename T>
class BaseMetaType : public IMetaType
{
	public:
		virtual ClassType getClassType() const override{return type;}
		virtual size_t getTypeId() const override{return type_id;}
		virtual size_t getSize() const override{return size;}
		virtual const char* getTypeName() const override{return type_name.c_str();}
		virtual const Methods& getMethods() const override{return methods;}
		virtual const Properties& getProperties() const override{return properties;}
		virtual const IMetaType* getBaseType() const override{return nullptr;}
		virtual bool isDerivedFrom(IMetaType *type) const override{return false;}
		
	protected:
		BaseMetaType(const char* name, ClassType type)
		{
			static size_t tid = type_id_manager.getTypeId(name);
			this->type_id = tid;
			this->type_name = name;
			this->size = sizeof(T);
			this->type = type;
		}
		
	private:
		size_t type_id;
		std::string type_name;
		size_t size;
		ClassType type;
		Methods methods;
		Properties properties;
};

template<typename T, typename BaseClass>
class BaseDerivedMetaType : public BaseMetaType<T>
{
	static_assert(std::is_base_of<BaseClass, T>::value, "T must derive from BaseClass");
	
	public:
		virtual const IMetaType* getBaseType() const override{return base_class_meta_type;}
		virtual bool isDerivedFrom(IMetaType *base_type) const override{return getBaseType()->getTypeId() == base_type->getTypeId();}
		
	protected:
		BaseDerivedMetaType(const char* name, ClassType type):
		BaseMetaType<T>(name, type)
		{
			base_class_meta_type = new MetaType<BaseClass>();
		}
		
		~BaseDerivedMetaType()
		{
			delete base_class_meta_type;
		}
		
	private:
		MetaType<BaseClass>* base_class_meta_type;
};

template<>
class MetaType<int> : public BaseMetaType<int>
{
	public:
		MetaType():BaseMetaType("int", ClassType::PRIMITIVE){}
};

template<>
class MetaType<float> : public BaseMetaType<float>
{
	public:
		MetaType():BaseMetaType("float", ClassType::PRIMITIVE){}
};

template<>
class MetaType<A> : public BaseMetaType<A>
{
	public:
		MetaType():BaseMetaType("A", ClassType::CLASS){}
};

template<>
class MetaType<B> : public BaseMetaType<B>
{
	public:
		MetaType():BaseMetaType("B", ClassType::CLASS){}
};

template<>
class MetaType<C> : public BaseDerivedMetaType<C, B>
{
	public:
		MetaType():BaseDerivedMetaType("C", ClassType::CLASS){}
};

template<>
class MetaType<D> : public BaseDerivedMetaType<D, C>
{
	public:
		MetaType():BaseDerivedMetaType("D", ClassType::CLASS){}
};

int main()
{
	MetaType<int> intMetaType;
	std::cout << intMetaType.getTypeName() << " = " << intMetaType.getTypeId() << std::endl;
	
	MetaType<float> floatMetaType;
	std::cout << floatMetaType.getTypeName() << " = " << floatMetaType.getTypeId() << std::endl;
	
	MetaType<float> floatMetaType2;
	std::cout << floatMetaType2.getTypeName() << " = " << floatMetaType2.getTypeId() << std::endl;
	
	MetaType<B> bmt;
	std::cout << bmt.getTypeName() << " = " << bmt.getTypeId() << std::endl;
	
	MetaType<C> bmt2;
	std::cout << bmt2.getTypeName() << " = " << bmt2.getTypeId() << " derived from " << bmt2.getBaseType()->getTypeName() << std::endl;

	std::cout << "Inheritance tree: " << std::endl;
	
	MetaType<D> dmt;
	const IMetaType* dmtp = &dmt;
	do
	{
		std::cout << dmtp->getTypeName() << " <- ";
		dmtp = dmtp->getBaseType();
	}
	while(dmtp != nullptr);
	std::cout << "END" << std::endl;
	
	return 0;
}