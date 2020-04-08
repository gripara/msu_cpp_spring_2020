#include <cstdlib>
#include "allocator.h"

void* mem_ptr;
size_t occSize;
size_t blockSize;

void makeAllocator(size_t maxSize)
{
	mem_ptr = (char*) std::malloc(maxSize * sizeof(char));
	occSize = 0;
	blockSize = maxSize;
}

char* alloc(size_t size)
{
	if (mem_ptr == nullptr or size > blockSize - occSize) return nullptr;
	else
	{
		occSize += size;
		return ((char*) mem_ptr + (occSize - size) * sizeof(char));
	}
}

void reset()
{
	occSize = 0;
}
