#pragma once

#include <vector>

typedef enum
{
	Schoppen,
	Harten,
	Klaveren,
	Ruiten,
}   soort_e;

typedef enum 
{
	Zeven,
	Acht,
	Negen,
	Tien,
	Boer,
	Vrouw,
	Heer,
	Aas,
}	waarde_e;

typedef struct
{
	soort_e		soort;
	waarde_e	waarde;
}	kaart_t;

char const * strSoort(soort_e soort);
char const * strWaarde(waarde_e waarde);
char const * strKaart(kaart_t kaart);

typedef std::vector<kaart_t>	kaarten_t;
kaarten_t Spel(void);

typedef struct
{
	kaarten_t	noord;
	kaarten_t	oost;
	kaarten_t	zuid;
	kaarten_t	west;
	kaarten_t	open;
	kaarten_t	dicht;
	kaarten_t	slapers;
}	potje_t;

potje_t	Deel(void);

void printHand(const kaarten_t & hand);
void printPot(const potje_t & potje);
