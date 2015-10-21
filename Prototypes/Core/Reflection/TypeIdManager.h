#pragma once

#include "MetaType.h"

class TypeIdManager {
	public:
		size_t getTypeId(const char *name) {
			auto iter = mappings.find(name);
			if (iter == mappings.end()) {
				size_t val = counter++;
				mappings.emplace(name, val);
				return val;
			}
			return iter->second;
		}

		template<typename T>
		MetaType<T> &getMetaType() {
			static MetaType<T> meta_type;
			return meta_type;
		}

		static TypeIdManager* instance;
	private:
		size_t counter = 0;
		std::unordered_map<std::string, size_t> mappings;
};

#define META_TYPE(T) TypeIdManager::instance->getMetaType<T>()
#define META_TYPE_NAME(T) TypeIdManager::instance->getMetaType<T>().getTypeName()
#define META_TYPE_ID(T) TypeIdManager::instance->getMetaType<T>().getTypeId()