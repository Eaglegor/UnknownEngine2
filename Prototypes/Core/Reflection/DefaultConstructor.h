#pragma once

#include "Constructor.h"

template<typename Cls>
class DefaultConstructor : public Constructor {
	public:
		DefaultConstructor() {

		}

		virtual void construct(void *memory) const override {
			new(memory) Cls();
		}

		virtual void construct(void *memory, const Arguments &arguments) const override { }

		virtual const Arguments &getArguments() const override { return arguments; }

		virtual const IMetaType &getType() const override { return META_TYPE(Cls); }

	private:
		Arguments arguments;
};