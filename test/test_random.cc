#include "random.h"

#include <ctime>
#include <algorithm>

#include <gtest/gtest.h>

static unsigned getSeed()
{
	timespec tp{};
	clock_gettime(CLOCK_TAI, &tp);
	return static_cast<unsigned>(tp.tv_nsec);
}

static intvector_t	random_unique(int maximum, int count)
{
	return random_unique(getSeed(), maximum, count);
}

TEST(RandomTest, DeeltAlles)
{
	intvector_t	een = random_unique(1, 1);

	ASSERT_EQ(1, een.size());
	ASSERT_EQ(0, een[0]);

	intvector_t	twee = random_unique(2, 2);

	ASSERT_EQ(2, twee.size());
	ASSERT_TRUE(0 == twee[0] || 1 == twee[0]);
	ASSERT_TRUE(0 == twee[1] || 1 == twee[1]);
	ASSERT_TRUE(twee[0] != twee[1]);

	intvector_t	drie = random_unique(3, 3);
	ASSERT_EQ(3, drie.size());
	ASSERT_TRUE(0 == drie[0] || 1 == drie[0] || 2 == drie[0]);
	ASSERT_TRUE(0 == drie[1] || 1 == drie[1] || 2 == drie[1]);
	ASSERT_TRUE(0 == drie[2] || 1 == drie[2] || 2 == drie[2]);
	ASSERT_TRUE(drie[0] != drie[1] && drie[1] != drie[2]);

	const intvector_t	tweeendertig = random_unique(32, 32);
	ASSERT_EQ(32, tweeendertig.size());
	int sum = 0;
	for (auto van = tweeendertig.begin(); van != tweeendertig.end(); ++ van)
	{
		int zoek = *van;

		ASSERT_EQ(tweeendertig.end(), std::find(van + 1, tweeendertig.end(), zoek));
		sum += *van;
	}
	ASSERT_EQ(16 * 31, sum);

	const intvector_t	honderd = random_unique(100, 100);
	sum = 0;
	for (auto van = honderd.begin(); van != honderd.end(); ++ van)
	{
		int zoek = *van;

		ASSERT_EQ(honderd.end(), std::find(van + 1, honderd.end(), zoek));
		sum += *van;
	}
	ASSERT_EQ(50 * 99, sum);
}
