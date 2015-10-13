#include <unordered_map>
#include <iostream>

class Methods {
};

class Properties {
};

class Constructors {
};

class Destructor {
};

enum class ClassType {
		PRIMITIVE,
		CLASS,
		ARRAY
};

class IMetaType {
	public:
		virtual ClassType getClassType() const = 0;

		virtual size_t getTypeId() const = 0;

		virtual size_t getSize() const = 0;

		virtual const char *getTypeName() const = 0;

		virtual const Constructors &getConstructors() const = 0;

		virtual const Destructor& getDestructor() const = 0;

		virtual const Methods &getMethods() const = 0;

		virtual const Properties &getProperties() const = 0;

		virtual const IMetaType *getBaseType() const = 0;

		virtual bool isDerivedFrom(IMetaType *type) const = 0;

		bool operator==(const IMetaType &rhs) {
			return getTypeId() == rhs.getTypeId();
		}

		bool operator!=(const IMetaType &rhs) {
			return !(*this == rhs);
		}
};


class TypeIdManager {
	public:
		size_t getTypeId(const char *name) {
			auto iter = mappings.find(name);
			if (iter == mappings.end()) {
				int val = counter++;
				mappings.emplace(name, val);
				return val;
			}
			return iter->second;
		}

	private:
		size_t counter = 0;
		std::unordered_map<std::string, size_t> mappings;
};

TypeIdManager type_id_manager;

class A {
	public:
		int intProperty;
};

class B {
	public:
		float floatProperty;
};

class C : public B {
	public:
		int int2Property;
};

class D : public C {
	public:
		int int3Property;
};

template<typename T>
class MetaType : public IMetaType {
		virtual ~ MetaType() {
		}

		MetaType() = delete;
};

class ObjectRefHolder {
	public:

		virtual ~ ObjectRefHolder() {
		}

		template<typename T>
		T *cast() {
			MetaType<T> type;
			if (type != *getType()) {
				std::cout << "Bad type" << std::endl;
				return nullptr;
			}
			return static_cast < T * >(getPointer());
		}

	protected:
		ObjectRefHolder() {
		}

	private:
		virtual IMetaType *getType() const = 0;

		virtual void *getPointer() = 0;
};

template<typename T>
class TypedObjectHolder : public ObjectRefHolder {
	public:
		TypedObjectHolder(T *ptr) :
				pointer(ptr),
				type(new MetaType<T>()) {
		}

		~TypedObjectHolder() {
			delete type;
		}

	private:
		virtual void *getPointer() override {
			return pointer;
		}

		virtual IMetaType *getType() const override {
			return type;
		}

		MetaType<T> *type;
		T *pointer;

};

class Property {
	public:
		template<typename Cls, typename T>
		void setValue(Cls *cls, const T &value) {
			TypedObjectHolder<Cls> objholder(cls);
			TypedObjectHolder<T> valueHolder(value);
		}

		virtual IMetaType *getType() = 0;

	private:
		virtual void setValueImpl(ObjectRefHolder &object_holder, ObjectRefHolder &value_holder) = 0;
};

template<typename T>
class BaseMetaType : public IMetaType {
	public:
		virtual ClassType getClassType() const override {
			return type;
		}

		virtual size_t getTypeId() const override {
			return type_id;
		}

		virtual size_t getSize() const override {
			return size;
		}

		virtual const char *getTypeName() const override {
			return type_name.c_str();
		}


		virtual const Constructors &getConstructors() const
		{
			return constructors;
		}

		virtual const Destructor &getDestructor() const
		{
			return destructor;
		}

		virtual const Methods &getMethods() const override {
			return methods;
		}

		virtual const Properties &getProperties() const override {
			return properties;
		}

		virtual const IMetaType *getBaseType() const override {
			return nullptr;
		}

		virtual bool isDerivedFrom(IMetaType *type) const override {
			return false;
		}

	protected:
		BaseMetaType(const char *name, ClassType type) {
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
		Constructors constructors;
		Destructor destructor;
};

template<typename T, typename BaseClass>
class BaseDerivedMetaType : public BaseMetaType<T> {
		static_assert(std::is_base_of<BaseClass, T>::value, "T must derive from BaseClass");

	public:
		virtual const IMetaType *getBaseType() const override {
			return base_class_meta_type;
		}

		virtual bool isDerivedFrom(IMetaType *base_type) const override {
			return getBaseType()->getTypeId() == base_type->getTypeId();
		}

	protected:
		BaseDerivedMetaType(const char *name, ClassType type) :
				BaseMetaType<T>(name, type) {
			base_class_meta_type = new MetaType<BaseClass>();
		}

		~BaseDerivedMetaType() {
			delete base_class_meta_type;
		}

	private:
		MetaType<BaseClass> *base_class_meta_type;
};

template<>
class MetaType<int> : public BaseMetaType<int> {
	public:
		MetaType() :
				BaseMetaType("int", ClassType::PRIMITIVE) {
		}
};

template<>
class MetaType<float> : public BaseMetaType<float> {
	public:
		MetaType() :
				BaseMetaType("float", ClassType::PRIMITIVE) {
		}
};

template<>
class MetaType<A> : public BaseMetaType<A> {
	public:
		MetaType() :
				BaseMetaType("A", ClassType::CLASS) {
		}
};

template<>
class MetaType<B> : public BaseMetaType<B> {
	public:
		MetaType() :
				BaseMetaType("B", ClassType::CLASS) {
		}
};

template<>
class MetaType<C> : public BaseDerivedMetaType<C, B> {
	public:
		MetaType() :
				BaseDerivedMetaType("C", ClassType::CLASS) {
		}
};

template<>
class MetaType<D> : public BaseDerivedMetaType<D, C> {
	public:
		MetaType() :
				BaseDerivedMetaType("D", ClassType::CLASS) {
		}
};

int main() {
	MetaType<int> intMetaType;
	std::cout << intMetaType.getTypeName() << " = " << intMetaType.getTypeId() << std::endl;

	MetaType<float> floatMetaType;
	std::cout << floatMetaType.getTypeName() << " = " << floatMetaType.getTypeId() << std::endl;

	MetaType<float> floatMetaType2;
	std::cout << floatMetaType2.getTypeName() << " = " << floatMetaType2.getTypeId() << std::endl;

	MetaType<B> bmt;
	std::cout << bmt.getTypeName() << " = " << bmt.getTypeId() << std::endl;

	MetaType<C> bmt2;
	std::cout << bmt2.getTypeName() << " = " << bmt2.getTypeId() << " derived from " << bmt2.
			getBaseType()->getTypeName() << std::endl;

	std::cout << "Inheritance tree: " << std::endl;

	MetaType<D> dmt;
	const IMetaType *dmtp = &dmt;
	do {
		std::cout << dmtp->getTypeName() << " <- ";
		dmtp = dmtp->getBaseType();
	}
	while (dmtp != nullptr);
	std::cout << "END" << std::endl;

	return 0;
}
