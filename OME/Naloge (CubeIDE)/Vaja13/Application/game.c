/*
 * game.c
 *
 *  Created on: 18.5.2022
 *      Author: Rok Plesko
 */


/* **************** MODULE DESCRIPTION *************************

Ta modul implementira algoritem igrice s pomoÄjo avtomatov stanj.
Algoritem igre za svoje delovanje potrebuje podporo sistemskih
modulov za delo z vhodno-izhodnimi napravami sistema ter podporo
aplikacijskih modulov za delo z objekti aplikacije ter podporo
za izris objekotv na zaslon.

************************************************************* */



// ----------- Include other modules (for private) -------------



// ------ Standard C libraries -----
#include <stdio.h>
#include <stdlib.h>		// support for random number generation


// POGLEJTE: igra (tj. aplikacija) je odvisna le od modulov s
// sistemskega nivoja, ne pa tudi od modulov s strojnega nivoja!


// --- Moduli sistemskega nivoja ---


#include "LED.h"				// podpora za delo z LEDicami
#include "kbd.h"				// podpora za delo s tipkovnico
#include "SCI.h"				// podpora za delo s serijskim vmesnikom
#include "joystick.h"			// podpora za delo z joystickom
#include "lcd.h"				// podpora za delo z LCDjem
#include "timing_utils.h"		// podpora za delo z orodji za merjenje Äasa
#include "ugui.h"


// --- Moduli applikacijskega nivoja ----

#include "game.h"			// lastne definicije game.c modula

#include "objects.h"			// v igro vkljuÄimo modul za delo z objekti igre
#include "graphics.h"			// v igro vkljuÄimo modul za prikaz objektov na zaslon



// ---------------------- Private definitions ------------------



// ----- Definicija stanj avtomatov  --------


// stanja avtomata Game()
typedef enum GAME_states {GAME_INTRO_STATE, GAME_PLAY_STATE, GAME_OVER_STATE} GAME_states_t;

// stanja avtomata Intro()
typedef enum INTRO_states {INTRO_INIT, INTRO_WAIT_BEFORE_KBD_ACTIVE, INTRO_PRESS_ANY_KEY, INTRO_WAIT_FOR_ANY_KEY, INTRO_LEDS_OFF} INTRO_states_t;

// stanja avtomata GamePlay()
//typedef enum GAMEPLAY_states {s } GAMEPLAY_states_t;

// stanja avtomata GameOver()
typedef enum GAMEOVER_states {GAMEOVER_SCREEN, GAMEOVER_WAIT_BEFORE_LEDS_OFF, GAMEOVER_LEDS_OFF, GAMEOVER_WAIT_FOR_ANY_KEY} GAMEOVER_states_t;




// ------------- Public function implementations --------------


// Funkcija, ki implementira nad-avtomat Game().
void Game()
{
	// Stanje avtomata je potrebno pomniti tudi, ko se avtomat ne izvaja.
	// To pomeni, da je potrebno stanje avtomata hraniti v spremenljivki,
	// ki ima neskonÄno Ĺživljensko dobo. Lokalni spremenljivki funkcije
	// lahko napravimo Ĺživljensko dobo neskonÄno, Äe jo definiramo kot
	// statiÄno spremenljivko (tj. uporabimo t.i. kljuÄno besedo "static",
	// Osvojimo C, Fajfar et al., stran 83).
	// Hkrati z definicijo spremenljivke poskrbimo ĹĄe za inicializacijo zaÄetnega stanja avtomata.
	static GAME_states_t state = GAME_INTRO_STATE;


	// PomoĹžna spremenljivka, kamor bomo shranjevali vrnjeno izhodno
	// vrednost pod-avtomatov (tj. "exit value").
	// Hkrati z definicijo spremenljivke poskrbimo ĹĄe za inicializacijo zaÄetne vrednosti.
	uint8_t exit_value = 0;


	// Avtomat stanj implementiramo s pomoÄjo "switch-case" stavka, s katerim
	// zelo enostavno doseĹžemo izvajanja le tistega dela kode, ki pripada
	// toÄno doloÄenemu stanju avtomata.
	switch (state)
	{

		case GAME_INTRO_STATE:

			// Znotraj tega stanja izvajamo pod-avtomat Intro().
			exit_value = Intro();

			// Äe pod-avtomat vrne vrednost razliÄno od niÄ,
			// avtomat Game() preide v naslednje stanje.
			if (exit_value != 0)
				state = GAME_PLAY_STATE;

		break;



		case GAME_PLAY_STATE:

			// Znotraj tega stanja izvajamo pod-avtomat GamePlay().
			exit_value = GamePlay();

			// Äe pod-avtomat vrne vrednost razliÄno od niÄ,
			// avtomat Game() preide v naslednje stanje.
			if (exit_value != 0)
				state = GAME_OVER_STATE;

		break;





		case GAME_OVER_STATE:

			// Znotraj tega stanja izvajamo pod-avtomat GameOver().
			exit_value = GameOver();

			// Äe pod-avtomat vrne vrednost razliÄno od niÄ,
			// avtomat Game() preide v naslednje stanje.
			if (exit_value != 0)
				state = GAME_INTRO_STATE;

		break;




		// Avtomatu dodamo "varovalko" za primer, da avtomat zaide v nedefinirano stanje.
		// To napako javimo preko SCI vmesnika. Vidite, da SCI vmesnik uporabljamo
		// za realno-Äasni nadzor nad napakami aplikacije preko serijskega terminala.
		default:

			// Javimo vir napake in vrednost nedefiniranega stanja, v katerem se je naĹĄel avtomat.
			printf("Game(): Error - undefined state (%d)", state);

			// Ustavimo izvajanje z namenom, da razvojnik lahko opazi neobiÄajno obnaĹĄanje aplikacije.
			HAL_Delay(5000);

			// In na koncu avomat restiramo tako, da ga postavimo v zaÄetno stanje.
			state = GAME_INTRO_STATE;
			exit_value = 0;

		break;
	}
}




// Funkcija, ki implementira pod-avtomat Intro().
uint8_t Intro()
{

	// Definicija makro parametrov za pod-avtomat Intro().
	#define INTRO_DELAY_BEFORE_KBD_ACTIVE	0		// Äasovni premor pred aktivacijo tipkovnice


	// Stanje avtomata je potrebno pomniti tudi, ko se avtomat ne izvaja.
	// To pomeni, daje potrebno stanje avtomata hraniti v spremenljivki,
	// ki ima neskonÄno Ĺživljensko dobo. Lokalni spremenljivki funkcije
	// lahko napravimo neskonÄno Ĺživljensko dobo, Äe jo definiramo kot
	// statiÄno spremenljivko ("static").
	// Hkrati z definicijo spremenljivke poskrbimo ĹĄe za inicializacijo zaÄetnega stanja avtomata.
	static INTRO_states_t state = INTRO_INIT;


	// PomoĹžna spremenljivka, kamor bomo shranjevali vrnjeno izhodno
	// vrednost pod-avtomatov (tj. "exit value").
	// Hkrati z definicijo spremenljivke poskrbimo ĹĄe za inicializacijo zaÄetne vrednosti.
	uint8_t exit_value = 0;

	// PomoĹžna spremenljivka, kjer bomo hranili informacijo o pritisnjeni tipki.
	buttons_enum_t	key = BTN_NONE;


	// Ker mora pod-avtomat implementirati Äasovne zakasnitve oziroma premore,
	// bomo potrebovali funkcionalnost ure ĹĄtoparice iz modula timing_utils.c.
	// Premislite: tudi ura ĹĄtoparica mora imeti svoje spremenljivke z neskonÄno
	// Ĺživljensko dobo.
	static stopwatch_handle_t    stopwatch;




	// Avtomat stanj implementiramo s pomoÄjo "switch-case" stavka, s katerim
	// zelo enostavno doseĹžemo izvajanja le tistega dela kode, ki pripada
	// toÄno doloÄenemu stanju avtomata.
	switch (state)
	{

		// ZaÄetno stanje pod-avtomata.
		// Inicializacija vseh podaktovnih struktur igre, risanje "splash screen" zaslona
	 	// ter priĹžig vseh LEDic.
		case INTRO_INIT:

			// Opravila stanja.
			OBJ_init();		// Namig: inicializacijo podatkovnih struktur (tj. objektov)
						// lahko izvedete s klicem ene same funkcije.
			LEDs_write(255);
			//OBJ_init_splash_screen();



			// Ob koncu tega stanja priÄnemo z merjenjem Äasa premora, ki sledi
			// (tj. sproĹžimo uro ĹĄtoparico tako, da postavimo Äasovni zaznamek - "time mark").
			TIMUT_stopwatch_set_time_mark(&stopwatch);

			// DoloÄimo naslednje stanje ter "exit" vrednost.
			state = INTRO_WAIT_BEFORE_KBD_ACTIVE;
			exit_value = 0;

		break;




		// Premor pred aktivacijo tipkovnice, ÄiĹĄÄenje medpomnilnika tipkovnice.
		case INTRO_WAIT_BEFORE_KBD_ACTIVE:

			// V tem stanju preverjamo, ali se je premor Ĺže iztekel.
			if ( TIMUT_stopwatch_has_X_ms_passed(&stopwatch, INTRO_DELAY_BEFORE_KBD_ACTIVE) )
			{
				// Äe se je premor Ĺže iztekel,

				// poÄistimo medpomnilnik tipkovnice.
				KBD_flush();

				// ter doloÄimo naslednje stanje in "exit" vrednost.
				state = INTRO_PRESS_ANY_KEY;
				exit_value = 0;

			}

		break;



		// Izpis "press any key".
		case INTRO_PRESS_ANY_KEY:

			// Opravila stanja.
					// Namig: Napis "Press any key" je shranjen v obliki "sprite-a". PreuÄite,
												// v katerem od objektov se skriva ta "sprite".
			GFX_draw_gfx_object(&splash_screen);
			GFX_draw_one_gfx_object_on_background(&press_any_key_sprite, &background);
			// DoloÄimo naslednje stanje ter "exit" vrednost.
			state = INTRO_WAIT_FOR_ANY_KEY;
			exit_value = 0;

		break;



		// Äakanje na pritisk tipke.
		case INTRO_WAIT_FOR_ANY_KEY:

			// V tem stanju preverjamo, Äe je bila pritisnjena katerakoli tipka.

			// Preberemo informacijo o pritisnjenih tipkah iz medpomnilnika tipkovnice.
			// (Skeniranje tipkovnice se izvaja avtomatsko v sklopu periodic_services.c modula.)
			key = KBD_get_pressed_key();

			// In Äe je bila pritisnjena katerakoli tipka
			if ( key != BTN_NONE )
			{

				// doloÄimo naslednje stanje in "exit" vrednost.
				state = INTRO_LEDS_OFF;
				exit_value = 0;

			}

		break;




		// Ugasnitev vseh LEDic
		case INTRO_LEDS_OFF:

			// Opravila stanja.
			LEDs_write(0);

			// DoloÄimo naslednje stanje ter "exit" vrednost.

			// V tej toÄki se je izvajanje pod-avtomata zakljuÄilo.
			// Stanje avtomata nastavimo na zaÄetno stanje in nastavimo "exit" vrednost 1.
			state = INTRO_INIT;
			exit_value = 1;

		break;






		// Avtomatu dodamo "varovalko" za primer, da avtomat zaide v nedefinirano stanje.
		// To napako javimo preko SCI vmesnika. Vidite, da SCI vmesnik uporabljamo
		// za realno-Äasni nadzor nad napakami aplikacije preko serijskega terminala.
		default:

			// Javimo vir napake in vrednost nedefiniranega stanja, v katerem se je naĹĄel avtomat.
			printf("Intro(): Error - unknown state (%d)", state);

			// Ustavimo izvajanje z namenom, da razvojnik lahko opazi neobiÄajno obnaĹĄanje aplikacije.
			HAL_Delay(5000);

			// In na koncu avomat restiramo tako, da ga postavimo v zaÄetno stanje.
			state = INTRO_INIT;
			exit_value = 0;

		break;


	}


	// Vrnemo zgoraj nastavljeno "exit_value" vrednost nad-avtomatu.
	// Tako bo nad-avtomat vedel, ali mora ĹĄe zaganjati ta pod-avtomat ali
	// pa mora preiti v naslednje stanje.
	return exit_value;

}









// Funkcija, ki implementira pod-avtomat GamePlay().
uint8_t GamePlay()
{
	// Tu bomo kasneje implementirali ĹĄe avtomat za izvedbo
	// igranja igre.

	// Zankrat pa tu le izriĹĄimo ozadje in poÄakajmo na pritisk tipke.

	GFX_draw_gfx_object( &background );


	while( KBD_get_pressed_key() == BTN_NONE );

	LEDs_write(255);
	HAL_Delay(500);
	LEDs_write(0);

	return 1;

}



// Funkcija, ki implementira pod-avtomat GameOver().
uint8_t GameOver()
{
	// Po vzoru pod-avtomata Intro() implementirajte ĹĄe pod-avtomat GameOver().

	static GAMEOVER_states_t state = GAMEOVER_SCREEN;

	//typedef enum GAMEOVER_states {GAMEOVER_SCREEN, GAMEOVER_WAIT_BEFORE_LEDS_OFF, GAMEOVER_LEDS_OFF, GAMEOVER_WAIT_FOR_ANY_KEY} GAMEOVER_states_t;
	// PomoĹžna spremenljivka, kamor bomo shranjevali vrnjeno izhodno
	// vrednost pod-avtomatov (tj. "exit value").
	// Hkrati z definicijo spremenljivke poskrbimo ĹĄe za inicializacijo zaÄetne vrednosti.
	uint8_t exit_value = 0;

	// PomoĹžna spremenljivka, kjer bomo hranili informacijo o pritisnjeni tipki.
	//buttons_enum_t	key;


	// Ker mora pod-avtomat implementirati Äasovne zakasnitve oziroma premore,
	// bomo potrebovali funkcionalnost ure ĹĄtoparice iz modula timing_utils.c.
	// Premislite: tudi ura ĹĄtoparica mora imeti svoje spremenljivke z neskonÄno
	// Ĺživljensko dobo.
	stopwatch_handle_t    stopwatch;


	switch (state)
		{

			case GAMEOVER_SCREEN:
				//opravila stanja
				GFX_draw_one_gfx_object_on_background(&game_over_sprite, &background);

				LEDs_on(0xFF);

				// Določimo naslednje stanje ter "exit" vrednost.

				// V tej točki se je izvajanje pod-avtomata zaključilo.
				// Stanje avtomata nastavimo na začetno stanje in nastavimo "exit" vrednost 1.
				state = GAMEOVER_WAIT_BEFORE_LEDS_OFF;
				exit_value = 0;

			break;

			case GAMEOVER_WAIT_BEFORE_LEDS_OFF:
				// Opravila stanja.
				KBD_flush();

				LEDs_on(0xFF);
				TIMUT_stopwatch_set_time_mark(&stopwatch);

				if(TIMUT_stopwatch_has_X_ms_passed(&stopwatch, 3000))
				{
				  state = GAMEOVER_LEDS_OFF;
				  exit_value = 0;
				}

			break;


			case GAMEOVER_LEDS_OFF:
				LEDs_off(0xFF);
				  state = GAMEOVER_WAIT_FOR_ANY_KEY;
				  exit_value = 0;
				  TIMUT_stopwatch_set_time_mark(&stopwatch);
				  KBD_flush();
			break;


			case GAMEOVER_WAIT_FOR_ANY_KEY:
				if(TIMUT_stopwatch_has_X_ms_passed(&stopwatch, 10000) || KBD_get_pressed_key() == BTN_NONE)
				{
					//cas 10 s je pretekel
					exit_value = 1;
					state = GAMEOVER_SCREEN;
				}
				else
				{
					 state = GAMEOVER_WAIT_FOR_ANY_KEY;
					 exit_value = 0;
				}


			break;


			// Avtomatu dodamo "varovalko" za primer, da avtomat zaide v nedefinirano stanje.
			// To napako javimo preko SCI vmesnika. Vidite, da SCI vmesnik uporabljamo
			// za realno-Äasni nadzor nad napakami aplikacije preko serijskega terminala.
			default:

				// Javimo vir napake in vrednost nedefiniranega stanja, v katerem se je naĹĄel avtomat.
				printf("Intro(): Error - unknown state (%d)", state);

				// Ustavimo izvajanje z namenom, da razvojnik lahko opazi neobiÄajno obnaĹĄanje aplikacije.
				HAL_Delay(5000);

				// In na koncu avomat restiramo tako, da ga postavimo v zaÄetno stanje.
				state = GAMEOVER_SCREEN;
				exit_value = 0;

			break;


		}


	return exit_value;

}


// ------- Test functions ---------


// -------------- Private function implementations -------------

