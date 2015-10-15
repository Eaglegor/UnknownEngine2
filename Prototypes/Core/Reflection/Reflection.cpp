#include <unordered_map>
#include <iostream>
#include <chrono>
#include <array>
#include <tuple>
#include <functional>
#include <vector>

class Constructors;

class Destructor;

class Methods;

class Fields;

enum class ClassType {
		PRIMITIVE,
		CLASS,
		ARRAY,
		VOID_TYPE
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

		virtual bool hasBaseType() const = 0;

		virtual const IMetaType &getBaseType() const = 0;

		virtual bool isDerivedFrom(const IMetaType &type) const = 0;

		bool operator==(const IMetaType &rhs) const {
			return getTypeId() == rhs.getTypeId();
		}

		bool operator!=(const IMetaType &rhs) const {
			return !(*this == rhs);
		}
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
				size_t val = counter++;
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

class Methods {
};

class Field;

class IMetaType;

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
	public:
		Argument(const IMetaType &type) :
				default_value_storage(nullptr),
				type(type) { }

		~Argument() {
			if (default_value_storage) delete_closure(default_value_storage); // Deallocate storage memory ;
		}

		Argument(const Argument &rhs) :
				default_value_storage(nullptr),
				type(rhs.getType()) {
			if (rhs.hasBoundValue()) {
				rhs.copyDefaultValue(*this);
			}
		}

		const IMetaType &getType() const { return type; }

		bool hasBoundValue() const {
			return default_value_storage != nullptr;
		}

		template<typename T>
		T *getBoundValuePtr() const {
			if (type_id_manager.getMetaType<T>() != type)
			{
				std::cout << "Incorrect value type requested" << std::endl;
				std::cout << "Expected: " << type.getTypeName() << " but passed: " << type_id_manager.getMetaType<T>().getTypeName() << std::endl;
				return nullptr;
			}
			return static_cast<T *>(default_value_storage);
		}

		template<typename T>
		void bindValue(const T &value) {
			if(type_id_manager.getMetaType<T>() != type) {
				std::cout << "Incorrect value type passed to be bound" << std::endl;
				std::cout << "Expected: " << type.getTypeName() << " but passed: " << type_id_manager.getMetaType<T>().getTypeName() << std::endl;
				return;
			}
			default_value_storage = new T(value);
			delete_closure = [](void *obj) { delete static_cast<T *>(obj); };
			copy_default_value_closure = [this](Argument &arg) { arg.bindValue(*getBoundValuePtr<T>()); };
		}

		void copyDefaultValue(Argument &value) const {
			copy_default_value_closure(value);
		}

	private:
		std::function<void(Argument &)> copy_default_value_closure;
		std::function<void(void *)> delete_closure;

		void *default_value_storage;
		const IMetaType &type;
};

class Arguments {
	public:
		template<typename Arg, typename... Args>
		void initialize() {
			std::cout << "Creating arguments" << std::endl;
			ArgumentPusher<Arg, Args...>().push(arguments);
		}

		const Argument &operator[](size_t index) const {
			return arguments[index];
		}

		const size_t size() const {
			return arguments.size();
		}

		template<typename T>
		void bindValue(size_t index, const T& value)
		{
			arguments[index].bindValue(value);
		}

	private:
		template<typename Arg, typename... Args>
		struct ArgumentPusher {
			void push(std::vector<Argument> &arguments) {
				std::cout << "Pushing argument of type " << type_id_manager.getMetaType<Arg>().getTypeName() <<
				std::endl;
				arguments.emplace_back(type_id_manager.getMetaType<Arg>());
				ArgumentPusher<Args...>().push(arguments);
			}
		};

		template<typename Arg>
		struct ArgumentPusher<Arg> {
			void push(std::vector<Argument> &arguments) {
				arguments.emplace_back(type_id_manager.getMetaType<Arg>());
				std::cout << "Pushing last argument of type " << type_id_manager.getMetaType<Arg>().getTypeName() <<
				std::endl;
			}
		};

		std::vector<Argument> arguments;
};


class Constructor {
	public:
		virtual void construct(void *memory) const = 0;

		virtual void construct(void *memory, const Arguments &arguments) const = 0;

		virtual const Arguments &getArguments() const = 0;

		virtual const IMetaType &getType() const = 0;
};

template<typename Cls>
class DefaultConstructor : public Constructor {
	public:
		DefaultConstructor() {

		}

		virtual void construct(void *memory) const override {
			new(memory) Cls();
		}

		virtual void construct(void *memory, const Arguments &arguments) const override { }

		virtual const Arguments &getArguments() const override { return arguments; }

		virtual const IMetaType &getType() const override { return type_id_manager.getMetaType<Cls>(); }

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
			construct(memory, arguments);
		}

		virtual void construct(void *memory, const Arguments &args) const override {
			if (!argumentBindingsAreCorrect(args)) {
				std::cout << "Incorrect bindings passed" << std::endl;
				return;
			}
			int argument_counter = arguments.size() - 1;
			constructImpl(memory, extractBinding<Arg>(args, argument_counter),
						  extractBinding<Args>(args, argument_counter)...);
		}

		virtual const Arguments &getArguments() const override { return arguments; }

		virtual const IMetaType &getType() const override { return type_id_manager.getMetaType<Cls>(); }

	private:
		template<typename T>
		const T &extractBinding(const Arguments &binding, int &argument_counter) const {
			int counter = argument_counter;
			std::cout << "Extracting bound argument: " << argument_counter << std::endl;
			std::cout << "Type: " << type_id_manager.getMetaType<T>().getTypeName() << std::endl;
			std::cout << "PTR: " << binding[counter].getBoundValuePtr<T>() << std::endl;
			std::cout << "Value: " << *binding[counter].getBoundValuePtr<T>() << std::endl;
			--argument_counter;
			return *binding[counter].getBoundValuePtr<T>();
		}

		template<typename... InternalArgs>
		void constructImpl(void *memory, InternalArgs &&...args) const {
			std::cout << "Calling constructor with " << sizeof...(InternalArgs) << " arguments" << std::endl;
			new(memory) Cls(std::forward<InternalArgs>(args)...);
		}

		bool argumentBindingsAreCorrect(const Arguments &bindings) const {
			std::cout << "Checking argument bindings" << std::endl;
			for(int i = 0; i < bindings.size(); ++i)
			{
				if(!bindings[i].hasBoundValue())
				{
					return false;
				}
			}
			return true;
		}

		Arguments arguments;
};

class Constructors {
};

class Destructor {
};


class A {
	public:
		int intProperty;

		A() {
			std::cout << "Default A constructor called" << std::endl;
		}

		A(int a1, int a2, float a3, const std::string &a4) {
			std::cout << "Parametrized A constructor called" << std::endl;
			std::cout << "Parameters are:" << std::endl;
			std::cout << "a1: " << a1 << std::endl;
			std::cout << "a2: " << a2 << std::endl;
			std::cout << "a3: " << a3 << std::endl;
			std::cout << "a4: " << a4 << std::endl;
		}
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


class ObjectRefHolder {
	public:

		virtual ~ ObjectRefHolder() {
		}

		template<typename T>
		T *cast() {
			MetaType<T> &type = type_id_manager.getMetaType<T>();
			if (type != getType()) {
				std::cout << "Bad type" << std::endl;
				return nullptr;
			}
			return static_cast < T * >(getPointer());
		}

		template<typename T>
		void set(T *ptr) {
			MetaType<T> &type = type_id_manager.getMetaType<T>();
			if (type != getType()) {
				std::cout << "Bad type" << std::endl;
				return;
			}
			setPointer(ptr);
		}

	protected:
		ObjectRefHolder() {
		}

	private:
		virtual const IMetaType &getType() const = 0;

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

		virtual const IMetaType &getType() const override {
			return type;
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

		virtual IMetaType &getType() const = 0;

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

		IMetaType &getType() const override {
			return type;
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

		std::string name;
		T Cls::*field_ptr;
		MetaType<T> &type;
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

		virtual bool hasBaseType() const override {
			return getBaseType() != type_id_manager.getMetaType<void>();
		}

		virtual const IMetaType &getBaseType() const override {
			return type_id_manager.getMetaType<void>();
		}

		virtual bool isDerivedFrom(const IMetaType &type) const override {
			return false;
		}

	protected:
		BaseMetaType(const char *name, ClassType type, size_t size = sizeof(T)) {
			static size_t tid = type_id_manager.getTypeId(name);
			this->type_id = tid;
			this->type_name = name;
			this->size = size;
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
		virtual const IMetaType &getBaseType() const override {
			return base_class_meta_type;
		}

		virtual bool isDerivedFrom(const IMetaType &base_type) const override {
			if (getBaseType() == type_id_manager.getMetaType<void>()) return false;
			return getBaseType() == base_type || getBaseType().isDerivedFrom(base_type);
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
class MetaType<void> : public BaseMetaType<void> {
	public:
		MetaType() :
				BaseMetaType("void", ClassType::VOID_TYPE, 0) {
		}
};

bool is_void_type(const IMetaType &type) {
	return type == type_id_manager.getMetaType<void>();
}

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

template<>
class MetaType<std::string> : public BaseMetaType<std::string> {
	public:
		MetaType() :
				BaseMetaType("std::string", ClassType::CLASS) {
		}
};

int main() {
	MetaType<int> intMetaType;
	std::cout << intMetaType.getTypeName() << " = " << intMetaType.getTypeId() << std::endl;

	MetaType<float> floatMetaType;
	std::cout << floatMetaType.getTypeName() << " = " << floatMetaType.getTypeId() << std::endl;

	MetaType<float> floatMetaType2;
	std::cout << floatMetaType2.getTypeName() << " = " << floatMetaType2.getTypeId() << std::endl;

	DefaultConstructor<A> tc1;

	ParametrizedConstructor<A, int, int, float, std::string> tc2;

	Arguments args(tc2.getArguments());
	args.bindValue(0, 1);
	args.bindValue(1, 2);
	args.bindValue(2, 3.5f);
	args.bindValue(3, std::string("456"));

	void* mem1 = malloc(sizeof(A));
	void* mem2 = malloc(sizeof(A));

	tc1.construct(mem1);
	tc2.construct(mem2, args);




	std::cout << "Constructor definition:" << std::endl;
	std::cout << tc2.getType().getTypeName() << "(";
	for (int i = 0; i < tc2.getArguments().size(); ++i) {
		std::cout << tc2.getArguments()[i].getType().getTypeName();
		if (i < tc2.getArguments().size() - 1) std::cout << ", ";
	}
	std::cout << ")" << std::endl;

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
			getBaseType().getTypeName() << std::endl;

	std::cout << "Inheritance tree: " << std::endl;

	MetaType<D> dmt;
	const IMetaType *dmtp = &dmt;
	do {
		std::cout << dmtp->getTypeName() << " <- ";
		dmtp = &(dmtp->getBaseType());
	}
	while (!is_void_type(*dmtp));
	std::cout << "END" << std::endl;

	//getchar();

	return 0;
}
