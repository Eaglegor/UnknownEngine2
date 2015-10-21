#pragma once


class ObjectRefHolder {
	public:

		virtual ~ ObjectRefHolder() {
		}

		template<typename T>
		T *cast() {
			MetaType<T> &type = META_TYPE(T);
			if (type != getType()) {
				std::cout << "Bad type" << std::endl;
				return nullptr;
			}
			return static_cast < T * >(getPointer());
		}

		template<typename T>
		void set(T *ptr) {
			MetaType<T> &type = META_TYPE(T);
			if (type != getType()) {
				std::cout << "Bad type" << std::endl;
				return;
			}
			setPointer(ptr);
		}

	protected:
		ObjectRefHolder() {
		}

	private:
		virtual const IMetaType &getType() const = 0;

		virtual void *getPointer() = 0;

		virtual void setPointer(void *ptr) = 0;
};
