#pragma once

#include "MetaType.h"
#include "TypeIdManager.h"

template<>
class MetaType<void> : public IMetaType {
	public:
		MetaType() {
			static size_t tid = TypeIdManager::instance->getTypeId("void");
			type_id = tid;
		}

		virtual ClassType getClassType() const {return ClassType::VOID_TYPE; }

		virtual size_t getTypeId() const {return type_id;}

		virtual size_t getSize() const {return 0;}

		virtual const char *getTypeName() const {return "void";}

		virtual const Constructors &getConstructors() const {return constructors;}

		virtual const Destructor &getDestructor() const {return destructor;}

		virtual const Methods &getMethods() const {return methods;}

		virtual const Fields &getFields() const {return fields;}

		virtual bool hasBaseType() const {return false;}

		virtual const IMetaType &getBaseType() const {return *this;}

		virtual bool isDerivedFrom(const IMetaType &type) const {return false;}

	private:
		Methods methods;
		Fields fields;
		Constructors constructors;
		Destructor destructor;

		size_t type_id;
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
