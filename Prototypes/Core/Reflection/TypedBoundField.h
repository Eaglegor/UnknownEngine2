#pragma once


template<typename Cls, typename T>
class TypedBoundField {
	public:
		TypedBoundField(const Field *field, Cls *cls) :
				t(field->ref<T>(cls)) {
		}

		TypedBoundField &operator=(const T &rhs) {
			t = rhs;
			return *this;
		}

		void setValue(const T &val) {
			t = val;
		}

	private:
		T &t;
};