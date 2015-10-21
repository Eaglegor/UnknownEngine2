#pragma once

#include "IMetaType.h"
#include "TypeIdManager.h"
#include "Constructors.h"
#include "Destructor.h"
#include "Methods.h"
#include "Fields.h"
#include "TypedField.h"
#include "DefaultConstructor.h"
#include "ParametrizedConstructor.h"

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
			return getBaseType() != META_TYPE(void);
		}

		virtual const IMetaType &getBaseType() const override {
			return META_TYPE(void);
		}

		virtual bool isDerivedFrom(const IMetaType &type) const override {
			return false;
		}

	protected:
		BaseMetaType(const char *name, ClassType type, size_t size = sizeof(T)) {
			static size_t tid = TypeIdManager::instance->getTypeId(name);
			this->type_id = tid;
			this->type_name = name;
			this->size = size;
			this->type = type;
		}

		void addField(const char *name, Field *field) {
			fields.addField(name, field);
		}

		void addConstructor(Constructor* constructor)
		{
			constructors.addConstructor(constructor);
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
