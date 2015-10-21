#pragma once

#include "BaseDerivedMetaType.h"

class C : public B {
	public:
		int int2Property;
};

template<>
class MetaType<C> : public BaseDerivedMetaType<C, B> {
	public:
		MetaType() :
				BaseDerivedMetaType("C", ClassType::CLASS) {
		}
};