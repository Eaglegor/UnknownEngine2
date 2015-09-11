class IProperty
{
	public:
		virtual ITypeMetaInfo* getType() = 0;
		virtual ~IProperty(){}
};

class PropertyGetter;
class PropertySetter;

template<typename Type>
class PropertyBase : public IProperty
{
	public:
		template<typename T>
		virtual setValue(const T& value)
		{
			findSetter<T>()->setValue(value);
		}
		
		template<typename T>
		virtual T getValue()
		{
			return findGetter<T>()->getValue();
		}
		
	private:
		template<typename T>
		PropertyGetter findGetter();
		
		template<typename T>
		PropertySetter findSetter();
};