/*
		TABELE

Pri tej nalogi bomo obnovili znanje za delo s tabelami. To bomo storili na
primeru implementacije funkcije, ki izračuna povprečno vrednost elementov 
v tabeli. 

Srečali se boste tudi še z dvema detajloma.

Prvi detajl vas bo spomnil, kako lahko s pomočjo predprocesorskega ukaza #define 
ustvarimo makro, ki na enem samem mestu hrani pomembno informacijo, ki jo nato lahko
uporabimo na različnih mestih v kodi.


Drugi detajl, na katerega pa boste mogoče naleteli, je t. i. eksplicitna pretvorba 
med podatkovnimi tipi (angl. type cast).
(več na https://www.tutorialspoint.com/cprogramming/c_type_casting.htm )
Taka pretvorba je včasih nujna, da resnično dobimo številski rezultat, ki si ga želimo.



Sledite komentarjem spodaj in po potrebi dopolnite kodo.


*/



// Vključimo standardno C knjižnico za delo z vhodnimi/izhodnimi podatkovnimi tokovi.
#include <stdio.h>		// več na https://en.wikibooks.org/wiki/C_Programming/stdio.h


// Na tem mestu definirajmo makro ARRAY_SIZE, ki bo za nas hranil dolžino tabele,
// nad katero bomo izvajali operacije. Naj tabela vsebuje 5 elementov.

#define ARRAY_SIZE 5



// Sedaj pa tu definirajmo funkcijo array_average(array, size), ki naj ima dva vhodna parametra:
// 		1.	array = tabela celoštevilskih vrednosti 
// 		2.	size = dolžina tabele
//
// Funkcija naj vrača realno vrednost, ki je povprečna vrednost elementov v tabeli.

float array_average(int array[], int size)
{
	float sum = 0;
	for(int i = 0; i < size; i++)
		sum += array[i];
	return (sum/size);
}


// Sedaj pa v glavnem programu pripravimo tabelo ocen in izračunajmo
// povprečno oceno.

int main(void)
{
	// Definirajte tabelo zgoraj določene dolžine in ji
	// nastavite začetne vrednosti elementov takole: 7,9,7,10,8.
	// Elementi tabela naj bodo celoštevilske vrednosti.
	
	int tab[ARRAY_SIZE] = {7,9,7,10,8};
	
	
	// Definirajte realno spremenljivko, ki bo hranila povprečno oceno.
	float vrnjena;
	
	
	// Sedaj pa pokličite funkcijo za izračun povprečne vrednosti tabele.
	vrnjena = array_average(tab, ARRAY_SIZE);
	
	// In izpišite povprečno oceno s printf().
	printf("%f", vrnjena);
	
	
	// Preverite, ali ste dobili pravilen rezultat. Za ocene 7,9,7,10,8
	// je pravilno izračunano povprečje 8,2. Če je vaš rezultat drugačen,
	// imate težave s pretvorbami med tipi spremenljivk. Premislite,
	// kaj se zgodi v ukazu za izračun povprečne vrednosti.
	
	
	
    // In zaključimo funkcijo main().
	return 0;
	
	
}