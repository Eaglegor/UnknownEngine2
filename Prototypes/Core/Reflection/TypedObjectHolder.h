#pragma once



template<typename T>
class TypedObjectHolder : public ObjectRefHolder {
	public:
		TypedObjectHolder() :
				pointer(nullptr),
				type(META_TYPE(T)) {
		}

		TypedObjectHolder(T *ptr) :
				pointer(ptr),
				type(META_TYPE(T)) {
		}

		~TypedObjectHolder() {
			//delete type;
		}

	private:
		virtual void *getPointer() override {
			return pointer;
		}

		virtual void setPointer(void *ptr) override {
			pointer = static_cast<T *>(ptr);
		}

		virtual const IMetaType &getType() const override {
			return type;
		}

		MetaType<T> &type;
		T *pointer;
};
