/*
		DELO S STRUKTURAMI

Pogosta praksa pri programiranju vgrajenih sistemov je ta, da za vsako periferno enoto
ali pa napravo na sistemskem nivoju vpeljemo posebno podatkovno strukturo, ki vsebuje
vse potrebne parametre za delo s posamezno enoto oziroma napravo.

Idejo bomo poskusili predstaviti na matematičnem primeru: za delo s kvadratno krivuljo
oblike 
	
	y(x) = a*x^2 + b*x + c

bomo vpeljali podatkovno strukturo, ki bo hranila vse potrebne parametre za izračune,
povezane s kvadratno krivuljo, torej  parametre "a", "b" in "c".

Nato bomo definirali posebno inicializacijsko funkcijo, ki nam bo pomagala nastaviti 
parametre kriulje. Nazadnje pa bomo implementirali še funkcijo, ki bo za podane parametre
krivulje izračunala vrednost krivulje pri dani koordinati "x".


V nadaljevanju bodite pozorni na sledeče koncepte:

	1.	da parametre za delo z neko rečjo (v našem primeru s kvadratno krivuljo) združujemo v strukture;
	
	2.	da za delo z neko rečjo (tj. krivuljo) razvijamo funkcije, ki kot vhodni podatek dobijo 
		referenco (kazalec) na ustrezno strukturo parametrov;
	
	3. 	kako dostopamo do parametrov strukture, če s strukturo rokujemo s pomočjo reference (kazalca);
	
	3. 	kako dostopamo do parametrov strukture, če imamo neposredni dostop do spremenljivke strukture.
	


Sledite komentarjem spodaj in po potrebi dopolnite kodo.


*/


// Vključimo standardno C knjižnico za delo z vhodnimi/izhodnimi podatkovnimi tokovi.
#include <stdio.h>		// več na https://en.wikibooks.org/wiki/C_Programming/stdio.h


// Kot že nakazano zgoraj, bomo najprej definirali posebno strukturo za delo s kvadratnimi krivuljami.
// To bomo storili v dveh korakih: najprej bomo s "typedef" ukazom definirali nov tip strukture, 
// nato pa bomo definirali še dejansko strukturno spremenljivko takega tipa. Poglejmo kako.

// Definirajmo najprej nov tip strukture takole:
typedef struct
{
	float  a;		// parameter "a"
	DOPOLNI			// parameter "b"
	DOPOLNI			// parameter "c"
	
} square_function_parameters_t;

// Tako smo definirali nov tip strukture z imenom "square_function_parameters_t", pri čemer
// struktura takega tipa vsebuje tri spremenljivke oziroma parametre tipa "float": "a", "b" in "c".
//
// V glavnem main() programu pa bomo kasneje definirali še dejansko spremenljivko  
// tipa "square_function_parameters_t", ki bo hranila parametre naše krivulje. 

// Na tem mestu definirajmo še dve funkciji za delo s krivuljami: funkcijo za inicializacijo 
// parametrov krivulje ter funkcijo za izračun vrednosti krivulje pri dani koordinati "x".

// Implementirajmo najprej inicializacijsko funckijo za nastavitev parametrov krivulje. Kako se lotiti tega?
// To storimo tako, da inicializacijski funkciji kot vhodni parameter posredujemo:
// 		1.	referenco na strukturo parametrov (tj. kazalec na strukturo parametrov)
// 		2.	ter vrednosti parametrov "a", "b" in "c", ki jih bomo shranili v strukturo.
//
// S tem razmislekom oblikujemo inicializacijsko funkcijo takole:
void square_function_init( square_function_parameters_t *param, float a, float b, float c )
{
	// Prvi vhodni podatek funkcije je 
	//		square_function_parameters_t *param
	//
	// Opazite zvezdico zraven imena spremenljivke? Torej je prvi vhodni podatek funkcije 
	// kazalec na strukturo "tipa square_function_parameters_t"! 
	// Funkciji je torej posredovana REFERENCA na strukturo!
	
	// Kako torej dostopamo preko kazalca na strukturo "param" do parametra "a" znotraj strukture?
	// Če uporabimo za dereferenciranje zvezdico "*", potem bi to lahko naredili takole
	//
	//			(*param).a = ...
	//
	// Vendar pa se v praksi izogibamo take nerodne notacije in običajno uporabimo 
	// t.i. "operator puščice" "->", takole
	//
	// 			param->a = ...
	//
	// (Več o tem v učbeniku "Osvojimo C" (Fajfar), stran 137.)
	
	// Torej, če želimo shraniti vrednost parametra "a" v strukturo krivulje, na katero kaže
	// kazalec "param", potem to storimo takole
	param->a = a;	
	
	// Storimo podobno še za parametra "b" in "c".
	DOPOLNI
	DOPOLNI
	
	
	// In tako smo si pripravili inicializacijsko funkcijo, ki nam bo pomagala "inicializirati 
	// kvadratno krivuljo".
	
}


// Sedaj pa spišimo še funkcijo, ki nam bo na podlagi posredovanih parametrov krivulje izračunala
// vrednost krivulje za dano vrednost koordinate "x". Funkcija mora torej vrniti realno število,
// zato jo definiramo takole
float square_function_value( square_function_parameters_t *param, float x )
{
	// Prvi parameter je enako kot prej referenca (kazalec) na strukturo parametrov krivulje,
	// drugi parameter pa je realna vrednost koordinate "x", pri kateri nas zanima vrednost 
	// "y" koordinate krivulje.
	
	// Po definiciji izračunamo vrednost y(x) = a*x^2 + b*x + c,
	// pri čemer vrednosti parametrov "a", "b" in "c" dobimo iz strukture,
	// ki nam je posredovana preko reference "param". 
	// Ne pozabite, da jezik C ne pozna potenciranja z operatorjem "^".
	// Tako sledi
	return (   param->a * x*x + DOPOLNI   );
	
}



// Sedaj pa preizkusimo zgoraj zastavljeno rešitev v glavnem programu.


int main(void)
{
	
	// Najprej v glavnem programu definiramo lokalno strukturno spremenljivko,
	// ki bo hranila parametre naše krivulje.
	square_function_parameters_t	parametri_krivulje;
	
	
	// Nato z inicializacijsko funkcijo nastavimo vrednosti parametrov 
	// naše kvadratne krivulje.
	// Naj bo 
	//	 	a = 1
	//		b = -5
	//		c = 2
	//
	// Pokličemo torej inicializacijsko funkcijo in ji posredujemo referenco
	// na strukturo parametrov ter zgornje vrednosti parametrov.
	square_function_init( &parametri_krivulje, DOPOLNI, DOPOLNI, DOPOLNI );
	
	// Vidite, da referenco na strukturo parametrov posredujemo tako,
	// da posredujemo naslov strukture z opratorjem "&".
	
	
	// Preizkusimo, ali inicializacijska funkcija deluje pravilno.
	// Kako? Kar neposredno dostopajmo do parametrov strukture v 
	// spremenljivki "parametri_krivulje" in jih izpišimo.
	printf("parameter a = %.2f\n", parametri_krivulje.a );
	
	// POGLEJTE, kako pa dostopamo do parametrov strukture, če rokujemo 
	// neposredno s strukturno spremenljivko! Uporabimo piko "." namesto puščice "->"!
	// Na podoben način izpišimo še preostala dva parametra.
	printf("parameter b = %.2f\n", DOPOLNI );
	printf("parameter c = %.2f\n", DOPOLNI );
	
	
	
	// Sedaj pa še izračunajmo vrednost koordinate "y" za x = 5.
	// Pokličemo torej ustrezno funkcijo in ji posredujemo referenco
	// na strukturo parametrov ter vrednost koordinate "x".
	// Rezultat shranimo v pomožno spremenljivko "y".
	float y;
	y = square_function_value( DOPOLNI, DOPOLNI );
	
	// In dobljeni rezultat izpišemo.
	printf("vrednost y(5) = %.2f\n", y );
	
	
	
	
	// In na tak način smo pripravili sistematično urejeno orodje, ki omogoča,
	// da enostavno dodajamo nove kvadratne krivulje ter za njih elegantno
	// računamo vrednosti točk v koordinatni ravnini. 
	
	// Tovrstni pristop za delo z različnimi rečmi (v našem primeru s krivuljami)
	// je razmeroma sistematičen in modularen, kar pa omogoča
	// enostavno razširljivost in enostavne modifikacije
	// (zelo enostavno bi npr. dodali še funkcijo za izračun ničel na podlagi 
	// parametrov krivulje).
	//
	// Zato se tudi v praksi pogosto poslužimo enake metodologije: 
	// za periferne enote oziroma naprave v sistemu definiramo strukture,
	// ki bodo hranile vse potrebne parametre za delo z enoto oz. napravo.
	// Potem pa spišemo funkcije, ki enoti oz. napravi dodajo ustrezno funkcionalnost.
	// In enak način bomo uporabili tudi mi pri Miškotu za implementacijo sistemskih naprav!
	
	
	
	
    // In še zaključimo funkcijo main().
	return 0;
	
	
}