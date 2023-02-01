/*
 * SCI.c
 *
 *  Created on:
 *      Author:
 */


/* **************** MODULE DESCRIPTION *************************

Ta modul implementira serijski komunikacijski vmesnik (SCI) na sistemskem nivoju.
SCI vmesnik nudi serijsko povezavo z osebnim računalnikom preko periferne USART enote.
Z drugumi besedami: SCI vmesnik je implementiran z USART vmesnikom (lahko bi namreč
uporabili kak drug serijski vmesnik za implementacijo SCI vmesnika).

Podprta sta dva tipa prenosa podatkov preko SCI:

	1. prenos znakov (uporablja se za prenos besedilnih sporočil),

	2. prenos binarnih podatkov (uporablja se za prenos binarnih podatkov).


Poleg tega sta na voljo dve vrsti funkcij za pošiljanje "send":

	1. za pošiljanje enega samega znaka ali enega bajta podatkov

	2. za pošiljanje niza znakov ali zaporedja bajtov


POZOR: za uspešno uporabo modula je potrebno predhodno poskrbeti
za ustrezno nizko-nivojsko inicializacijo USART vmesnika.

************************************************************* */




// ----------- Include other modules (for private) -------------

#include "SCI.h"

#include <stdio.h>			// dodamo printf() funkcionalnost



// ---------------------- Private definitions ------------------


// ------ Definicje v zvezi z SCI -------


// Definiramo tip "handle" strukture "SCI_handle_t", ki jo bomo uporabili za upravljanje SCI.
// V strukturi je pravzaprav potrebno pomniti le, katera USART periferna enota bo uporabljena.

//DOPOLNI
{
	//DOPOLNI

} SCI_handle_t;



// In sedaj na podlagi zgoraj definiranega tipa definiramo še globalno strukturno spremenljivko "SCI".

//	DOPOLNI







// ------ printf() customization definitions -----


// V zgornjem delu SCI.c datoteke definiramo prototip funkcije
//
//		int _write(int file, char *ptr, int len)
//
// s pomočjo katere bomo lahko priredili uporabo printf() funkcije tako, da bo
// sporočila pošiljala preko SCI vmesnika (tj. redefinirali bomo pošiljanje sporočil
// preko standardnega izhoda "stdout").
int _write(int file, char *ptr, int len);







// -------------- Public function implementations --------------


// Funkcija SCI_init() poskrbi za inicializacijo SCI "handle" strukture SCI
// in modificira dolžino medpomnilnika printf() funkcije.
void SCI_init(void)
{

	// 0. Poskrbite, da je ustrezna nizko-nivojska strojna oprema že inicializirana

			// Za inicializacijo USART vmesnika, ki ga nameravamo uporabiti za implementacijo
			// SCI komunikacije, je poskrbljeno s pomočjo avtomatsko generirane CubeMX programske kode
			// znotraj funkcije MX_USARTx_UART_Init() v "main.c"!



	// 1. Določite, katera USART periferna enota bo uporabljena za implementacijo SCI vmesnika.

		// USART vmesnik specificiramo s pred-definiranim makrojem iz LL knjižnice, podobno kot
		// smo to storili za specifikacijo GPIO porta v prejšnjih vajah.

			// DOPOLNI


	// 2. modifikacija printf() medpomnilnika

		// Dolžino medpomnilnika, ki se uporablja za pošiljanje sporočil na
		// standardni izhod "stdout" s pomočjo printf() funkcije,
		// bomo nastavili na 0. Na ta način dosežemo najboljšo odzivnost
		// printf() funkcije, saj se tako ne čaka, da se medpomnilnik napolne,
		// preden se pošlje sporočilo. Sporočila bodo tako poslana takoj, ko se
		// prejme vsaj en znak.
		setvbuf(stdout, NULL, _IONBF, 0);

		// Opomba: uporabimo funkcijo setvbuf() iz modula "stdio.h" iz t.i. "newlib" knjižnice,
		//
		//		int setvbuf(FILE *fp, char *buf, int mode, size_t size);
		//
		// s katero specificiramo dolžino medpomnilnika za standardni izhod "stdout" (prvi argument funkcije).
		// Za 3. vhodni parameter uporabimo že pred-definirani makro _IONBF (I/O No Buffer), ki bo povzročil,
		// da se za standardni izhod "stdout" ne uporablja medpomnilnika, temveč
		// se znake takoj pošlje na standardni izhod.

}







// ------ Funkcije za pošiljanje enega samega bajta podatkov -------



// Funkcija SCI_send_char() pošlje en sam ZNAK preko SCI vmesnika (uporabno, kadar delamo z besedilnimi sporočili).
// Ker SCI vmesnik implementiramo z USART vmesnikom, je potrebno pravzaprav znak poslati z oddajnikom USART enote.
// Pri tem si pomagamo z LL funkcijo.
void SCI_send_char(char c)
{
	// S čakanjem v zanki zagotovimo, da lahko USART oddajnik sprejme nov znak v oddajni register.
	// Za ugotavljanje, ali je že mogoče pisati v oddajni register USART vmesnika, uporabimo ustrezno
	// nizko-nivojsko LL funkcijo za delo z USART-om.
	while( DOPOLNI );

	// In nato z uporabo USART vmesnika pošljemo en znak "c". Za pošiljane podatka preko USART vmesnika
	// prav tako uporabimo ustrezno nizko-nivojsko LL funkcijo.

		//	DOPOLNI

}



// Funkcija SCI_send_byte() pošlje en sam BAJT preko SCI vmesnika (uporabno, kadar pošiljamo binarne podatke).
// Ker SCI vmesnik implementiramo z USART vmesnikom, je potrebno pravzaprav bajt podatkov poslati z oddajnikom USART enote.
// Pri tem si pomagamo z LL funkcijo.
void SCI_send_byte(uint8_t data)
{
	// S čakanjem v zanki zagotovimo, da lahko USART oddajnik sprejme nov bajt v oddajni register.
	// Za ugotavljanje, ali je že mogoče pisati v oddajni register USART vmesnika, uporabimo ustrezno
	// nizko-nivojsko LL funkcijo za delo z USART-om.

		//	DOPOLNI

	// In nato z uporabo USART vmesnika pošljemo en bajt podatkov "data". Za pošiljane podatka preko USART vmesnika
	// prav tako uporabimo ustrezno nizko-nivojsko LL funkcijo.

		//	DOPOLNI
}







// ------ Funkcije za pošiljanje niza znakov ali zaporedja bajtov -------

// Te funkcije lahko enostavno implementiramo s pomočjo funkcij za pošiljanje
// enega samega znaka oziroma bajta podaktkov, ki smo jih definirali zgoraj.


// Funkcija SCI_send_string() pošlje znakovni niz (tj. string) preko SCI vmesnika.
void SCI_send_string(char *str)
{
	// Pomožna spremenljivka - indeks znaka, ki ga pošiljamo.
	uint32_t i = DOPOLNI;

	// Pošlji celoten niz znakov tako, da pošiljaš znak za znakom
	// vse dokler ne naletiš na vrednost 0 (null terminated string).
	// Premislite: "null terminating" znaka ni potrebno pošiljati preko SCI vmesnika.
	while( DOPOLNI )
	{
		// DOPOLNI
	}


}




// Funkcija SCI_send_bytes() pošlje zaporedje bajtov preko SCI vmesnika.
// Lokacija podatkov zapošiljanje je podana z vhodnim argumentom "*data",
// dolžina podatkov za pošiljanje pa je podano z vhodnim argumentom "size".
void SCI_send_bytes(uint8_t *data, uint32_t size)
{
	for( DOPOLNI )
	{
		// DOPOLNI
	}
}










// ------ Funkcije za sprejemanje enega samega bajta podatkov -------


// Najprej si pripravimo pomožno funkcijo, s katero bomo lahko preverjali, ali je v SCI vmesniku
// na voljo nov prejeti podatek.


// Funkcija SCI_is_data_waiting() preveri, če je v SCI vmesniku na voljo nov prejeti podatek.
// Ker SCI vmesnik implementiramo z USART vmesnikom, je potrebno pravzaprav preveriti, ali je v sprejemniku USART-a
// na voljo nov podatek.
uint8_t SCI_is_data_waiting(void)
{
	// V premislek: LL funkcija, ki jo boste uporabili za preverjanje prejetega podatka vrača vrednost
	// tipa "uint32_t", sistemska funkcija SCI_is_data_waiting() pa vrača vrednost tipa uint8_t.
	// Torej boste imeli opravka s pretvorbo tipov.

	return DOPOLNI;

}




// Funkcija SCI_read_char() POSKUSI prebrati en ZNAK iz SCI vmesnika in
// ga shraniti na lokacijo, ki jo določa vhodni argument funkcije *c.
// Ker SCI vmesnik implementiramo z USART vmesnikom, je potrebno pravzaprav podatek prebrati iz
// sprejemnika USART vmesnika. Poskus branja podatka iz SCI vmesnika je
// lahko uspešen (return code = SCI_NO_ERROR) ali pa neuspešen (return code = SCI_ERROR).
SCI_rtrn_codes_t SCI_read_char(char *c)
{
	// Najprej preverimo, če sploh je v SCI vmesniku na voljo nov prejeti podatek.
	// Uporabimo zgoraj definirano SCI funkcijo.
	if ( DOPOLNI )
	{

		// In če je na voljo nov prejeti podatek, ta podatek preberemo
		// in ga shranimo na specificirano mesto.
		// Preberemo ga seveda iz USART vmesnika s pomočjo LL funkcije.


			// DOPOLNI

		// In ker je bilo branje novega prejetega podatka uspešno, vrnemo
		// kodo SCI_NO_ERROR.
		return DOPOLNI;

	}
	else
	{
		// Če pa ni na voljo novega prejetega podatka, pa vrnemo kodo SCI_ERROR
		// in ne spreminjamo vrednosti spremenljivke *c.
		return DOPOLNI;
	}

}





// Funkcija SCI_read_byte() POSKUSI prebrati en BAJT iz SCI vmesnika in
// ga shraniti na lokacijo, ki jo določa vhodni argument funkcije *data.
// Ker SCI vmesnik implementiramo z USART vmesnikom, je potrebno pravzaprav podatek prebrati iz
// sprejemnika USART vmesnika. Poskus branja podatka iz SCI vmesnika je
// lahko uspešen (return code = SCI_NO_ERROR) ali pa neuspešen (return code = SCI_ERROR).
SCI_rtrn_codes_t SCI_read_byte(uint8_t *data)
{
	// Najprej preverimo, če sploh je v SCI vmesniku na voljo nov prejeti podatek.
	// Uporabimo zgoraj definirano SCI funkcijo.
	if ( DOPOLNI )
	{

		// In če je na voljo nov prejeti podatek, ta podatek preberemo
		// in ga shranimo na specificirano mesto.
		// Preberemo ga seveda iz USART vmesnika s pomočjo LL funkcije.

			// DOPOLNI

		// In ker je bilo branje novega prejetega podatka uspešno, vrnemo
		// kodo SCI_NO_ERROR.
		return DOPOLNI;

	}
	else
	{
		// Če pa ni na voljo novega prejetega podatka, pa vrnemo kodo SCI_ERROR
		// in ne spreminjamo vrednosti spremenljivke *data.
		return DOPOLNI;
	}
}








// -------------- Private function implementations -------------



// ----------- printf() customization ----------


// Na tem mestu pa REDEFINIRAMO "newlib" funkcijo _write(). Funkcija _write()
// se namreč uporablja za pošiljanje sporočil s printf() funkcijo. S tem ko
// redefiniramo _write() funkcijo pravzaprav priredimo uporabo printf() funkcije
// tako, da pošilja sporočila na točno tak način, kakor to sami želimo.
// In mi želimo uporabljati funkcijo printf() tako, da bomo s pomočjo nje
// pošiljali formatirana sporočila preko SCI vmesnika.
int _write(int file, char *ptr, int len)
{
	// Vhodna argumenta _write funkcije "*ptr" in "len" specificirata,
	// kje se nahajajo podatki, ki jih printf() funkcija želi poslati
	// ter kako dolgi so ti podatki (v smislu števila bajtov).

	// Sedaj pa uporabimo našo SCI sistemsko funkcijo SCI_send_bytes()
	// da z njo pošljemo te podatke, na katere kaže "ptr".
	// Ker naša funkcija SCI_send_bytes() uporablja drugačen tip
	// vhodnih argumentov, je potrebno poskrbeti za eksplicitno
	// pretvorbo med tipi (angl. type-casting).
	SCI_DOPOLNI( (uint8_t*) DOPOLNI, (uint32_t) DOPOLNI );



	// Funkcija _write() mora vrniti število uspešno poslanih
	// znakov. Tu poenostavimo in privzamemo, da je bilo uspešno
	// poslanih vseh "len" znakov.
	return DOPOLNI;
}


// --------------------------------------------------------------











// ------- Testne funkcije ---------


// Funkcija SCI_demo_Hello_world() naj preko SCI vmesnika pošlje
// klasično sporočilo "Hello world!".
void SCI_demo_Hello_world(void)
{
	// DOPOLNI
}



// Funkcija SCI_demo_Hello_world() naj preko SCI vmesnika pošlje
// sporočilo "Hello world!" s pomočjo prirejene funkcije printf().
// Sporočila naj bodo izpisana vsaka v svojo vrstico in naj bodo
// sledeče oblike:
//
//		1 : Hello printf() world!
//		2 : Hello printf() world!
//		3 : Hello printf() world!
//
// in tako dalje izpišite 10 vrstic.
// Sporočila naj se pošiljajo na vsako sekundo.
void SCI_demo_Hello_world_printf(void)
{

	// DOPOLNI

}




// Funkcija SCI_demo_echo_with_polling() naj demonstrira t.i. "echo funkcionalnost"
// s pristopom poizvedovanja (angl. polling).
//
// To pomeni da funkcija vsake toliko časa, ko ima na vojo "procesorski čas",
// preveri, če je bil preko SCI vmesnika sprejet nov znak in če je bil,
// naj ta znak takoj pošlje preko SCI vmesnika nazaj. Tako ste pravzaprav
// naredili nekakšen "odmev znakov", ki prihajajo preko SCI vmesnika.
// Demonstracija bo ključnega pomena, saj bomo z njo lahko pokazali
// pomembno težavo, ki jo prinese pristop poizvedovanja (angl. polling).
void SCI_demo_echo_with_polling(void)
{

	// pomožna spremenljivka, kamor bomo shranili prejeti znak
	char c;


	// spremenljivke, s pomočjo katerih bomo simulirali "zaposlenost procesorja" ("CPU busy")
	float a_0 = 0.5;
	float a_n;
	float sum = 0;

	#define N_MAX		50


	// V neskončni zanki
	while(1)
	{

		// s tehniko poizvedovanja ("polling") prevrejamo, ali je preko SCI vmesnika prispel
		// nov znak
		if ( SCI_read_char( DOPOLNI ) == SCI_NO_ERROR )
		{
			// in če je prispel, ga takoj pošljemo preko SCI vmesnika nazaj (tj. "echo").

				// DOPOLNI
		}



		// Potem pa simuliramo "zaposlenost procesorja" ("CPU busy") z drugimi opravili.
		// V našem primeru bomo to simulirali tako, da bomo računali privh N_MAX členov
		// geometrijske vsote.
		//
		// Na začetku, ko preverjate, kako dobro deluje "echo funkcionalnost",
		// pustite N_MAX nastavljen na 50. Kasneje pa lahko preverite, kaj se
		// dogaja, ko vrednost N_MAX večate oziroma manjšate. Lahko tudi poskusite zakomentirati
		// spodnjo kodo.

		a_n = a_0;
		for(uint32_t n=0; n<N_MAX; n++)
		{
			 sum = sum + a_n;
			 a_n = a_n * a_0;
		}


	}

}











