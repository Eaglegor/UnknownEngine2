#pragma once

#include "MetaType.h"
#include "BaseMetaType.h"

template<>
class MetaType<void> : public BaseMetaType<void> {
	public:
		MetaType() :
				BaseMetaType("void", ClassType::VOID_TYPE, 0) {
		}
};

bool is_void_type(const IMetaType &type) {
	return type == META_TYPE(void);
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
class MetaType<std::string> : public BaseMetaType<std::string> {
	public:
		MetaType() :
				BaseMetaType("std::string", ClassType::CLASS) {
		}
};
