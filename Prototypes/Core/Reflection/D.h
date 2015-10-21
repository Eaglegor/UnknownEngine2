#pragma once

#include "BaseDerivedMetaType.h"

class D : public C {
	public:
		int int3Property;
};

template<>
class MetaType<D> : public BaseDerivedMetaType<D, C> {
	public:
		MetaType() :
				BaseDerivedMetaType("D", ClassType::CLASS) {
		}
};
