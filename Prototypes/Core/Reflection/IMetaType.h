#pragma once

class Constructors;
class Destructor;
class Methods;
class Fields;

enum class ClassType {
		PRIMITIVE,
		CLASS,
		ARRAY,
		VOID_TYPE
};

class IMetaType {
	public:
		virtual ClassType getClassType() const = 0;

		virtual size_t getTypeId() const = 0;

		virtual size_t getSize() const = 0;

		virtual const char *getTypeName() const = 0;

		virtual const Constructors &getConstructors() const = 0;

		virtual const Destructor &getDestructor() const = 0;

		virtual const Methods &getMethods() const = 0;

		virtual const Fields &getFields() const = 0;

		virtual bool hasBaseType() const = 0;

		virtual const IMetaType &getBaseType() const = 0;

		virtual bool isDerivedFrom(const IMetaType &type) const = 0;

		bool operator==(const IMetaType &rhs) const {
			return getTypeId() == rhs.getTypeId();
		}

		bool operator!=(const IMetaType &rhs) const {
			return !(*this == rhs);
		}
};