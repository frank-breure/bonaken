#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>

#include "bonaken.h"

int main(int argc, const char * argv[])
{
	potje_t		potje;

	if (argc == 1)
	{

		do
		{
			potje = Deel();

			printPot(potje);
		}	while (vindVierkaart(potje.noord) == 0 && vindVierkaart(potje.oost) == 0 &&
				vindVierkaart(potje.zuid) == 0 && vindVierkaart(potje.west) == 0);
		/* Stop bij de eerste roem
		(vindRoem(potje.noord) == 0 && vindRoem(potje.oost) == 0 &&
		vindRoem(potje.zuid) == 0 && vindRoem(potje.west) == 0); */
	}
	else
	{
		for (int i = 1; i < argc; i ++)
		{
			unsigned seed;

			seed = strtoul(argv[i], nullptr, 16);
			if (seed != 0 || argv[i][0] == '0')
			{
				potje = Deel(seed);
				printPot(potje);
			}
			else
			{
				std::cerr << "Failed to parse hexadecimal seed: " << argv[i] << std::endl;
			}
		}
	}
}
