#pragma once

#include "IMetaType.h"

template<typename T>
class MetaType : public IMetaType {
		virtual ~ MetaType() {
		}

		MetaType() = delete;
};