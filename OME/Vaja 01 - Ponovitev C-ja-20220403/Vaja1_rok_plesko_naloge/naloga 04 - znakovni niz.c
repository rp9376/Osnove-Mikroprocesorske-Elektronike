/*
		ZNAKOVNI NIZI

Pri tej nalogi boste obonovili znanje o zgradbi znakovnega niza (angl. string).
Hkrati boste osvežili tudi znanje za delo z zankami.

Vaša naloga bo, da implementirate funkcijo za kopiranje znakovnega niza ter
da nato funkcijo stestirate.


Sledite komentarjem spodaj in po potrebi dopolnite kodo.


*/



// Vključimo standardno C knjižnico za delo z vhodnimi/izhodnimi podatkovnimi tokovi.
#include <stdio.h>		// več na https://en.wikibooks.org/wiki/C_Programming/stdio.h


// Tukaj implementirajte funkcijo za kopiranje znakovnega niza copy_str( source, dest ), ki naj ima
// dva vhodna parametra:
//		1. source 	= znakovni niz, ki ga želimo skopirati
//		2. dest 	= znakovni niz, kamor želimo skopirati vsebino niza "source"
// 
// Namig: ne pozabite, da so znakovni nizi t. i. "null terminated". To pomeni, da na koncu niza stoji
// poseben znak, ki ima vrednost enako 0. Ne pozabite skopirati tudi tega znaka!
void copy_str(char source[], char dest[])
{
	for(int i = 0; source[i] != 0; i++)
		dest[i] = source[i];
}



// Sedaj pa v glavnem programu stestirajte zgornjo funkcijo za kopiranje znakovnega niza.

int main(void)
{
	// Definirajte prvi niz, ki bo služil kot "source" in ga inicializirajte na "Hey!"
	char prvi[50] = "Hey!";
	
	// Definirajte drugi niz, v katerega bomo kopirali, in ga inicializirajte na "Hello world!"
	char drugi[50] = "";
	
	
	// Najprej izpišite s printf() vsebini obeh nizov.
	printf("source = %s\n", prvi);
	printf("dest = %s\n", drugi);
	
	// Sedaj pa uporabite funkcijo za kopiranje niza.
	copy_str(prvi, drugi);
	
	
	// In ponovno izpišite vsebini obeh nizov.
	printf("source = %s\n", prvi);
	printf("dest = %s\n", drugi);
	
	
	// Je kopiranje uspelo?
	
	
	
    // In zaključimo funkcijo main().
	return 0;
	
	
}