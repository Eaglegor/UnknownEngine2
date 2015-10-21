#pragma once

class Field;

class Fields {
	public:
		void addField(const char *name, Field *field) {
			fields.emplace(name, field);
		}

		const Field *getField(const char *name) const {
			auto iter = fields.find(name);
			if (iter == fields.end()) return nullptr;
			return iter->second;
		}

	private:
		std::unordered_map<std::string, Field *> fields;
};