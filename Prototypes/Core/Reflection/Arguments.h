#pragma once

#include "Argument.h"

class Arguments {
	public:
		template<typename... Args>
		void initialize() {
			std::cout << "Creating arguments" << std::endl;
			ArgumentPusher<Args...>().push(arguments);
		}

		const Argument &operator[](size_t index) const {
			return arguments[index];
		}

		const size_t size() const {
			return arguments.size();
		}

		template<typename T>
		void bindValue(size_t index, const T& value)
		{
			arguments[index].bindValue(value);
		}

	private:
		template<typename... Args>
		struct ArgumentPusher
		{
			void push(std::vector<Argument> &arguments) {
			}
		};

		template<typename Arg, typename... Args>
		struct ArgumentPusher<Arg, Args...> {
			void push(std::vector<Argument> &arguments) {
				std::cout << "Pushing argument of type " << META_TYPE_NAME(Arg) <<
				std::endl;
				arguments.emplace_back(META_TYPE(Arg));
				ArgumentPusher<Args...>().push(arguments);
			}
		};

		template<typename Arg>
		struct ArgumentPusher<Arg> {
			void push(std::vector<Argument> &arguments) {
				arguments.emplace_back( META_TYPE(Arg) );
				std::cout << "Pushing last argument of type " << META_TYPE_NAME(Arg) <<
				std::endl;
			}
		};


		std::vector<Argument> arguments;
};
