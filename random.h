#pragma once

#include <vector>

typedef std::vector<int>	intvector_t;

/**
 * @brief Get an array of random numbers.
 *
 * @param seed		Seed to randomizer.
 * @param number 	Maximum value of the numbers, 0 is assumed to be a valid number as well.
 * @param count 	How many unique random numbers to generate.
 * @return intvector_t Array of random numbers, without duplicates.
 */
intvector_t	random_unique(unsigned seed, int maximum, int count);
