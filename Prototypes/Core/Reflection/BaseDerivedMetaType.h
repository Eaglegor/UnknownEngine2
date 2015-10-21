#pragma once

#include "BaseMetaType.h"

template<typename T, typename BaseClass>
class BaseDerivedMetaType : public BaseMetaType<T> {
		static_assert(std::is_base_of<BaseClass, T>::value, "T must derive from BaseClass");

	public:
		virtual const IMetaType &getBaseType() const override {
			return base_class_meta_type;
		}

		virtual bool isDerivedFrom(const IMetaType &base_type) const override {
			if (getBaseType() == META_TYPE(void)) return false;
			return getBaseType() == base_type || getBaseType().isDerivedFrom(base_type);
		}

	protected:
		BaseDerivedMetaType(const char *name, ClassType type) :
				BaseMetaType<T>(name, type),
				base_class_meta_type(META_TYPE(BaseClass)) {

		}

	private:
		MetaType<BaseClass> &base_class_meta_type;
};
