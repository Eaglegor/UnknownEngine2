#include <unordered_map>
#include <iostream>
#include <chrono>
#include <array>
#include <tuple>

class Methods {
};

class Field;

class Fields {
	public:
		void addField(const char *name, Field *field) {
			fields.emplace(name, field);
		}

		const Field *getField(const char *name) const {
			auto iter = fields.find(name);
			if (iter == fields.end()) return nullptr;
			return iter->second;
		}

	private:
		std::unordered_map<std::string, Field *> fields;
};

class Argument {
};

template<typename T>
class TypedArgument
{

};

class Arguments {
	public:
		template<typename Arg, typename... Args>
		void initialize()
		{
			std::cout << "Creating arguments" << std::endl;
			ArgumentPusher<Arg, Args...>().push();
		}


	private:
		template<typename Arg, typename... Args>
		struct ArgumentPusher
		{
			void push()
			{
				std::cout << "Pushing argument" << std::endl;
				ArgumentPusher<Args...>().push();
			}
		};

		template<typename Arg>
		struct ArgumentPusher<Arg>
		{
			void push()
			{
				std::cout << "Pushing last argument" << std::endl;
			}
		};
};

class ArgumentBindings {
};

class Constructor {
	public:
		virtual void construct(void *memory) const = 0;

		virtual void construct(void *memory, const ArgumentBindings &arguments) const = 0;

		virtual const Arguments &getArguments() const = 0;
};

template<typename Cls>
class DefaultConstructor : public Constructor {
	public:
		DefaultConstructor() {

		}

		virtual void construct(void *memory) const override {

		}

		virtual void construct(void *memory, const ArgumentBindings &arguments) const override { }

		virtual const Arguments &getArguments() const override { return arguments; }

	private:
		Arguments arguments;
};

template<typename Cls, typename Arg, typename... Args>
class ParametrizedConstructor : public Constructor {
	public:
		ParametrizedConstructor() {
			std::cout << "Constructing parametrized constructor" << std::endl;
			arguments.initialize<Arg, Args...>();
		}

		virtual void construct(void *memory) const override {

		}

		virtual void construct(void *memory, const ArgumentBindings &arguments) const override { }

		virtual const Arguments &getArguments() const override { return arguments; }

	private:
		Arguments arguments;
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

		virtual const Destructor &getDestructor() const = 0;

		virtual const Methods &getMethods() const = 0;

		virtual const Fields &getFields() const = 0;

		virtual const IMetaType *getBaseType() const = 0;

		virtual bool isDerivedFrom(IMetaType *type) const = 0;

		bool operator==(const IMetaType &rhs) {
			return getTypeId() == rhs.getTypeId();
		}

		bool operator!=(const IMetaType &rhs) {
			return !(*this == rhs);
		}
};

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

		template<typename T>
		MetaType<T> &getMetaType() {
			static MetaType<T> meta_type;
			return meta_type;
		}

	private:
		size_t counter = 0;
		std::unordered_map<std::string, size_t> mappings;
};

TypeIdManager type_id_manager;

class ObjectRefHolder {
	public:

		virtual ~ ObjectRefHolder() {
		}

		template<typename T>
		T *cast() {
			MetaType<T> &type = type_id_manager.getMetaType<T>();
			if (type != *getType()) {
				std::cout << "Bad type" << std::endl;
				return nullptr;
			}
			return static_cast < T * >(getPointer());
		}

		template<typename T>
		void set(T *ptr) {
			MetaType<T> &type = type_id_manager.getMetaType<T>();
			if (type != *getType()) {
				std::cout << "Bad type" << std::endl;
				return;
			}
			setPointer(ptr);
		}

	protected:
		ObjectRefHolder() {
		}

	private:
		virtual const IMetaType *getType() const = 0;

		virtual void *getPointer() = 0;

		virtual void setPointer(void *ptr) = 0;
};

template<typename T>
class TypedObjectHolder : public ObjectRefHolder {
	public:
		TypedObjectHolder() :
				pointer(nullptr),
				type(type_id_manager.getMetaType<T>()) {
		}

		TypedObjectHolder(T *ptr) :
				pointer(ptr),
				type(type_id_manager.getMetaType<T>()) {
		}

		~TypedObjectHolder() {
			//delete type;
		}

	private:
		virtual void *getPointer() override {
			return pointer;
		}

		virtual void setPointer(void *ptr) override {
			pointer = static_cast<T *>(ptr);
		}

		virtual const IMetaType *getType() const override {
			return &type;
		}

		MetaType<T> &type;
		T *pointer;
};

class Field {
	public:
		virtual ~Field() { };

		template<typename T, typename Cls>
		T &ref(Cls *cls) const {
			return *static_cast<T *>(getPointer(cls));
		}

		template<typename Cls, typename T>
		void setValue(Cls *cls, const T &value) const {
			if (!typeMatches(type_id_manager.getMetaType<Cls>(), type_id_manager.getMetaType<T>())) {
				std::cout << "BadType" << std::endl;
				return;
			}
			setValueImpl(cls, &value);
		}

		template<typename Cls, typename T>
		const T &getValue(Cls *cls) const {
			if (!typeMatches(type_id_manager.getMetaType<Cls>(), type_id_manager.getMetaType<T>())) {
				std::cout << "BadType" << std::endl;
				throw std::invalid_argument("bad type");
			}
			void *value;
			getValueImpl(cls, &value);
			return *reinterpret_cast<T *>(value);
		}

		virtual IMetaType *getType() const = 0;

		virtual const char *getName() = 0;

	protected:
		Field() { }

	private:

		virtual bool typeMatches(const IMetaType &cls_type, const IMetaType &value_type) const = 0;

		virtual void setValueImpl(void *cls, const void *value) const = 0;

		virtual void getValueImpl(void *cls, void **value) const = 0;

		virtual void *getPointer(void *cls) const = 0;
};

template<typename Cls, typename T>
class TypedField : public Field {
	public:
		TypedField(const char *name, T Cls::*ptr) :
				name(name),
				field_ptr(ptr),
				type(type_id_manager.getMetaType<T>()) {
		}

		IMetaType *getType() const override {
			return &type;
		}

		const char *getName() override {
			return name.c_str();
		}

	private:
		void setValueImpl(void *cls, const void *value) const override {
			Cls *clsptr = static_cast<Cls *>(cls);
			const T *val = static_cast<const T *>(value);
			clsptr->*field_ptr = *val;
		}

		void getValueImpl(void *cls, void **value) const override {
			Cls *clsptr = static_cast<Cls *>(cls);
			*value = &(clsptr->*field_ptr);
		}

		void *getPointer(void *cls) const override {
			Cls *clsptr = static_cast<Cls *>(cls);
			return &(clsptr->*field_ptr);
		}

		virtual bool typeMatches(const IMetaType &cls_type, const IMetaType &value_type) const {
			return type_id_manager.getMetaType<Cls>() == cls_type && type_id_manager.getMetaType<T>() == value_type;
		}

		MetaType<T> &type;
		T Cls::*field_ptr;
		std::string name;
};

template<typename Cls, typename T>
class TypedBoundField {
	public:
		TypedBoundField(const Field *field, Cls *cls) :
				t(field->ref<T>(cls)) {
		}

		TypedBoundField &operator=(const T &rhs) {
			t = rhs;
			return *this;
		}

		void setValue(const T &val) {
			t = val;
		}

	private:
		T &t;
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


		virtual const Constructors &getConstructors() const {
			return constructors;
		}

		virtual const Destructor &getDestructor() const {
			return destructor;
		}

		virtual const Methods &getMethods() const override {
			return methods;
		}

		virtual const Fields &getFields() const override {
			return fields;
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

		void addField(const char *name, Field *field) {
			fields.addField(name, field);
		}

	private:
		size_t type_id;
		std::string type_name;
		size_t size;
		ClassType type;
		Methods methods;
		Fields fields;
		Constructors constructors;
		Destructor destructor;
};

template<typename T, typename BaseClass>
class BaseDerivedMetaType : public BaseMetaType<T> {
		static_assert(std::is_base_of<BaseClass, T>::value, "T must derive from BaseClass");

	public:
		virtual const IMetaType *getBaseType() const override {
			return &base_class_meta_type;
		}

		virtual bool isDerivedFrom(IMetaType *base_type) const override {
			return getBaseType()->getTypeId() == base_type->getTypeId();
		}

	protected:
		BaseDerivedMetaType(const char *name, ClassType type) :
				BaseMetaType<T>(name, type),
				base_class_meta_type(type_id_manager.getMetaType<BaseClass>()) {

		}

	private:
		MetaType<BaseClass> &base_class_meta_type;
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
				BaseMetaType("A", ClassType::CLASS),
				intProperty("intProperty", &A::intProperty) {
			addField("intProperty", &intProperty);
		}

	private:
		TypedField<A, int> intProperty;
};

template<>
class MetaType<B> : public BaseMetaType<B> {
	public:
		MetaType() :
				BaseMetaType("B", ClassType::CLASS),
				floatProperty("floatProperty", &B::floatProperty) {
			addField("floatProperty", &floatProperty);
		}

	private:
		TypedField<B, float> floatProperty;
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
	/*MetaType<int> intMetaType;
	std::cout << intMetaType.getTypeName() << " = " << intMetaType.getTypeId() << std::endl;

	MetaType<float> floatMetaType;
	std::cout << floatMetaType.getTypeName() << " = " << floatMetaType.getTypeId() << std::endl;

	MetaType<float> floatMetaType2;
	std::cout << floatMetaType2.getTypeName() << " = " << floatMetaType2.getTypeId() << std::endl;
*/
	DefaultConstructor<A> tc1;

	ParametrizedConstructor<A, int, int, float, std::string> tc2;
/*

	A a;

	std::chrono::time_point<std::chrono::system_clock> start, end;

	A *pa = &a;

	start = std::chrono::system_clock::now();

	for (int i = 0; i < 1000000; ++i) {
		pa->intProperty = i;
	}

	end = std::chrono::system_clock::now();

	std::cout << "Plain: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000000.0f <<
	std::endl;

	MetaType<A> &amt = type_id_manager.getMetaType<A>();
	const Field *f = amt.getFields().getField("intProperty");

	TypedBoundField<A, int> bound_field(f, &a);

	int &ia = f->ref<int, A>(&a);

	start = std::chrono::system_clock::now();

	for (int i = 0; i < 1000000; ++i) {
		//f->setValue(&a, i);
		bound_field.setValue(i);
	}

	end = std::chrono::system_clock::now();

	std::cout << "Reflection: " <<
	std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000000.0f << std::endl;

	std::cout << f->getValue<A, int>(&a) << std::endl;

	B b;

	MetaType<B> bmt;
	std::cout << bmt.getTypeName() << " = " << bmt.getTypeId() << std::endl;

	const Field *ff = bmt.getFields().getField("floatProperty");
	ff->setValue(&b, 3.14f);

	std::cout << ff->getValue<B, float>(&b) << std::endl;

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

	getchar();
*/
	return 0;
}
