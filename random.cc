// C program for generating a
// random number in a given range.
#include <stdio.h>
#include <stdlib.h>

#include "random.h"


// Generates and prints 'count' random
// numbers in range [lower, upper].
void printRandoms(int lower, int upper, int count)
{
	int i;
	for (i = 0; i < count; i++) 
	{
		int num = (rand() % (upper - lower + 1)) + lower;
		printf("%d ", num);
	}
	printf("\n");
}

intvector_t	random_unique(unsigned seed, int maximum, int count)
{
	intvector_t	allemaal;
	intvector_t	numbers;

	srand(seed);

	for (int i = 0; i < maximum; i ++)
	{
		allemaal.push_back(i);
	}
	while (count -- > 0)
	{
		int nummer = rand() % (maximum --);
		numbers.push_back(allemaal[nummer]);
		allemaal.erase(allemaal.begin() + nummer);
	}
	return numbers;
}
