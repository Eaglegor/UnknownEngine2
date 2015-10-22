#pragma once
#include <array>
#include <tuple>
#include <unordered_map>
#include "SequenceUtils.h"

enum class RefType
{
		LVALUE_REFERENCE,
		RVALUE_REFERENCE,
		POINTER,
		VALUE
};

class Argument
{
	public:
		virtual bool isConst() = 0;
		virtual RefType getRefType() = 0;
};

template<typename T>
class TypedArgument
{
	public:
		TypedArgument()
		{
			if(std::is_lvalue_reference<T>::value)
			{
				using RawType = std::remove_reference<T>::type;
				ref_type = RefType::LVALUE_REFERENCE;
				is_const = std::is_const<RawType>::value;
			}
			else if(std::is_rvalue_reference<T>::value)
			{
				using RawType = std::remove_reference<T>::type;
				ref_type = RefType::RVALUE_REFERENCE;
				is_const = std::is_const<RawType>::value;
			}
			else if(std::is_pointer<T>::value)
			{
				using RawType = std::remove_pointer<T>::type;
				ref_type = RefType::POINTER;
				is_const = std::is_const<RawType>::value;
			}
			else
			{
				is_const = std::is_const<T>::value;
				ref_type = RefType::VALUE;
			}
		}

		virtual bool isConst() {return is_const;}
		virtual RefType getRefType(){return ref_type;}

	private:
		RefType ref_type;
		bool is_const;
};

class Arguments
{
	public:
		virtual size_t size() = 0;
		virtual Argument& operator[](size_t index) = 0;
		virtual Argument* operator[](const char* name) = 0;
		virtual bool hasArgument(const char* name) = 0;
		virtual void bindArgumentName(size_t index, const char* name) = 0;
};

template<typename... Args>
class TypedArguments : public Arguments
{
	public:
		TypedArguments()
		{
			initializeArgumentsArray(generate_sequence<sizeof...(Args)>::type());
		}

		virtual size_t size(){
			return sizeof...(Args);
		}

		virtual Argument& operator[](size_t index)
		{
			return *arguments_array[index];
		}

		virtual Argument* operator[](const char* name)
		{
			auto iter = argument_name_mappings.find(name);
			if(iter == argument_name_mappings.end()) return nullptr;
			return iter->second;
		}

		virtual bool hasArgument(const char* name)
		{
			return argument_name_mappings.find(name) != argument_name_mappings.end();
		}

		virtual void bindArgumentName(size_t index, const char* name)
		{
			argument_name_mappings.emplace(name, arguments_array[index]);
		}

	private:

		template<size_t ...S>
		void initializeArgumentsArray(sequence<S...>) const
		{
			initializeArgumentsArrayImpl<S...>();
		}

		template<size_t N, size_t... Rest>
		void initializeArgumentsArrayImpl()
		{
			arguments_array[N] = std::get<N>(arguments);
			initializeArgumentsArrayImpl<Rest...>();
		}

		std::tuple<TypedArgument<Args>...> arguments;
		std::array<Argument*, sizeof...(Args)> arguments_array;
		std::unordered_map<std::string, Argument*> argument_name_mappings;
};
