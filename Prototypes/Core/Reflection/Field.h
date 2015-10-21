#pragma once

class Field {
	public:
		virtual ~Field() { };

		template<typename T, typename Cls>
		T &ref(Cls *cls) const {
			return *static_cast<T *>(getPointer(cls));
		}

		template<typename Cls, typename T>
		void setValue(Cls *cls, const T &value) const {
			if (!typeMatches(META_TYPE(Cls), META_TYPE(T))) {
				std::cout << "BadType" << std::endl;
				return;
			}
			setValueImpl(cls, &value);
		}

		template<typename Cls, typename T>
		const T &getValue(Cls *cls) const {
			if (!typeMatches(META_TYPE(Cls), META_TYPE(T))) {
				std::cout << "BadType" << std::endl;
				throw std::invalid_argument("bad type");
			}
			void *value;
			getValueImpl(cls, &value);
			return *reinterpret_cast<T *>(value);
		}

		virtual IMetaType &getType() const = 0;

		virtual const char *getName() = 0;

	protected:
		Field() { }

	private:

		virtual bool typeMatches(const IMetaType &cls_type, const IMetaType &value_type) const = 0;

		virtual void setValueImpl(void *cls, const void *value) const = 0;

		virtual void getValueImpl(void *cls, void **value) const = 0;

		virtual void *getPointer(void *cls) const = 0;
};