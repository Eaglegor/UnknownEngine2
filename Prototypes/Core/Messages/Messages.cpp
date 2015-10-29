#include <iostream>
#include <string>
#include <stdlib.h>

void* allocateMemory(size_t size)
{
	return malloc(size);
}

void deallocateMemory(void* memory)
{
	free(memory);
}

class IMessageType
{
	public:
		virtual std::string getName() = 0;
		virtual size_t getSize() = 0;

		virtual void construct(void* memory) = 0;
		virtual void destruct(void* memory) = 0;
};

template<typename T>
class MessageType : public IMessageType
{
	public:
		MessageType(std::string name):
		name(name)
		{
		}

		virtual std::string getName() override
		{
			return name;
		}

		virtual size_t getSize() override
		{
			return sizeof(T);
		}

		virtual void construct(void *memory) override
		{
			new(memory) T();
		}

		virtual void destruct(void *memory) override
		{
			static_cast<T*>(memory)->~T();
		}

	private:
		std::string name;
};

class IMessage
{
	public:
		virtual IMessageType& getType() = 0;
};

template<typename T>
class Message : public IMessage
{
	public:
		virtual IMessageType& getType() override
		{
			return type;
		}

	private:
		MessageType<T> type;
};

class TestEventMessage : public Message<TestEventMessage>
{
	public:
		int i;
		float f;
		std::string s;
};

class TestRequestMessage : public Message<TestRequestMessage>
{
	public:
		int request;
};

class TestResponseMessage : public Message<TestResponseMessage>
{
	public:
		int answer;
};

class A
{
	public:
		void eventProcessor(const TestEventMessage& msg)
		{
			std::cout << "A: Got event message (" << msg.i << ", " << msg.f << ", " << msg.s << ")" << std::endl;
		}

		void requestProcessor(const TestRequestMessage &msg, TestResponseMessage &response)
		{

		}
};

class B
{
	public:
		void eventProcessor(const TestEventMessage& msg)
		{
			std::cout << "B: Got event message (" << msg.i << ", " << msg.f << ", " << msg.s << ")" << std::endl;
		}
};

int main()
{
	return 0;
}
