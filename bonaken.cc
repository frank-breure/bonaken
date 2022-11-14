#include <stdio.h>
#include <time.h>

#include <algorithm>

#include "bonaken.h"
#include "random.h"

const std::vector<soort_e>	Soorten(void)
{
	static std::vector<soort_e> soorten =
	{
		Schoppen,
		Harten,
		Klaveren,
		Ruiten,
	};
	return soorten;
}

char const * strSoort(soort_e soort)
{
	static char const * soorten[] =
	{
		"Sch",
		"Har",
		"Kla",
		"Rui",
	};
	return soorten[soort];
}

char const * strWaarde(const waarde_e waarde)
{
	static char const * waardes[] =
	{
		"7 ",
		"8 ",
		"9 ",
		"10",
		"B ",
		"V ",
		"H ",
		"A ",
	};
	return waardes[waarde];
}

int	Punten(kaart_t kaart)
{
	static int gewoon[] =
	{
		0,
		0,
		0,
		10,
		1,
		2,
		3,
		11,
	};
	return gewoon[kaart.waarde];
}

int TroefPunten(soort_e troef, kaart_t kaart)
{
	static int troeven[] =
	{
		0, 
		0,
		14,
		10,
		20,
		2,
		3,
		11,
	};
	if (kaart.soort == troef)
	{
		return troeven[kaart.waarde];
	}
	return 0;
}

int TotaalTroefPunten(soort_e troef, kaarten_t hand)
{
	int totaal = 0;

	for (auto kaart: hand)
	{
		totaal += TroefPunten(troef, kaart);
	}
	return totaal;
}

char const * strKaart(const kaart_t kaart)
{
	static char buf[10];

	sprintf(buf, "%s-%s", strSoort(kaart.soort), strWaarde(kaart.waarde));
	return buf;
}

kaarten_t Spel(void)
{
	kaarten_t spel;
	std::vector<soort_e> soorten = { Schoppen, Harten, Klaveren, Ruiten };
	std::vector<waarde_e> waardes = { Zeven, Acht, Negen, Tien, Boer, Vrouw, Heer, Aas };

	for (auto & soort : soorten) 
	{
		for (auto & waarde : waardes)
		{
			kaart_t kaart = { soort, waarde };
			spel.push_back(kaart);
		}
	}
	return spel;
}

static bool deel(const kaarten_t & spel, intvector_t & geschud, int aantal, kaarten_t & aan)
{
	if ((size_t) aantal > geschud.size())
	{
		return false;
	}
	for (int i = 0; i < aantal; i ++)
	{
		aan.push_back(spel[geschud[0]]);
		geschud.erase(geschud.begin());
	}
	return true;
}

potje_t	Deel(unsigned seed)
{
	potje_t		pot;
	kaarten_t	spel = Spel();

	if (seed == 0)
	{
		struct timespec tp;
		clock_gettime(CLOCK_TAI, &tp);
		seed = (unsigned) tp.tv_nsec;
	}
	printf("seed=%08x\n", seed);

	intvector_t	geschud = random_unique(seed, 32, 32);

	for (int i = 0; i < 2; i ++)
	{
		deel(spel, geschud, 3, pot.noord);
		deel(spel, geschud, 3, pot.oost);
		deel(spel, geschud, 3, pot.zuid);
		deel(spel, geschud, 3, pot.west);
		if (i == 0)
		{
			deel(spel, geschud, 2, pot.open);
		}
	}
	deel(spel, geschud, 1, pot.dicht);
	deel(spel, geschud, 5, pot.slapers);
	return pot;
}

inline bool operator< (const kaart_t & lhs, const kaart_t & rhs) 
{
	if (lhs.soort == rhs.soort)
	{
		return lhs.waarde < rhs.waarde;
	}
	return lhs.soort < rhs.soort;
}

void printHand(const kaarten_t & hand)
{
	kaarten_t	volgorde = hand;
	int			punten = 0;

	std::sort(volgorde.begin(), volgorde.end());
	for (auto kaart: volgorde)
	{
		printf("%s ", strKaart(kaart));
		punten += Punten(kaart);
	}
	for (int i = 7 * hand.size(); i < 7 * 6; i ++)
	{
		putc(' ', stdout);
	}
	printf(" [%2d] ", punten);
	for (auto troef: Soorten())
	{
		printf("[%s %2d] ", strSoort(troef), TotaalTroefPunten(troef, hand));
	}
	int roem = vindRoem(hand);
	if (roem)
	{
		printf(" roem: %d", roem);
	}
	printf("\n");
}

void printPot(const potje_t & potje)
{
	printf("\n");
	printf("Noord: ");
	printHand(potje.noord);
	printf("Oost : ");
	printHand(potje.oost);
	printf("Zuid : ");
	printHand(potje.zuid);
	printf("West : ");
	printHand(potje.west);
	printf("Open : ");
	printHand(potje.open);
	printf("Dicht: ");
	printHand(potje.dicht);
	printf("Slaap: ");
	printHand(potje.slapers);
	printf("\n");
}

inline bool sorteerOpWaarde(const kaart_t & lhs, const kaart_t & rhs) 
{
	return lhs.waarde < rhs.waarde;
}

int vindVierkaart(const kaarten_t & hand)
{
	kaarten_t	handOpWaarde = hand;

	// Sorteer de hand alleen op waarde, niet op soort.
	std::sort(handOpWaarde.begin(), handOpWaarde.end(), sorteerOpWaarde);
	
	for (int i = 0; i < (int) handOpWaarde.size() - 3; i  ++)
	{
		if (handOpWaarde[i].waarde == handOpWaarde[i + 1].waarde && 
			handOpWaarde[i].waarde == handOpWaarde[i + 2].waarde && handOpWaarde[i].waarde == handOpWaarde[i + 3].waarde &&
			handOpWaarde[i].waarde >= Boer)
		{
			return (handOpWaarde[i].waarde == Boer) ? 200 : 100;
		}
	}
	return 0;
}

int	vindRoem(const kaarten_t & hand)
{
	int	roem = 0;
	for (int i = 0; i < (int) hand.size() - 2; i  ++)
	{
		// Is dit een driekaart?
		if (hand[i].soort == hand[i + 1].soort && hand[i].soort == hand[i + 2].soort &&
			(hand[i].waarde + 1) == hand[i + 1].waarde && (hand[i].waarde + 2) == hand[i + 2].waarde)
		{
			// Is het een vierkaart?
			if (i + 3 < hand.size() && 
				hand[i].soort == hand[i + 3].soort && (hand[i].waarde + 3) == hand[i + 3].waarde)
			{
				// Of zelfs een vijfkaart.
				if (i + 4 < hand.size() && 
					hand[i].soort == hand[i + 4].soort && (hand[i].waarde + 4) == hand[i + 4].waarde)
				{
					roem += 100;
					i += 4;
					// Nog gekker, een echte zeskaart, hoeveel roem is dat?
					if (i + 5 < hand.size() && (hand[i].waarde + 5) == hand[i + 5].waarde)
					{
						roem += 200;
						i += 5;
					}
				}
				else
				{
					roem += 50;
					i += 3;
				}
			}
			else
			{
				roem += 20;
				i += 2;
			}
		}
	}
	return roem + vindVierkaart(hand);
}
