#pragma once

#include <cstddef>

void* operator new(std::size_t size);
void* operator new[](std::size_t size);
void operator delete(void* pointer);
void operator delete[](void* pointer);
