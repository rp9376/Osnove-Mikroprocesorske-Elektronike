// Funkcija KBD_demo_toggle_LEDs_if_buttons_pressed() je namenjena testiranju
// delovanja tipkovnice. Deluje tako, da ugotovi, katere tipke so bile pritisnjene
// in se na te pritiske odzove s spremembo stanja ustrezne LEDice ("toggle").
//
// PAZITE: demo funkcija ne izvaja skeniranja tipkovnice! To je potrebno
// izvesti zunaj te funkcije.
void KBD_demo_toggle_LEDs_if_buttons_pressed(void)
{

	// Pomožna spremenljivka, kjer bomo hranili informacijo o nazadnje 
	// pritisnjeni tipki.
	buttons_enum_t pressed_key;


	// Preberemo, katera tipka je bila pritisnjena nazadnje 
	// (uporabite ustrezno KBD_ funkcijo).
	pressed_key = DOPOLNI ;


	// Če je v pomožni spremenljivki informacija o pritisku dejanske tipke,
	while (pressed_key != BTN_NONE)
	{
		// spremenimo stanje ustrezne LEDice glede na to, katera tipka
		// je bila pritisnjena.
		switch ( DOPOLNI )
		{
		  case BTN_OK:
			  LED_toggle(LED0);
			  break;

		  // DOPOLNITE še za ostale tipke
		  

		  default:
			  break;
		}


		// Preberemo, če je bila morda pritisnjena še kaka tipka,
		// ki še ni bila obdelana.
		pressed_key = DOPOLNI ;

	}

}