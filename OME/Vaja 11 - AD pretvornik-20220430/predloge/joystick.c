/*
 * joystick.c
 *
 *  Created on:
 *      Author:
 */



/* **************** MODULE DESCRIPTION *************************

Ta modul implementira funkcionalnost "joysticka" na sistemskem
nivoju. Modul je implementiran na podlagi pristopa s pomočjo DMA enote
(angl. DMA mode), kjer DMA enota poskrbi za prenos rezultatov
AD pretvornika v sistemske spremenljivke.

Modul omogoča:

	- kalibracijo osi "joysticka",

	- branje trenutne relativne pozicije "joystika" (izražene v
	 	 procentualnem deležu polnega odklona osi),

	- detekcijo pritiska tipke,

	- branje trenutnega stanja tipke,

	- demonstracijo delovanja "joysticka" (s pomočjo SCI in LED
		modulov)



POZOR: za uspešno uporabo modula je potrebno predhodno poskrbeti
za ustrezno inicializacijo perifernih enot, ki zagotovijo delovanje
AD pretvornika v navezi z DMA enoto.


************************************************************* */





// ----------- Include other modules (for private) -------------


#include "joystick.h"

// Vključimo še LED in SCI sistemska modula, ki bosta pomagala
// pri demonstraciji delovanja "joysticka".
#include "LED.h"
#include "SCI.h"




// ---------------------- Private definitions ------------------


// Na enak način kot smo to storili pri tipkovnici, definirajmo najprej tip
// "joystick_button_handle_t" strukture, ki hrani vse potrebne parametre
// za delo s tipko "joysticka".

typedef struct
{
	GPIO_TypeDef 						*port;
	uint32_t 							pin;
	joystick_button_sig_value_t			state_new;
	joystick_button_sig_value_t			state_old;

} joystick_button_handle_t;





// Sedaj pa definirajmo tip "handle" strukture joystick_handle_t, ki jo bomo uporabljali
// za delo z "joystickom".
typedef struct
{
	// Dodamo ji "handle" strukturo za delo s tipko "joysticka".
	DOPOLNI	button;


	// Dodamo sistemske spremenljivke za delo z osmi "joysticka".
	uint16_t 	DOPOLNI;			// meritev trenutne pozicije osi "joysticka"

	uint16_t 	DOPOLNI;			// informacija o najmanjšem odklonu osi "joysticka"
	uint16_t 	DOPOLNI;			// informacija o največjem odklonu osi "joysticka"
	uint16_t 	DOPOLNI;			// informacija o razponu odklona osi "joysticka" (angl. axis range)


	// Dodamo ji kazalca na "handle" strukturi za časovnik in AD pretvornik,
	// da lahko po potrebi s pomočjo HAL funkcij upravljamo periferne enote,
	// ki so ključne za delovanje "joystick" modula.
	TIM_HandleTypeDef 	*timer;
	ADC_HandleTypeDef 	*ADC;


} joystick_handle_t;





// Vse to zgoraj so bile le DEFINICIJE ZGRADBE podatkovne strukture. Sedaj pa lahko končno ustvarimo
// še strukturno spremenljivko "joystick", ki bo imela tako zgradbo in bo za nas hranila vse potrebne
// parametre za delo z "joystickom".

	// DOPOLNI






// -------- Joystick button buffer ----------

// "Joystick" ima tudi tipke. In pri delu s tipkami je smiselno uporabiti
// medpomnilnik, ki hrani informacijo o tem, katere tipke so bile pritisnjene,
// a se na njihov pritisk še nismo odzvali. Čeprav ima naš "joystick" le eno
// tipko, je uporaba medpomnilnika smiselna. Zakaj? Ker lahko to tipko pritisnemo
// večkrat zapored in se je potrebno na vsak pritisk odzvati posebej
// (primer: s tipko "joysticka" streljate in vsak pritisk pomeni en strel).

// Medpomnilnik uporabimo na popolnoma enak način, kot smo to storili v primeru
// tipkovnice.


// Najprej je potrebno vključiti knjižnico za delo s cikličnim medpomnilnikom.
#include "buf.h"

// Definirajmo dolžino cikličnega medpomnilnika za tipke "joysticka". Definirajmo
// jo kot makro parameter.
#define JOY_BTN_BUF_LEN 	DOPOLNI


// In sedaj še definirajmo podatkovne strukture, s katerimi bomo implementirali
// ciklični medpomnilnik. Potrebujemo tabelo, kamor bomo shranjevali informacijo
// o pritisnjenih tipkah "joysticka". In potrebujemo "handle" strukturo za upravljanje
// cikličnega medpomnilnika.
uint8_t 		joy_btn_buffer[DOPOLNI];			// the buffer data array
buf_handle_t 	joy_btn_buf_handle;					// the buffer handle structure









// ------------- Public function implementations --------------




// Funkcija JOY_init() poskrbi za inicializacijo "joystick" modula na sistemskem
// nivoju: inicializira parametre "joystick" handle strukture, inicializira
// medpomnilnik "joysticka" ter inicializira in zažene periferne enote za
// merjenje signalov "joysticka".
// Mimogrede: inicializacijska funkcija se razlikuje od prejšnjih inicializacijskih funkcij
// v tem, da za vhodna argumenta funkcije prejme kazalce na "handle" strukture, ki so
// potrebne za delo s HAL funkcijami.
void JOY_init(ADC_HandleTypeDef *ADC_handle, TIM_HandleTypeDef *timer_handle)
{

	// 0. Poskrbite, da je ustrezna nizko-nivojska strojna oprema že inicializirana

		// Za merjenje pozicije "joysticka" uporabljamo pristop z DMA enoto in proženje
		// AD pretvornika s pomočjo časovnika. Da bo "joystick" modul pravilno deloval,
		// je potrebno torej poskrbeti za inicializacijo GPIO digitalnega vhoda,
		// časovnika, AD pretvornika ter DMA enote, za kar pa je poskrbljeno s pomočjo
		// avtomatsko generirane CubeMX programske kode v "main.c".



	 // 1. Inicializacija "handle" strukture za tipke "joysticka" na strojnem nivoju

		// Definirajte, kako so posamezne tipke povezane na GPIO pine in porte.
		// To storite tako, da pravilno inicializirate "handle" strukturo tipke "joysticka".
		// Uporabite makroje "GPIOn" in "LL_GPIO_PIN_n" iz nizko-nivojske LL knjižnice.
		// Postopate popolnoma enako, kot smo to storili v primeru tipkovnice.

			// DOPOLNI



	// 2. Nastavitev začetnih vrednosti "joystick" sistemskih spremenljivk

		// Začetne vrednosti tipke "joysticka"
		joystick.button.state_old = DOPOLNI;
		joystick.button.state_new = DOPOLNI;


		// Smiselno nastavimo začetne ekstremne vrednosti pozicije "joysticka".
		joystick.position_raw_min[X] = DOPOLNI;

			// DOPOLNI


		joystick.position_raw_max[X] = DOPOLNI;

			// DOPOLNI


		// Shranimo si kazalce na "handle" strukturi za AD pretvornik in časovnik,
		// ki ju uporabljamo pri implementaciji "joystick" modula.
		// Ti dve infromaciji seveda shranimo v spremenljivki "joystick handle" strukture.
		joystick.ADC = DOPOLNI;
		joystick.timer = DOPOLNI;



	// 3. Inicializiramo medpomnilnik za tipke "joysticka"

		// Uporabimo funkcijo BUF_init(), ki določi, katera tabela se bo uporabljala kot
		// ciklični medpomnilnik ter kako dolg bo ta medpomnilnik.
		BUF_init( &joy_btn_buf_handle, joy_btn_buffer, DOPOLNI);




	// 4. Poskrbimo za zagon strojne opreme za merjenje signalov "joysticka"

		// Pri tem uporabljamo funkcije HAL knjižnice.


		// Najprej kalibriramo AD pretvornik, da bodo meritve pozicije "joysticka" bolj točne.
		// Kalibracijo izvedemo za "single-ended" vhodne signale.
		HAL_ADCEx_Calibration_Start( DOPOLNI, ADC_SINGLE_ENDED );


		// Nato omogočimo DMA enoto v navezi z AD pretvornikom (rečemo tudi, da zaženemo
		// AD pretovrnik v DMA načinu).
		// To storimo s klicem spodnje HAL funkcije, ki DMA enoti
		// "sporoči", s katerim AD pretvornikom bo delala, na katero mesto v pomnilniku
		// naj shranjuje rezultate AD pretvorbe ter koliko teh rezultatov bo morala prenesti
		// ob vsaki končani AD pretvorbi.
		HAL_ADC_Start_DMA( DOPOLNI, (uint32_t *) DOPOLNI, DOPOLNI );


		// Na koncu pa še zaženemo časovnik, ki bo prožil AD pretvorbe.
		// S tem smo pravzaprav sprožili "avtomatsko" merjenje pozicije "joysticka".
		HAL_TIM_Base_Start( DOPOLNI );


	// 5. Počakamo na prvo meritev pozicije "joysticka"

		// Časovnik proži AD pretvorbe vsakih 10 milisekund.
		// Torej je smiselno počakati milisekundo dlje.

			// DOPOLNI


}








// ------- Funkcionalnost povezana s tipkami "joysticka" ----------


// Funkcionalnost "joystickovih" tipk implementiramo na popolnoma enak način,
// kot smo to storili v primeru tipkovnice.


// Funkcija JOY_scan_button() prebere trenutno stanje tipke "joysticka"; ugotovi,
// ali je bila tipka pritisnjena ter shrani to informacijo v medpomnilnik
// "joysticka", da se bo kasneje lahko sistem odzval na pritisk te tipke.
void JOY_scan_button(void)
{
	// Ker ima naš "joystick" le eno samo tipko, se funkcija poenostavi.

	// Trenutno, novo stanje tipke postane sedaj staro stanje tipke
	joystick.button.state_old = joystick.button.state_new ;

	// in novo, trenutno stanje tipke se prebere iz ustreznega digitalnega GPIO vhoda.
	joystick.button.state_new = LL_GPIO_IsInputPinSet( joystick.button.port, joystick.button.pin );



	// Sedaj je potrebno preveriti, ali se je za to tipko zgodil pritisk. Pri tem si pomagajte s starim in
	// trenutnim stanjem tipke. Pomaga vam lahko tudi pomožni naštevni tip joystick_button_sig_value_t.
	if ( ( joystick.button.state_old == JOY_BTN_SIG_VALUE_RELEASED) && ( joystick.button.state_new == JOY_BTN_SIG_VALUE_PRESSED ) )
	{

		// In če zaznamo pritisk tipke, shranimo to informacijo v medpomnilnik "joystick" tipkovnice.
		// Ker ima "joystick" le eno samo tipko, shranimo vedno isto informacijo: JOY_BTN_FIRE.
		//Uporabimo funkcijo BUF_store_byte().
		BUF_store_byte( &joy_btn_buf_handle, JOY_BTN_FIRE);

	}

}



// Funkcija JOY_get_pressed_key() iz medpomnilnika "joysticka" vrne
// informacijo o tem, katera je naslednja pritisnjena tipka, na katero
// se še nismo odzvali (tj. je nismo obdelali, "sprocesirali").
joystick_buttons_enum_t JOY_get_pressed_key(void)
{
	// Ustvarimo pomožno spremenljivko, v kateri bomo pripravili
	// vrednost, ki jo bo funkcija JOY_get_pressed_key() vrnila.
	// Ustvarimo tudi pomožno spremenljivko, ki bo hranila informacijo
	// o uspešnosti branja iz medpomnilnika.
	joystick_buttons_enum_t 		pressed_button;
	buf_rtrn_codes_t				return_code;


	// Sedaj poskusimo prebrati nov element iz medpomnilnika in ga shraniti v spremenljivko "pressed_button"
	// Hkrati si v spremenljivko "return_code" zabeležimo vrnjeno kodo "buffer" funkcije.
	return_code = BUF_get_byte(&joy_btn_buf_handle, &pressed_button);


	// Če je bilo branje elementa iz medpomnilnika v spremenljivko "pressed_button"
	// uspešno (tj. vrnjen BUFFER_OK),
	if ( return_code == BUFFER_OK )
	{
		//potem je vrednost, ki jo mora funkcija JOY_get_pressed_key() vrniti
		// kar enaka vrednosti pomožne spremenljivke "pressed_button".
		return pressed_button;
	}
	else
	{
		// Če pa je bilo branje elementa iz medpomnilnika v spremenljivko "pressed_button"
		// neuspešno (tj. ni bil vrnjen BUFFER_OK), potem pa sklepamo, da je medpomnilnik
		// prazen in da pravzaprav ni bila pritisnjena nobena nova tipka.
		// Funkcija JOY_get_pressed_key() mora vrniti kodo "JOY_BTN_NONE".
		return JOY_BTN_NONE;
	}

}



// Funkcija JOY_get_button_state() vrne TRENUTNO stanje tipke "joysticka".
// Ker ima "joystick" eno samo tipko, je funkcija poenostavljena.
joystick_button_sig_value_t JOY_get_button_state(void)
{
	return joystick.button.state_new;
}








// ------- Funkcionalnost povezana z osmi "joysticka" ----------




// Funkcija JOY_calibrate() kalibrira "joystick". To pomeni, da
// funkcija spremlja meritve lege osi "joysticka" in si beleži,
// kolikšna je bila najmanjša oziroma največja vrednost meritve.
// Kalibrirane ekstremne vrednosti bomo nato uporabili za izračun
// relativne pozicije osi "joysticka".
// Kalibracijo zaključimo s pritiskom na tipko "joysticka".
void JOY_calibrate(void)
{

	// Pomožna spremenljivka, kjer hranimo informacijo o pritisnjeni tipki "joysticka".
	// Sprva privzamemo, da tipka "joysticka" še ni bila pritisnjena.
	joystick_buttons_enum_t pressed_key = DOPOLNI;


	// Dokler ni pritisnjena tipka "joystikca", izvajmo kalibracijo.
	while (pressed_key == DOPOLNI)
	{

		// Beležimo si minimalne vrednosti (najmanši odklon osi).

			// Za X os "joysticka".
			// Če je trenutna meritev odklona manjša od zabeležene minimalne vrednosti,
			if ( DOPOLNI )
			{
				// to vrednost zabeležimo kot novo minimalno vrednost.

					// DOPOLNI
			}

			// Za Y os "joysticka".
			// Če je trenutna meritve odklona manjša od zabeležene minimalne vrednosti,
			if ( DOPOLNI )
			{
				// to vrednost zabeležimo kot novo minimalno vrednost.

					// DOPOLNI
			}


		// Beležimo si maksimalne vrednosti (največji odklon osi).

			// Za X os "joysticka".
			// Če je trenutna meritev odklona večja od zabeležene maksimalne vrednosti,
			if ( DOPOLNI )
			{
				// to vrednost zabeležimo kot novo maksimalno vrednost.

					// DOPOLNI
			}

			// Za Y os "joysticka".
			// Če je trenutna meritev odklona večja od zabeležene maksimalne vrednosti,
			if ( DOPOLNI )
			{
				// to vrednost zabeležimo kot novo maksimalno vrednost.

					// DOPOLNI
			}



		// Iz ekstremnim vrednosti lahko poračunamo razpon odklona (angl. axis range).
		joystick.position_raw_range[X] = DOPOLNI;

			// DOPOLNI


		// Preverimo, če ni morda medtem bila pritisnjena tipka "joysticka".
		JOY_ // DOPOLNI
		pressed_key = DOPOLNI;



		// Izpišemo status "joysticka" preko SCI vmesnika, kar nam pomaga
		// pri "debuggiranju" kalibracije "joysticka".
		printf("******** CALIBRATION IN PROGRESS ********\n");
		JOY_SCI_send_status();


		// Dodamo časovni zamik, preden se ponovno lotimo beleženja ekstremnih vrednosti.
		HAL_Delay(100);

	}

}








// Funkcija JOY_get_axis_position() vrne RELATIVNO pozicijo osi "joysticka".
// Relativno pozicijo "joystcika" izračunamo na podlagi trenutne "surove" meritve
// pozicije osi ter ekstremnih vrednosti osi, ki jih hranimo v "handle" strukturi
// "joysticka". Os "joysticka" specificiramo kot vhodni argument funkcije.
// Funkcija mora poskrbeti tudi, da so vrednosti, ki jih vračamo, vedno smiselno
// omejene na interval [0..100].
uint8_t JOY_get_axis_position(joystick_axes_enum_t axis)
{

	// Pomožna spremenljivka, kjer bomo hranili izračunano relativno pozicijo osi.
	// Pozor: uporabimo predznačeni celoštevilski tip, ki nam bo pomagal zaznati
	// primer, da je trenutna meritev pozicije manjša od kalibrirane minimalne vrednosti.
	int16_t	relative_position;


	// Izračun relativne pozicije osi na procent natančno.
	// Pazite: uporablja se celoštevilska aritmetika! Operacija deljenja vrne celoštevilski količnik brez deleža zaradi ostanka!
	relative_position = DOPOLNI;


	// Poskrbimo še, da se vrnjena vrednost nahaja na smiselnem intervalu [0..100].

		// Obravnavamo primer, ko je trenutna meritev pozicije manjša od kalibrirane minimalne vrednosti.
		if ( DOPOLNI )
		{
			return DOPOLNI ;
		}

		// Obravnavamo primer, ko je trenutna meritev pozicije večja od kalibrirane maksimalne vrednosti.
		else if ( DOPOLNI )
		{
			return DOPOLNI ;
		}

		// Ostane le še primer, ko se izračunana relativna pozicija nahaja na intervalu [0..100].
		else
		{
			return DOPOLNI;
		}

}









// ------- Test functions ---------


// Funkcija JOY_SCI_send_status() je pomožna "debug" funkcija, ki nam pomaga izpisovati
// stanje "joysticka" preko serijskega vmesnika SCI. Tako lahko v terminalu opazujete
// meritve osi "joysticka" v realnem času.
void JOY_SCI_send_status(void)
{
	printf("--- Joystick status ---\n");

	// Sistemske spremenljivke "joystick" modula.
	printf("X_RAW = %d\n", DOPOLNI );
	printf("Y_RAW = %d\n", DOPOLNI );

	printf("X_RAW_MIN = %d\n", DOPOLNI );
	printf("X_RAW_MAX = %d\n", DOPOLNI );

	printf("Y_RAW_MIN = %d\n", DOPOLNI );
	printf("Y_RAW_MAX = %d\n", DOPOLNI );

	printf("X_RAW_RANGE = %d\n", DOPOLNI );
	printf("Y_RAW_RANGE = %d\n", DOPOLNI );


	// Trenutna relativna lega osi "joysticka".
	printf("X = %d\n", DOPOLNI  );
	printf("Y = %d\n", DOPOLNI  );

	printf("\n");
}




// Funkcija JOY_button_demo() demonstrira delovanje tipke "joysticka".
// Demonstracija je izvedena na popolnoma enak način, kot smo to storili
// v primeru tipkovnice.
void JOY_button_demo(void)
{

	joystick_buttons_enum_t pressed_key;


	// scan joystick buttons
	JOY_scan_button();

	// get next pressed button
	pressed_key = DOPOLNI;


	// read all pressed keys from the joystick buffer
	while (pressed_key != JOY_BTN_NONE)
	{
		// toggle LEDs according to pressed keys
		switch (pressed_key)
		{
		  case JOY_BTN_FIRE:

			  	  // DOPOLNI

			  break;

		  default:
			  break;
		}

		// get next pressed button
		pressed_key = DOPOLNI;

	}

	// test get button state
	LED_set(LED7, JOY_get_button_state() );


	// button scan period
	HAL_Delay(10);
}





// Funkcija JOY_LED_demo() demonstrira funkcionalnost "joysticka" s pomočjo
// prižiganja LEDice glede na trenutno relativno lego osi joysticka: če je os
// "joysticka" porinjena v skrajno pozicijo, potem sveti "krajna" LEDica.
void JOY_LED_demo(void)
{
	// DODATNA NEOBVEZNA NALOGA

	// DOPOLNI
}


