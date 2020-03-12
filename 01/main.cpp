#include <iostream>
#include <cstdlib>
#include "allocator.h"

extern void* mem_ptr;
extern size_t occSize;
extern size_t blockSize;

int main()
{
	int N_tests = 3;
	int N_tests_completed = 0;
	size_t maxSize = 500;

	makeAllocator(maxSize);

/*-------- Test #1: Linearity of allocation --------*/

	size_t size_1 = 10, size_2 = 20;
	char* p_first = alloc(size_1);
	if (p_first - ((char *) mem_ptr) != 0)
	{
		std::cerr << "Allocation error: allocation of memory started not from the beginning" << std::endl;
		return 1;
	}

	char *p_second = alloc(size_2);
	if (p_second - p_first != size_1 * sizeof(char))
	{
		std::cerr << "Allocation error: non-linear allocation" << std::endl;
		return 1;
	}

	if (size_1 + size_2 != occSize)
	{
		std::cerr << "Allocation error: incorrect definition of occupied memory" << std::endl;
		return 1;
	}

	N_tests_completed += 1;
	std::cout << "Tests completed: " << N_tests_completed << "/" << N_tests << std::endl;

/*-------- Test #2: Ability to reset the memory --------*/

	reset();
	p_first = alloc(size_1);

	if (p_first - (char *) mem_ptr != 0)
	{
		std::cerr << "Reset error: not all the access to the memory is given" << std::endl;
		return 1;
	}

	N_tests_completed += 1;
	std::cout << "Tests completed: " << N_tests_completed << "/" << N_tests << std::endl;

	reset();
	p_first = alloc(size_1);
	p_first[size_1] = 'w';

/*-------- Test #3: Boundness of the block --------*/

	int N_blocks = 15;
	size_t subblockSize = maxSize / N_blocks;
	char *block_ptr[N_blocks];

	reset();

	p_first = alloc(maxSize); /* admissible allocation */
	if (p_first == nullptr)
	{
		std::cerr << "Boundness error: allocation must be admissible" << std::endl;
		return 1;
	}

	reset();

	p_first = alloc(maxSize + 1); /* Allocating more memory than available in \
				    \ one allocation */
	if (p_first != nullptr)
	{
		std::cerr << "Boundness error: out of size" << std::endl;
		return 1;
	}

	for (int i = 0; i < N_blocks + 1; i++) /* Allocating block by block*/
	{
		block_ptr[i] = alloc(subblockSize);
	}

	if (block_ptr[N_blocks] != nullptr)
	{
		std::cerr << "Boundness error: out of size" << std::endl;
		return 1;
	}
	N_tests_completed += 1;
	std::cout << "Tests completed: " << N_tests_completed << "/" << N_tests << std::endl;
	return 0;
}
