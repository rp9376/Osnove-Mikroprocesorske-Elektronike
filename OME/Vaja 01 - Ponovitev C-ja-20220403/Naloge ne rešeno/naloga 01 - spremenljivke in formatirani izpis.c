/*
		SPREMENLJIVKE in FORMATIRANI IZPIS s printf()

Pri tej nalogi bomo obnovili znanje o deklaracijah spremenljivk različnih vrst.
Spomnili se bomo tudi, kako lahko s pomočjo funkcije printf() zelo enostavno
oblikujemo formatirana sporočila, kjer se vrednosti spremenljivk elegantno 
vgradijo v besedilo sporočila.

Izpisovanje sporočil s printf() v standardni izhod (tj. "stdout") je zelo uporabno orodje, 
ki nam pogosto pomaga pri programiranju in odkrivanju napak. Kasneje tekom
semestra bomo za Miškota3 funkcijo printf() priredili tako, da bo formatirana sporočila 
pošiljala preko serijskega vmesnika na računalnik.


Sledite komentarjem spodaj in po potrebi dopolnite kodo.

*/



// Vključimo standardno C knjižnico za delo z vhodnimi/izhodnimi podatkovnimi tokovi.
#include <stdio.h>		// več na https://en.wikibooks.org/wiki/C_Programming/stdio.h


// Sedaj na tem mestu najprej definiramo globalne spremenljivke, ki jih bomo
// nato izpisali s printf().


	// celoštevilska spremenljivka "a" naj bo enaka 65
	DOPOLNI
	
	// celoštevilska spremenljivka "b" tipa "long" naj drži veliko vrednost 64000000000
	DOPOLNI
	
	// celoštevilska spremenljivka "c" tipa "unsigned" naj bo enaka 4000000000
	DOPOLNI
	
	// znakovno spremenljivko "d", ki hrani znak 'a'
	DOPOLNI
	
	// spremenljivko "message", ki je znakovni niz in je enak "Hello world!"
	DOPOLNI
	
	// realno spremenljivko "pi", ki hrani vrednost 3.14159
	DOPOLNI
	
	// ter realno spremenljivko "g" z zelo majhno vrednostjo 0.00000000000000000000123456789
	DOPOLNI





// Sedaj bomo pa znotraj main() funkcije s pomočjo funkcije printf() izpisali vrednosti 
// zgornjih spremenljivk.

// Pri tem si lahko pomagate z dokumentom "C Reference Card (ANSI)" s poglavjem "Codes for Formatted I/O".
// Na spletu pa najdete več o funkciji printf() tule: 
// https://www.gnu.org/software/libc/manual/html_node/Table-of-Output-Conversions.html


int main(void)
{
	
	// Tu spodaj izpisujemo s printf(). Za vsako spremenljivko napravite 
	// izpis oblike 
	//
	// 		"Vrednost spremenljivke a je enaka [vrednost spremenljivke]."
	//
	// Vsakemu izpisu na konec dodajte še poseben znak za pomik v naslednjo vrstico "\n".


	// izpišimo celoštevilsko spremenljivko "a"
	printf("Vrednost spremenljivke a je enaka %d.\n", a);

	// izpišimo celoštevilsko spremenljivko "a" kot heksadecimalno število s predpono "0x"
	DOPOLNI
	
	
	// izpišimo celoštevilsko spremenljivko "b", ki vsebuje veliko vrednost
	DOPOLNI
		
	// izpišimo nepredznačeno celoštevilsko spremenljivko "c"
	DOPOLNI
	
	
	
	// izpišimo znakovno spremenljivko "d"
	DOPOLNI
	
	// izpišimo znakovni niz "message"
	DOPOLNI
	

	
	// izpišimo realno spremenljivko "pi" na 3 decimalna mesta natančno
	DOPOLNI
	
	// izpišimo realno spremenljivko "g" v eksponentni obliki (angl. scientific notation)
	// na 2 decimalni mesti natančno
	DOPOLNI
	
	
	
	
    // In zaključimo funkcijo main().
	return 0;
	
	
}