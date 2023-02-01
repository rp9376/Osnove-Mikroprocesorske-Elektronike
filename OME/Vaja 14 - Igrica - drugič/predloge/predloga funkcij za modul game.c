// Funkcija, ki implementira pod-avtomat GamePlay().
uint8_t GamePlay()
{



	// -------------- Definicije znotraj funkcije GamePlay() ------------------

	// Definicija makro parametrov za pod-avtomat GamePlay().
		// DOPOLNI


	// Spremenljivka, ki hrani stanje avtomata.
		// DOPOLNI


	// Pomožna spremenljivka, kamor bomo shranjevali vrnjeno izhodno
	// vrednost pod-avtomatov (tj. "return exit value").
		// DOPOLNI


	// Pomožna spremenljivka, kjer bomo hranili informacijo o pritisnjeni tipki.
		// DOPOLNI


	// Spremenljivka za implementacijo ure štoparice.
	static stopwatch_handle_t   stopwatch;






	// ----------------- Ugnezdena funkcija GamePlay_UpdateChanges() ---------------------


	// Ugnezdena funkcija (angl. nested function) je funkcija, ki je definirana znotraj
	// druge funkcije. Taka ugnezdena funkcija lahko dostopa do spremenljivk te druge funkcije,
	// ki so bile definirane pred ugnezdeno funkcijo. V našem primeru bomo to izkoristili
	// tako, da bomo znotraj ugnezdene funkcije dostopali do spremenljivke "stopwatch", ki vsebuje
	// informacijo o času, ki je še na voljo za igranje.


	// Ugnezdena funkcija GamePlay_UpdateChanges() poskrbi, da se objekti, ki jih algoritem igre spreminja,
	// posodobijo: tako njihovi parametri kot njihov prikaz na zaslonu.
	void GamePlay_UpdateChanges(void)
	{

		// Spremenljivka za implementacijo ure štoparice.
		static stopwatch_handle_t   update_stopwatch;


		// PAZITE: parametre objektov in njihov izris osvežujemo periodično s
		// točno določeno periodo osveževanja. Tako dosežemo, da igrica vedno teče
		// z enako hitrostjo, neodvisno od hitrosti procesorja (tj. od hitrosti sistemske ure).
		if ( TIMUT_stopwatch_has_another_X_ms_passed( &update_stopwatch, settings.game_play_update_period) )
		{

			// -------- Posodobitve parametrov objektov -----------


			// Posodobimo parametre objektov s pomočjo GFX modula.

				// Posodobimo lokacijo tarče.
					// DOPOLNI



			// Posodobimo parametre objektov s pomočjo OBJ modula.

				// Posodobimo lokacijo namerka.
					// DOPOLNI

				// Posodobimo razdaljo med namerkom in tarčo.
					// DOPOLNI

				// Posodobimo vrednost "progress bar" indiktorja, ki kaže,
				// koliko časa je še na voljo za igranje.
					// DOPOLNI

				// Posodobimo vrednost doseženih točk.
					// DOPOLNI




			// ------ Izris posodobljenih objektov na zaslon -----------


			// Izrišemo posodobljene objekte na zaslon s pomočjo GFX modula.

				// Izris namerka in tarče na ozadje.
					// DOPOLNI


				// Izris vrednosti doseženih točk.
					// DOPOLNI

				// Izris "progress bar" indikatorja preostalega časa za igranje.
					// DOPOLNI



			// -------- Posodobitev ostalih izhodnih naprav sistema -------

				// Posodobimo LED indikator točnosti namerka.
					// DOPOLNI

		}

	}






	// --------------- Implementacija algoritma "igranja igre" z avtomatom stanj ------------------------

	// Avtomat stanj implementiramo s pomočjo "switch-case" stavka.
	switch (state)
	{

		// Začetno stanje pod-avtomata.
		//
		// Inicializacija, ki je potrebna pred začetkom igranja igre:
		//
		// 		- inicializacija generatorja naključnih števil
		//		- izrišemo ozadje
		//		- izrišemo napise "TIME" in "SCORE"
		//		- izrišemo "progress bar" za prikaz časa, ki je še na voljo za igranje
		//		- izpišemo trenutno število točk
		case GAMEPLAY_INIT:

			// Opravila stanja.

				// DOPOLNI


			// Določimo naslednje stanje ter "exit" vrednost.

				// DOPOLNI


		break;










		// Varovalka za nedefinirana stanja.
		default:

			// Javimo vir napake in vrednost nedefiniranega stanja, v katerem se je našel avtomat.
			printf("GamePlay(): Error - unknown state (%d)", state);

			// Ustavimo izvajanje z namenom, da razvojnik lahko opazi neobičajno obnašanje aplikacije.
			HAL_Delay(5000);

			// In na koncu avomat restiramo tako, da ga postavimo v začetno stanje.
			state = GAMEPLAY_INIT;
			exit_value = 0;

		break;

	}


	// Vrnemo "exit value" pod-avtomata.
	return exit_value;


}






// Funkcija GamePlay_Update_Aiming_LED_Indicator() posodobi stanje LED indikatorja
// točnosti namerka: bolj kot je namerek na tarči, več LEDic bo prižganih.
void GamePlay_Update_Aiming_LED_Indicator(void)
{

	// Definicija makro parametrov.
	#define NOMINAL_DISTANCE_BETWEEN_TARGET_AND_CROSSHAIR	150

	// Pomožne spremenljivke.
	int16_t percent_distance;
	int16_t percent_vicinity;

	uint8_t number_of_LEDs_on;

	uint8_t bitmask_right = 0;
	uint8_t bitmask_left = 0;
	uint8_t bitmask;


	// Izračunamo relativno oddaljenost tarče
	percent_distance = (crosshair.distance_to_target_center * 100) / NOMINAL_DISTANCE_BETWEEN_TARGET_AND_CROSSHAIR;


	// Porežemo prevelike vrednosti.
	if (percent_distance > 100)
		percent_distance = 100;


	// in jo pretvorimo v "relativno bližino tarče".
	percent_vicinity = 100 - percent_distance;


	// Preračunamo, koliko LEDic je potrebno prižgati za dano "relativno bližino tarče".
	number_of_LEDs_on = ( (1 + NUM_OF_LEDS/2) * percent_vicinity ) / 100;

	// Porežemo prevelike vrednosti.
	if (number_of_LEDs_on  > (NUM_OF_LEDS/2) )
		number_of_LEDs_on = (NUM_OF_LEDS/2);


	// Tvorimo bitno masko za prižig štirih LEDic na desni strani.
	for(uint8_t i = 1; i <= number_of_LEDs_on ; i++ )
	{
		bitmask_right |= 1;
		bitmask_right = bitmask_right << 1;
	}
	bitmask_right = bitmask_right >> 1;


	// Tvorimo bitno masko za prižig štirih LEDic na levi strani.
	bitmask_left = bitmask_right << (8 - number_of_LEDs_on);

	// Bitni maski združimo v eno samo masko
	bitmask = bitmask_right | bitmask_left;


	// in jo uporabimo za prižig LEDic.
	LEDs_write(bitmask);

}