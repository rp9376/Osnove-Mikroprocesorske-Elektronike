/*
		FUNKCIJE

Pri programiranju funkcionalno smiselne skupke kode združujemo v funkcije.
Pri tej nalogi bomo zato na preprostem primeru ponovili, kako definiramo
funkcijo, kako funkcijo pokličemo ter kako shranimo njen rezultat.

Vaša naloge je, da implementirate matematično funkcijo sign(x). To je funkcija, 
ki vrača tri različne vrednosti: 
	-	1, če je število x pozitivno
	-	0, če je število x enako 0 ter
	-  -1, če je število x negativno.

Vhodni podatek "x" je realno število. (Več na https://en.wikipedia.org/wiki/Sign_function .)


Funkcijo boste stestirali z različnimi vrednostmi vhodnega podatka ter 
izpisali dobljene rezulate na standardni izhod s printf() funkcijo.


Sledite komentarjem spodaj in po potrebi //DOPOLNIte kodo.

*/



// Vključimo standardno C knjižnico za delo z vhodnimi/izhodnimi podatkovnimi tokovi.
#include <stdio.h>		// več na https://en.wikibooks.org/wiki/C_Programming/stdio.h


// Na tem mestu definirajte funkcijo sign(x).

int sign(float x)
{
	if(x > 0)
		return 1;
	if(x == 0)
		return 0;
	else
		return -1; 
}


int main(void)
{
	
	// Na tem mestu definirajte pomožno spremenljivko za vhodni podatek sign() funkcije
	// ter ji kar takoj nastavite testno vrednost.
	//DOPOLNI
	int a = 23, b = -42, c = 0; 
	
	// Definirajte tudi pomožno spremenljivko, ki bo hranila vrnjeni rezultat sign() funkcije.
	//DOPOLNI
	int vrnjeno; 
	
	// Sedaj pokličite sign() funkcijo s testno vhodno spremenljivko in rezultat shranite
	// v pomožno spremenljivko.
	//DOPOLNI

	vrnjeno = sign(a);
	printf("%d\n", vrnjeno);

	vrnjeno = sign(b);
	printf("%d\n", vrnjeno);

	vrnjeno = sign(c);
	printf("%d\n", vrnjeno);
	
	// In nato s printf() izpišite sporočilo v sledeči obliki:
	// "Vrednost sign() funkcije za 1.23 je enaka 1."
	//DOPOLNI
	
	
	// Preverite za različne vhodne vrednosti, ali vaša sign() funkcija
	// deluje pravilno.
	
	
    // In zaključimo funkcijo main().
	return 0;
	
	
}

