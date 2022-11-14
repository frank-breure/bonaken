#include "bonaken.h"
#include <gtest/gtest.h>

TEST(BonakenTest, PrintKaart)
{
	kaart_t klaver_aas = { Klaveren, Aas };
	EXPECT_EQ(std::string("Kla-A "), std::string(strKaart(klaver_aas)));

	kaart_t schoppen_boer = { Schoppen, Boer };
	EXPECT_EQ(std::string("Sch-B "), std::string(strKaart(schoppen_boer)));
}

TEST(BonakenTest, SpelIsKompleet)
{
	kaarten_t	spel = Spel();
	EXPECT_EQ(32, spel.size());
	EXPECT_EQ(Schoppen, spel[0].soort);
	EXPECT_EQ(Zeven, spel[0].waarde);
	EXPECT_EQ(Ruiten, spel[31].soort);
	EXPECT_EQ(Aas, spel[31].waarde);
}

TEST(BonakenTest, DeelEenPotje)
{
	potje_t		potje = Deel();

	EXPECT_EQ(6, potje.noord.size());
	EXPECT_EQ(6, potje.oost.size());
	EXPECT_EQ(6, potje.zuid.size());
	EXPECT_EQ(6, potje.west.size());
	EXPECT_EQ(2, potje.open.size());
	EXPECT_EQ(1, potje.dicht.size());
	EXPECT_EQ(5, potje.slapers.size());

	printPot(potje);
}

TEST(BonakenTest, OpeenVolgendeRoem)
{
	kaarten_t drie_kaart = { { Schoppen, Zeven }, { Klaveren, Zeven }, { Klaveren, Acht }, { Klaveren, Negen }, { Ruiten, Tien }, { Harten, Negen } };

	EXPECT_EQ(20, vindRoem(drie_kaart));

	kaarten_t drie_kaart_1 = { { Schoppen, Zeven }, { Schoppen, Acht }, { Schoppen, Tien }, { Klaveren, Zeven }, { Klaveren, Acht }, { Klaveren, Negen } };

	EXPECT_EQ(20, vindRoem(drie_kaart));

	kaarten_t twee_drie_kaarten = { { Schoppen, Zeven }, { Schoppen, Acht }, { Schoppen, Negen }, { Klaveren, Zeven }, { Klaveren, Acht }, { Klaveren, Negen } };

	EXPECT_EQ(40, vindRoem(twee_drie_kaarten));

	kaarten_t vier_kaart = { { Schoppen, Zeven }, { Klaveren, Zeven }, { Klaveren, Acht }, { Klaveren, Negen }, { Klaveren, Tien }, { Harten, Negen } };
	EXPECT_EQ(50, vindRoem(vier_kaart));

	kaarten_t vijf_kaart = { { Schoppen, Zeven }, { Klaveren, Acht }, { Klaveren, Negen }, { Klaveren, Tien }, { Klaveren, Boer }, { Klaveren, Vrouw } };
	EXPECT_EQ(100, vindRoem(vijf_kaart));
}

TEST(BonakenTest, RoemMetVierkaarten)
{
	kaarten_t vier_kaart_boeren = { { Schoppen, Zeven }, { Schoppen, Boer }, { Schoppen, Aas }, { Klaveren, Boer }, { Ruiten, Boer }, { Harten, Boer } };

	EXPECT_EQ(200, vindRoem(vier_kaart_boeren));

	kaarten_t vier_kaart_heren = { { Schoppen, Zeven }, { Schoppen, Heer }, { Schoppen, Aas }, { Klaveren, Heer }, { Ruiten, Heer }, { Harten, Heer } };

	EXPECT_EQ(100, vindRoem(vier_kaart_heren));

	kaarten_t vier_kaart_negens = { { Schoppen, Zeven }, { Schoppen, Negen }, { Schoppen, Aas }, { Klaveren, Negen }, { Ruiten, Negen }, { Harten, Negen } };;
	EXPECT_EQ(0, vindRoem(vier_kaart_negens));
}
