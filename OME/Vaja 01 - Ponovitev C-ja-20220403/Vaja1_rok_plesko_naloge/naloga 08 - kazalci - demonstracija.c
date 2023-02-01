/*
		KAZALCI - DEMONSTRACIJA

Pri tej nalogi bomo osvežili znanje za delo s kazalci (angl. pointers). 

Spomnimo naj, da kazalce uporabljamo, kadar želimo delati s podatki "na kraju njihovega mesta",
torej tam, kjer se podatki dejansko nahajajajo v spominu. Alternativna možnost
bi bila, da prenesemo dejanske vrednosti podatkov in potem delamo s temi "kopijami"
podatkov. To pa je neugodno takrat, kadar imamo opravka z večjimi količinimami podatkov,
npr. s tabelami ali pa z večjimi strukturami. Zato takrat običajno uporabljamo reference na
podatke kot pa ustvarjamo kopije podatkov.

Ker bomo pri programiranju z Miškotom veliko delali s strukturami, je smiselno, da obnovimo
znanje o kazalcih, saj bomo strukturo pogosto posredovali funkcijam tako, da bomo posredovali
zgolj naslov na to strukturo (tj. ustvarili bomo kazalec na strukturo).

Poglejmo si torej osnovne principe za delo s kazalci.


Sledite komentarjem spodaj in po potrebi dopolnite kodo.

// Za morebitno dodatno razlago se lahko obrnete v učbenik "Osvojimo C" (Fajfar) na stran 65.


*/



// Vključimo standardno C knjižnico za delo z vhodnimi/izhodnimi podatkovnimi tokovi.
#include <stdio.h>		// več na https://en.wikibooks.org/wiki/C_Programming/stdio.h



int main(void)
{
	
	// Definirajmo najprej preprosto celoštevilsko spremenljivko, ki bo služila
	// kot primer podatka s katerim želimo delati.
	int d = 7;
	
	
	// Sedaj pa definirajmo še kazalec, ki ga bomo uporabljali za delo s podatkom,
	// ki ga hrani spremenljivka "d". 
	//
	// Potrebujemo torej kazalec na spremenljivko celoštevilskega tipa "int". 
	// Deklaracije takega tipa kazalca se lotimo na enak način kot deklaracije
	// spremenljivke "d", torej
	//
	//			int pc;
	//
	// Le da pred ime spremenljivke pišemo zvezdico "*", torej takole
	int *pd;
	
	
	// Tako smo dobili kazalec "pd", vendar pa ta kazalec še ni nastavljen.
	// To pomeni, da še ne kaže na nobeno spremenljivko.
	
	// Kazalec bomo nastavili tako, da bomo vanj shranili naslov
	// spremenljivke "d". 
	//
	// Kako pa se dokopljemo do naslova spremenljivke "d"? Tako, da uporabimo
	// t.i. naslovni operator "&" (angl. address operator) v navezi s spremenljivko "d".
	// Torej sledi
	pd = &d;	
	
	// Na ta način smo v kazalec "pd" shranili NASLOV spremenljivke "d".
	
	
	// Če bi sedaj izpisali vrednost kazalca "pd", bi dobili nekakšno veliko
	// celoštevilsko vrednost, ki pa nam programerjem ne pomeni ničesar.
	//
	// Poskusimo izpisati vrednost kazalca kot "unsigned long" vrednost:
	printf("Vrednost kazalca pd = %lu\n", ((unsigned long)pd) );
	
	
	// Da se vrnemo nazaj: kazalec je sedaj nastavljen tako, da kaže na 
	// spremenljivko "d", s katero želimo "delati preko reference", 
	// torej s pomočjo kazalca "pd".
	//
	// Poglejmo torej, kako lahko beremo vrednost spremenljivke "d"
	// s pomočjo kazalca (reference).
	// Če želimo prebrati vrednost, na katero kaže kazalec, potem
	// pred ime kazalca "pd" pišemo zvezdico "*", takole:
	printf("Vrednost spremenljivke, na katero kaže pd = %d\n",  *pd );
	
	
	// V žargonu pravimo tudi, da z zvezdico * "dereferiramo" kazalec.
	
	
	// Če pa želimo v spremenljivko, na katero kazalec "pd" kaže,
	// shraniti vrednost, potem pa na podoben način uporabimo zvezdico "*",
	// le da sedaj "*pd" nastopa na levi strani prireditvenega enačaja, takole:
	*pd = 12;
	
	// Sedaj smo s pomočjo kazalca (tj. reference) vrednost spremenljivke "d"
	// nastavili na 12! Preverimo, če to drži:
	printf("Nova vrednost spremenljivke d = %d\n" , d);
	
	
	// Če na stvar pogledamo drugače: ko enkrat nastavimo kazalec "pd" tako,
	// da kaže na spremenljivko "d", potem lahko za delo s spremenljivko "d"
	// uporabljamo dereferirani kazalec "*pd".
	//
	// Uporabimo dereferirani kazalec še zadnjič, da preverimo novo 
	// vrednost spremenljivke "d".
	printf("Vrednost spremenljivke, na katero kaže pd, je sedaj %d\n",  *pd);
	
	
	// V naslednji nalogi pa si bomo pogledali zelo uporaben primer, 
	// kako s pomočjo kazalcev prenašamo reference na strukture
	// in kako potem s tako posredovano strukturo rokujemo na
	// na nekoliko poseben način.
	
	
	
    // In še zaključimo funkcijo main().
	return 0;
	
	
}