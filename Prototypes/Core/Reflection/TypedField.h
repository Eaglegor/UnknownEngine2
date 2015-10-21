#pragma once

#include "Field.h"

template<typename Cls, typename T>
class TypedField : public Field {
	public:
		TypedField(const char *name, T Cls::*ptr) :
				name(name),
				field_ptr(ptr),
				type(META_TYPE(T)) {
		}

		IMetaType &getType() const override {
			return type;
		}

		const char *getName() override {
			return name.c_str();
		}

	private:
		void setValueImpl(void *cls, const void *value) const override {
			Cls *clsptr = static_cast<Cls *>(cls);
			const T *val = static_cast<const T *>(value);
			clsptr->*field_ptr = *val;
		}

		void getValueImpl(void *cls, void **value) const override {
			Cls *clsptr = static_cast<Cls *>(cls);
			*value = &(clsptr->*field_ptr);
		}

		void *getPointer(void *cls) const override {
			Cls *clsptr = static_cast<Cls *>(cls);
			return &(clsptr->*field_ptr);
		}

		virtual bool typeMatches(const IMetaType &cls_type, const IMetaType &value_type) const {
			return META_TYPE(Cls) == cls_type && META_TYPE(T) == value_type;
		}

		std::string name;
		T Cls::*field_ptr;
		MetaType<T> &type;
};