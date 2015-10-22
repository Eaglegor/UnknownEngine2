#pragma once

#include "Constructor.h"
#include "SequenceUtils.h"

template<typename Cls, typename... Args>
class ConstructorImpl : public Constructor {
		static_assert(std::is_constructible<Cls, Args...>::value, "Class has no constructor with provided argument types");
	public:
		ConstructorImpl() {
			std::cout << "Constructing parametrized constructor" << std::endl;
			arguments.initialize<Args...>();
		}

		virtual void construct(void *memory) const override {
			construct(memory, arguments);
		}

		virtual void construct(void *memory, const Arguments &args) const override {
			if (!argumentBindingsAreCorrect(args)) {
				std::cout << "Incorrect bindings passed" << std::endl;
				return;
			}
			constructImpl(memory, args, typename generate_sequence<sizeof...(Args)>::type());
		}

		virtual const Arguments &getArguments() const override { return arguments; }

		virtual const IMetaType &getType() const override { return META_TYPE(Cls); }

	private:
		template<size_t N>
		using NthArgumentType = typename std::tuple_element<N, std::tuple<Args...>>::type;

		template<size_t ...S>
		void constructImpl(void* memory, const Arguments &bindings, sequence<S...>) const
		{
			new(memory) Cls( extractBinding<S>(bindings) ...);
		}

		template<size_t S, typename T = NthArgumentType<S>>
		const T &extractBinding(const Arguments &bindings) const {
			return *bindings[S].getBoundValuePtr<T>();
		}

		bool argumentBindingsAreCorrect(const Arguments &bindings) const {
			std::cout << "Checking argument bindings" << std::endl;
			for(int i = 0; i < bindings.size(); ++i)
			{
				if(!bindings[i].hasBoundValue() || bindings[i].getType() != arguments[i].getType())
				{
					return false;
				}
			}
			return true;
		}

		Arguments arguments;
};