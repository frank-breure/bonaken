#include "bonaken.h"
#include <gtest/gtest.h>

TEST(BonakenTest, PrintKaart)
{
	kaart_t klaver_aas = { Klaveren, Aas };
	ASSERT_EQ(std::string("Kla-A "), std::string(strKaart(klaver_aas)));

	kaart_t schoppen_boer = { Schoppen, Boer };
	ASSERT_EQ(std::string("Sch-B "), std::string(strKaart(schoppen_boer)));
}

TEST(BonakenTest, SpelIsKompleet)
{
	kaarten_t	spel = Spel();
	ASSERT_EQ(32, spel.size());
	ASSERT_EQ(Schoppen, spel[0].soort);
	ASSERT_EQ(Zeven, spel[0].waarde);
	ASSERT_EQ(Ruiten, spel[31].soort);
	ASSERT_EQ(Aas, spel[31].waarde);
}

TEST(BonakenTest, DeelEenPotje)
{
	potje_t		potje = Deel();

	ASSERT_EQ(6, potje.noord.size());
	ASSERT_EQ(6, potje.oost.size());
	ASSERT_EQ(6, potje.zuid.size());
	ASSERT_EQ(6, potje.west.size());
	ASSERT_EQ(2, potje.open.size());
	ASSERT_EQ(1, potje.dicht.size());
	ASSERT_EQ(5, potje.slapers.size());

	printPot(potje);
}
