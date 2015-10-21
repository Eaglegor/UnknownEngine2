#pragma once

#include "BaseMetaType.h"

class B {
	public:
		float floatProperty;
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