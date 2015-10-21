#include <unordered_map>
#include <iostream>
#include <chrono>
#include <array>
#include <tuple>
#include <functional>
#include <vector>

#include "TypeIdManager.h"

#include "Arguments.h"
#include "ConstructorImpl.h"

#include "A.h"
#include "B.h"
#include "C.h"
#include "D.h"

#include "DefaultMetaTypes.h"
#include "TypedBoundField.h"

TypeIdManager* TypeIdManager::instance = new TypeIdManager();


int main() {
	MetaType<int> intMetaType;
	std::cout << intMetaType.getTypeName() << " = " << intMetaType.getTypeId() << std::endl;

	MetaType<float> floatMetaType;
	std::cout << floatMetaType.getTypeName() << " = " << floatMetaType.getTypeId() << std::endl;

	MetaType<float> floatMetaType2;
	std::cout << floatMetaType2.getTypeName() << " = " << floatMetaType2.getTypeId() << std::endl;

	ConstructorImpl<A> tc1;

	ConstructorImpl<A, int, int, float, std::string> tc2;

	const Constructor& constr = tc2;

	Arguments args(constr.getArguments());
	args.bindValue(0, 1);
	args.bindValue(1, 2);
	args.bindValue(2, 3.5f);
	args.bindValue(3, std::string("456"));

	void* mem1 = malloc(sizeof(A));
	void* mem2 = malloc(constr.getType().getSize());

	tc1.construct(mem1);
	constr.construct(mem2, args);




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

	MetaType<A> &amt = META_TYPE(A);
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
