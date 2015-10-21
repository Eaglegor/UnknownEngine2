#pragma once

#include "Arguments.h"

class Constructor {
	public:
		virtual void construct(void *memory) const = 0;

		virtual void construct(void *memory, const Arguments &arguments) const = 0;

		virtual const Arguments &getArguments() const = 0;

		virtual const IMetaType &getType() const = 0;
};