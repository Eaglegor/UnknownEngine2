#pragma once

#include "BaseMetaType.h"

class D : public C {
	public:
		int int3Property;
};

template<>
class MetaType<D> : public BaseMetaType<D, C> {
	public:
		MetaType() :
				BaseMetaType("D", ClassType::CLASS) {
		}
};
