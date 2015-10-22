#pragma once

#include "TypeIdManager.h"

class Argument {
	public:
		Argument(const IMetaType &type) :
				default_value_storage(nullptr),
				type(type) { }

		~Argument() {
			if (default_value_storage) delete_closure(default_value_storage); // Deallocate storage memory ;
		}

		Argument(const Argument &rhs) :
				default_value_storage(nullptr),
				type(rhs.getType()) {
			if (rhs.hasBoundValue()) {
				rhs.copyDefaultValue(*this);
			}
		}

		bool isConst() const
		{

		}

		const IMetaType &getType() const { return type; }

		bool hasBoundValue() const {
			return default_value_storage != nullptr;
		}

		template<typename T>
		T *getBoundValuePtr() const {
			if (META_TYPE(T) != type)
			{
				std::cout << "Incorrect value type requested" << std::endl;
				std::cout << "Expected: " << type.getTypeName() << " but passed: " << META_TYPE_NAME(T) << std::endl;
				return nullptr;
			}
			return static_cast<T *>(default_value_storage);
		}

		template<typename T>
		void bindValue(const T &value) {
			if( META_TYPE(T) != type) {
				std::cout << "Incorrect value type passed to be bound" << std::endl;
				std::cout << "Expected: " << type.getTypeName() << " but passed: " << META_TYPE_NAME(T) << std::endl;
				return;
			}
			default_value_storage = new T(value);
			delete_closure = [](void *obj) { delete static_cast<T *>(obj); };
			copy_default_value_closure = [this](Argument &arg) { arg.bindValue(*getBoundValuePtr<T>()); };
			owns_value = true;
		}



		void copyDefaultValue(Argument &value) const {
			copy_default_value_closure(value);
		}

	private:
		std::function<void(Argument &)> copy_default_value_closure;
		std::function<void(void *)> delete_closure;

		bool is_const;
		bool owns_value;
		void *default_value_storage;
		const IMetaType &type;
};