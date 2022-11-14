#include "bonaken.h"

int main(int, const char *[])
{
	potje_t		potje;

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
