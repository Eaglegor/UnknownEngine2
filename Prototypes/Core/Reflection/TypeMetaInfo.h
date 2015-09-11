class ITypeMetaInfo
{
	public:
		virtual const char* getTypeName() = 0;
		virtual size_t getSize() = 0;
		virtual size_t getTypeId() = 0;
		
		virtual ~ITypeMetaInfo(){}
};

size_t getNextTypeId();

template<typename T>
class TypeMetaInfoBase : public ITypeMetaInfo
{
	public:
		TypeMetaInfoBase(const char* type_name, size_t size):
		type_name(type_name),
		size(type_size)
		{
			static int new_type_id = getNextTypeId();
			this->type_id = new_type_id;
		}
	
		virtual const char* getTypeName()
		{
			return type_name.c_str();
		}
		
		virtual size_t getSize()
		{
			return type_size;
		}
		
		virtual size_t getTypeId()
		{
			return type_id;
		}
	
		template<typename Type>
		void addProperty(const char* name, PropertyGetter getter, PropertySetter setter)
		{
			properties->emplace(name, new Property<Type>(getter, setter));
		}
		
		template<typename Type>
		Property<Type>* getProperty(const char* name)
		{
			auto iter = properties.find(name);
			if(iter == properties.end()) return nullptr;
			else return iter->second;
		}
	
	private:
		std::unordered_map<std::string, IProperty*> properties;
	
		std::string type_name;
		size_t type_size;
		size_t type_id;
};

template<typename T>
class TypeMetaInfo : public TypeMetaInfoBase<T>
{
	public:
		TypeMetaInfo() = delete;
};