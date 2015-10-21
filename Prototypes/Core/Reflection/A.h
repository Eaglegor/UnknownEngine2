#pragma once

#include "BaseMetaType.h"

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

template<>
class MetaType<A> : public BaseMetaType<A> {
	public:
		MetaType() :
				BaseMetaType("A", ClassType::CLASS),
				intProperty("intProperty", &A::intProperty) {

			addConstructor(&defaultConstructor);
			addConstructor(&constructor1);

			addField("intProperty", &intProperty);
		}

	private:
		TypedField<A, int> intProperty;

		DefaultConstructor<A> defaultConstructor;
		ParametrizedConstructor<A, int, int, float, std::string> constructor1;
};