#pragma once

#include "BaseMetaType.h"

class C : public B {
	public:
		int int2Property;
};

template<>
class MetaType<C> : public BaseMetaType<C, B> {
	public:
		MetaType() :
				BaseMetaType("C", ClassType::CLASS) {
		}
};