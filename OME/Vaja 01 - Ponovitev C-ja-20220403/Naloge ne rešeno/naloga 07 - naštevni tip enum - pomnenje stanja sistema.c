/*
	NAŠTEVNI TIP ENUM - POMNENJE STANJA SISTEMA

Pri tej nalogi pa bomo pokazali, kako lahko spremenljivko naštevnega tipa uporabimo,
da za nas hrani pomembno informacijo o stanju sistema. Še drugače povedano: naštevni tip
lahko uporabimo, da za nas "zakodira" različna stanja sistema. Poglejmo kako.

Idejo si bomo pogledali na sledečem praktičnem primeru: imate mikrokrmilniški sistem 
in vaša naloga je, da spremljate, katera tipka sistema je bila pritisnjena nazadnje.
Poglejmo, kako si lahko v takem primeru pomagamo z naštevnim tipom.


Sledite komentarjem spodaj in po potrebi dopolnite kodo.

*/



// Vključimo standardno C knjižnico za delo z vhodnimi/izhodnimi podatkovnimi tokovi.
#include <stdio.h>		// več na https://en.wikibooks.org/wiki/C_Programming/stdio.h


// Naštevni tip bomo uporabili tako, da bomo z njim definirali vse tipke, ki jih mikrokrmilniški 
// sistem ima: torej tipke "OK", "Escape", "left arrow", "right arrow". 
//
// Vidite, da sistem pozna štiri tipke. Vendar pa bomo naštevni tip definirali z dvema dodatnima
// elementoma takole:

//              =0       =1        =2        =3             =4          =5
typedef enum { BTN_OK, BTN_ESC, BTN_LEFT, BTN_RIGHT, NUM_OF_BUTTONS, BTN_NONE }  buttons_enum_t;

// Vidite, da smo na začetku seznama definirali elemente za vse štiri resnične tipke sistema.
// Nato smo na konec seznama dodali "NUM_OF_" element, ki bo za nas hranil število vseh tipk v sistemu.
// In prav na konec seznama pa smo dodali še namišljeno oz. fiktivno tipko "BTN_NONE", ki 
// pravzaprav predstavlja situacijo, ko ni bila pritisnjena nobena tipka.


// Sedaj pa definiramo še spremenljivko zgoraj definiranega tipa "buttons_enum_t", ki bo za nas
// hranila informacijo o nazadnje pritisnjeni tipki (tj. o stanju sistema).
DOPOLNI		last_pressed_button;



// Sedaj pa pogeljmo spodaj, kako bi se taka spremenljivka uporabljala v pravem programu.


int main(void)
{
	// Iz branja digitalnih vhodov v mikrokrmilnik bi npr. ugotovili,
	// da je bila pritisnjena tipka ESC. In to informacijo bi si zato
	// shranili v pripravljeno spremenljivko naštevnega tipa takole:
	last_pressed_button = BTN_ESC;
	
	
	// In ko bi bilo potrebno na različne pritiske tipk ukrepati
	// na različne načine, bi lahko nad spremenljivko "last_pressed_button" 
	// uporabili stavek "switch-case" in obdelali vsako od možnosti posebej:
	switch (last_pressed_button)
	{
		case BTN_OK:
			printf("Pritisnjena je bila tipka OK.\n");
			break;

		case DOPOLNI:
			printf("Pritisnjena je bila tipka ESC.\n");
			break;

		case DOPOLNI:
			printf("Pritisnjena je bila tipka LEFT ARROW.\n");
			break;

		case DOPOLNI:
			printf("Pritisnjena je bila tipka RIGHT ARROW.\n");
			break;

		// Ne pozabimo na primer, ko ni bila pritisnjena nobena tipka.
		case DOPOLNI:
			printf("Nobena tipka ni bila pritisnjena.\n");
			break;

		default:
			break;
	}

	
	// Poglejte, kako je zgornja koda za obdelavo tipk postala s pomočjo
	// naštevnega tipa pregledna, smiselna, zgovorna in berljiva.
	
	// Pri programiranju Miškota3 boste uporabili podoben pristop za
	// implementacijo tipkovnice sistema.
	
	
	// Lahko še poskusite spreminjati vrednost 
	// spremenljivke "last_pressed_button" zgoraj.
	
	
    // In še zaključimo funkcijo main().
	return 0;
	
	
}