#include "New.h"

#include <cstdlib>

void* operator new(std::size_t size)
{
	return ::malloc(size);
}

void* operator new[](std::size_t size)
{
	return ::malloc(size);
}

void operator delete(void* pointer)
{
	::free(pointer);
}

void operator delete[](void* pointer)
{
	::free(pointer);
}
