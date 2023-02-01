/*
		NAŠTEVNI TIP ENUM - DEMONSTRACIJA


Pri tej nalogi si bomo ogledali pomen naštevnega tipa, ki ga ustvarimo z ukazom "enum".
Naštevni tip bomo uporabljali v dveh korakih:
	1. najprej bomo definirali nov naštevni tip s pomočjo dodatnega ukaza "typedef"
	2. nato pa bomo s tem novim naštevnim tipom definirali spremenljivko

Naloga vam bo pokazala, da naštevni tip ne stori nič drugega, kot da elementom
naštevnega tipa pripiše zaporedne številke od 0 dalje (privzeta možnost).
V naslednjih nalogah pa bomo pogledali, kako te oštevilčene elemente lahko
smiselno uporabljamo pri programiranju.

Sledite komentarjem spodaj in po potrebi dopolnite kodo.

*/



// Vključimo standardno C knjižnico za delo z vhodnimi/izhodnimi podatkovnimi tokovi.
#include <stdio.h>		// več na https://en.wikibooks.org/wiki/C_Programming/stdio.h


/*

V prvem koraku torej najprej definiramo novi naštevni tip z ukazom "typdef". 
Za primer demonstracije želimo definirati naštevni tip, ki bo vseboval vse dni v tednu.
Uporabimo kar angleška imena in to storimo takole:


       ukaz za definicijo 
	     naštevnega tipa
              |
             _|_
            /   \   =0       =1        =2        =3       =4        =5       =6                       */
	typedef enum { Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday } weekdays_enum_t;
/*	\_____/ 	 \________________________________________________________________/ \______________/
       |                                         |                                         |       
       |                                         |                                         |         
   ukaz za                             naštejemo elemente, ki jih                 poimenovanje novega 
  definicijo                          želimo imeti združene v tem                       tipa        
  novega tipa                                 novem tipu;                        (je še del tydef ukaza);    
                                    vrstni red je pomemben, saj določa             ponavadi novim tipom
                                    vrednost števila, ki se pripiše             na koncu dodamo pripono "_t"
                                         posameznemu elementu                 in s pripono "_enum" nakažemo še,
                                       (glejte vrednosti zgoraj)               da je novi tip naštevni tip
*/



// Sedaj imamo na voljo nov tip z imenom "weekdays_enum_t", s pomočjo katerega lahko 
 //v naslednjem koraku definiramo spremenljivko. To storimo takole:

weekdays_enum_t   day;

// Na popolnoma enak način kot bi npr. definirali integer spremenljivko:    int i;


// Sedaj imamo na voljo globalno spremenljivko "day", ki lahko prevzame vrednost kateregakoli
// elementa, ki smo ga navedli znotraj zavitih oklepajev { } pri zgornji definiciji, torej "Monday", 
// "Tuesday" itd.

// Preizkusimo to v glavnem programu.


int main(void)
{

	// Poskusimo prirediti spremenljivki "day" vrednost "Monday" in nato	
	// izpišimo njeno vrednost s printf().
	day = Monday;
	
	// Pri izpisu s printf() upoštevamo, da se v spremenljivki naštevnega
	// tipa pravzaprav skriva celoštevilska vrednost, zato za formatno 
	// določilo uporabimo "%d".
	printf("Vrednost spremenljivke day je sedaj enaka %d\n", day);
	
	
	// Poskusimo izpisati še nekaj drugih vrednosti.
	// Na primer, če spremenljivko "day" nastavimo na "Wednesday".
	day = Wednesday;
	printf("Vrednost spremenljivke day je sedaj enaka %d\n", day);
	
	
	// In pa na primer, če spremenljivko "day" nastavimo na "Sunday".
	day = Sunday;
	printf("Vrednost spremenljivke day je sedaj enaka %d\n", day);
	
	
	// Sedaj ste se prepričali, da za elementi naštevnega tipa
	// resnično pravzaprav stojijo le cela števila.
	// Definicija naštevnega tipa je torej seznamu elementov (tj. Monday, Tuesday ...)
	// le priredila zaporedna števila od 0 dalje.
	
	
	// Sedaj pa v naslednjih dveh nalogah poglejmo, kako lahko take oštevilčene
	// sezname pametno uporabimo pri programiranju.
	
	
	
	// Mimogrede, če bi želeli seznamu imen prirediti poljubna števila, se to 
	// lahko naredi npr. takole:
	// typedef enum { Jabolko=1, Banana=3} dva_sadeza_enum_t;
	
	
	
    // In zaključimo funkcijo main().
	return 0;
	
	
}