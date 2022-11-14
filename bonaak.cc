#include <stdio.h>

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

			if (sscanf(argv[i], "%x", &seed) == 1)
			{
				potje = Deel(seed);
				printPot(potje);
			}
			else
			{
				fprintf(stderr, "Failed to parse hexadecimal seed: %s\n", argv[i]);
			}
		}
	}
}
