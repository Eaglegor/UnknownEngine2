#pragma once

#include "Constructor.h"

class Constructors {
	public:
		void addConstructor(Constructor* constructor)
		{
			constructors.emplace_back(constructor);
		}

	private:
		std::vector<Constructor*> constructors;
};
