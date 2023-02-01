

// --------- Dodati je potrebno knjižnico za delo z bufferji:

// S pomočjo modula "buf.c" bomo lahko implementirali SCI sprejemni (RX) ciklični medpomnilnik,
// ki bo hranil sprejete, a še neobdelane podatke, ter SCI oddajni (TX) medpomnilnik, ki pa bo 
// hranil podatke, ki jih je še potrebno poslati.

	// 	DOPOLNI #include ...







// --------- Dodati je potrebno definicije v zvezi s sistemskimi SCI medpomnilniki:



// ------ SCI receive (RX) buffer definitions -------

// Pripraviti je potrebno podatkovne strukture, s katerimi bomo implementirali 
// sprejemni medpomnilnik.

// Definirajmo makro parameter, ki bo specificiral dolžino medpomnilnika.
#define SCI_RX_BUF_LEN 	DOPOLNI

// In definirajmo še dve podatkovni strukturi, ki sta potrebni za implementacijo
// medpomnilnika.
uint8_t SCI_RX_buffer[DOPOLNI];			// tabela bajtov, ki bo hranila podatke
buf_handle_t SCI_RX_buf_handle;			// "handle" struktura za RX medpomnilnik




// ------ SCI transmit (TX) buffer definitions -------

// Pripraviti je potrebno podatkovne strukture, s katerimi bomo implementirali 
// sprejemni medpomnilnik.

// Definirajmo makro parameter, ki bo specificiral dolžino medpomnilnika.
#define SCI_TX_BUF_LEN 	DOPOLNI

// In definirajmo še dve podatkovni strukturi, ki sta potrebni za implementacijo
// medpomnilnika.
uint8_t SCI_TX_buffer[DOPOLNI];			// tabela bajtov, ki bo hranila podatke
buf_handle_t SCI_TX_buf_handle;			// "handle" struktura za TX medpomnilnik







// ---------- Dopolniti je potrebno SCI_init():


// --- Spremeniti je potrebno komentar za opis vsebine SCI_init() funkcije:


// Funkcija SCI_init() poskrbi za inicializacijo "handle" strukture SCI,
// nastavi dolžino medpomnilnika printf() funkcije, poskrbi za inicializacijo
// sprejemnega RX in oddajnega TX sistemskega medpomnilnika za SCI vmesnik
// in omogoči prekinitve v zvezi s sprejemom podatkov.




// ----- Dodati je potrebno še dva koraka v inizializaciji:

	
	// 3. Inicializacija SCI medpomnilnikov  (RX and TX)
		BUF_init( &SCI_RX_buf_handle, SCI_RX_buffer, SCI_RX_BUF_LEN);	// RX SCI medpomnilnik
		DOPOLNI( DOPOLNI, DOPOLNI, DOPOLNI);							// TX SCI medpomnilnik


    // 4. Omogočitev prekinitev ob prejemu novega podatka
		
		// Kot zadnji korak inicializacije SCI vmesnika poskrbimo, da se vklopijo
		// prekinitve ob sprejemu novega podatka presko USART enote, s katero
		// implementiramo SCI vmesnik. Uporabimo seveda primerno LL funkcijo,
		// ki omogoči prekinitve ob postavitvi RXNE zastavice.
		
			// DOPOLNI

		
		// V vednost: prekinitve ob sprejemu novega podatka lahko vklopimo šele,
		// ko že imamo pripravljen sprejemni RX medpomnilnik, kamor se bodo ob 
		// prekinitvah shranjevali novoprejeti podatki.









// ---------- Dodati je potrebno funkciji za pošiljanje več podatkov s pomočjo prekinitev:


// ------ Funkcije za pošiljanje niza znakov ali zaporedja bajtov s pomočjo prekinitev -------


// Funkcija SCI_send_string_IT() pošlje znakovni niz (tj. string) preko SCI vmesnika s pomočjo prekinitev.
void SCI_send_string_IT(char *str)
{
	// pomožni spremenljivki
	uint32_t i = 0;		// indeks
	uint8_t c;			// hrani znak, ki ga bomo poskusili poslati takoj

	
	// Najprej je potrebno celoten znakovni niz "*str" shraniti v oddajni medpomnilnik.
	// Z "while" zanko se sprehodimo preko vseh znakov niza
	while( str[i] != DOPOLNI)
	{
		// in jih enega po enega shranjujemo v oddajni mepodmnilnik.
		BUF_store_byte( &DOPOLNI, (uint8_t) DOPOLNI );
		
		// Indeks se premakne na naslednji znak v nizu.
		
			// DOPOLNI
	}

	
	// Če je potrebno poslati vsaj en znak,
	if ( i > DOPOLNI )
	{

		// najprej preverimo, če lahko prvi znak za pošiljanje vpišemo 
		// v oddajni podatkovni register TDR že kar takoj. Uporabimo
		// ustrezno LL funkcijo, ki nam vrne to informacijo. 
		if ( LL_USART_IsActiveFlag_TXE_TXFNF(SCI.USART) )		// TX empty?
		{
			// Če oddajnik lahko sprejme nov znak, potem ta prvi znak
			// najprej preberemo iz oddajnega medpomnilnika v pomožno 
			// spremenljivko "c".
			BUF_get_byte( &DOPOLNI, DOPOLNI );

			// in nato ta znak s pomočjo LL funkcije takoj vpišemo 
			// v oddajni podatkovni register.
			
				// DOPOLNI

			// V vednost: pisanje v oddajni podatkovni register bo avtomatsko zbrisalo 
			// TXE zastavico.
			
		}

		// Z zgornjo kodo smo zagovotili, da se trenutno v oddajnem podatkovnem 
		// registru zagovoto nahaja nov podatek, ki se bo kmalu poslal.

		// In sedaj ključni del: ko se bo nov podatek pričel pošiljati, bo 
		// oddajni podatkovni register spet prost (TXE) in takrat lahko vanj
		// takoj vpišemo naslednji podatek, ki ga želimo poslati iz oddajnega medpomnilnika.
		// In ta vpis naslednjega podatka bomo opravili s pomočjo prekinitvene rutine.
		//
		// Da pa bo sploh prišlo do prekinitve, ko bo oddajni register spet prost,
		// je pa potrebno te prekinitve najprej omogočiti. To storimo z LL funkcijo
		// tu spodaj.
		
			// DOPOLNI

	}

}




// Funkcija SCI_send_bytes_IT() pošlje zaporedje bajtov preko SCI vmesnika s pomočjo prekinitev.
// Lokacija podatkov zapošiljanje je podana z vhodnim argumentom "*data",
// dolžina podatkov za pošiljanje pa je podano z vhodnim argumentom "size".
void SCI_send_bytes_IT(uint8_t *data, uint32_t size)
{
	// pomožna spremenljivka za hranjenje enega bajta podakov
	uint8_t	d;

	
	// Najprej je potrebno celotno zaporedje bajtov z naslova "data" shraniti v oddajni medpomnilnik.
	// To storimo s "for" zanko.
	for(uint32_t i=0; i < size ; i++ )
	{
		BUF_store_byte( &DOPOLNI, DOPOLNI );
	}


	// Če je potrebno poslati vsaj en znak,
	if ( size > DOPOLNI )
	{
		// najprej preverimo, če lahko prvi bajt za pošiljanje vpišemo 
		// v oddajni podatkovni register TDR že kar takoj. Uporabimo
		// ustrezno LL funkcijo, ki nam vrne to informacijo. 
		if ( LL_USART_IsActiveFlag_TXE_TXFNF(SCI.USART) )		// TX empty?
		{
			// Če oddajnik lahko sprejme nov bajt, potem ta prvi bajt
			// najprej preberemo iz oddajnega medpomnilnika v pomožno 
			// spremenljivko "d".
			BUF_get_byte( &DOPOLNI, DOPOLNI );

			// in nato ta bajt s pomočjo LL funkcije takoj vpišemo 
			// v oddajni podatkovni register.
			
				// DOPOLNI

			// V vednost: pisanje v oddajni podatkovni register bo avtomatsko zbrisalo 
			// TXE zastavico.
		}


		// Z zgornjo kodo smo zagovotili, da se trenutno v oddajnem podatkovnem 
		// registru zagovoto nahaja nov podatek, ki se bo kmalu poslal.

		// In sedaj ključni del: ko se bo nov podatek pričel pošiljati, bo 
		// oddajni podatkovni register spet prost (TXE) in takrat lahko vanj
		// takoj vpišemo naslednji podatek, ki ga želimo poslati iz oddajnega medpomnilnika.
		// In ta vpis naslednjega podatka bomo opravili s pomočjo prekinitvene rutine.
		//
		// Da pa bo sploh prišlo do prekinitve, ko bo oddajni register spet prost,
		// je pa potrebno te prekinitve najprej omogočiti. To storimo z LL funkcijo
		// tu spodaj.
		
			// DOPOLNI
	}

}






// ------------ Dodati je potrebno "callback" funkcije za pošiljanje in sprejemanje enega samega znaka:



// ------- "callback" funkcije, ki implementirajo prekinitvene rutine ---------

// Funkcija SCI_receive_char_Callback() je "callback" funkcija, ki jo bomo poklicali
// ob prekinitvah, ko bo sprejet nov znak preko USARTa, s katerim implementiramo sistemski SCI vmesnik.
void SCI_receive_char_Callback(void)
{
	// pomožna spremenljivka za novo-sprejeti podatek
	uint8_t received_data;
	
	// Ko preko USART vmesnika prejmemo nov podatek, ga shranimo v sprejemni RX medpomnilnik SCI vmesnika.
	
	
	// Najprej z uporabo LL funkcije preberemo novo-sprejeti podatek in ga shranimo v pomožno spremenljivko.
	received_data = DOPOLNI;
	
	// Nato pa ta podatek shranimo v sprejemni RX medpomnilnik SCI vmesnika za nadaljno obdelavo kasneje.
	BUF_store_byte( &DOPOLNI, DOPOLNI );
}






// Funkcija SCI_transmit_char_Callback() je "callback" funkcija, ki jo bomo poklicali
// ob prekinitvah, ko bo oddajni register USART vmesnika prost (tj. bo lahko sprejel nov podatek).
void SCI_transmit_char_Callback(void)
{
	// pomožna spremenljivke
	uint8_t 			data_to_transmit;		// sem shranimo podatek, ki ga želimo poslati
	buf_rtrn_codes_t	return_code;			// sem shranimo rezultat poskusa branja iz medpomnilnika


	// Najprej poskusimo prebrati naslednji podatek, ki ga želimo poslati.
	// Zapomnimo si "vrnjeno kodo" (angl. return code), ki jo vrne BUF_ funkcija.
	return_code = BUF_get_byte( &DOPOLNI, data_to_transmit );

	// S pomočjo "vrnjene kode" ugotovimo, če sedaj imamo na voljo naslednji podatek za pošiljanje.
	if ( return_code == BUFFER_OK )
	{
		// In če je na voljo naslednji podatek, ga kar vpišemo v oddajni podatkovni register
		// USART vmesnika s pomočjo LL funkcije.
		
			// DOPOLNI
	}


	// Po vsakem podatku, ki ga pošljemo, je potrebno preveriti, če smo morda 
	// poslali zadnji podatek. To je pomembno, saj moramo v tem primeru ustaviti
	// "avtomatsko" pošiljanje podatkov s pomočjo prekinitev.
	if ( BUF_get_data_size( &SCI_TX_buf_handle ) == 0)
	{
		// In če smo res poslali zadnji podatek, potem moramo onemogočiti nadaljne 
		// prekinitve ob sprostitvi oddajnega podatkovnega registra (TXE),
		// saj nimamo več kaj pošiljati. Tako onemogočimo avtomatsko 
		// pošiljanje iz oddajnega TX medpomnilnika SCI vmesnika s pomočjo prekinitev.
		// Uporabimo ustrezno LL funkcijo za onemogočitev prekinitve.
		
			//	DOPOLNI
	}

}








// ---------- Dodati je potrebno nove testne funkcije za demonstracijo uporabe prekinitev:


// Funkcija SCI_demo_receive_with_interrupts() demonstrira sprejem podatkov s pomočjo prekinitev.
// To stori tako, da ves čas preverja sprejemni RX medpomnilnik SCI vmesnika, kjer se s pomočjo
// prekinitvene rutine shranjujejo sprejeti podatki. In če so v tem medpomnilnu na voljo novi
// podatki, jih pošlje takoj nazaj pošiljatelju (echo) bajt po bajt.
void SCI_demo_receive_with_interrupts(void)
{

	// pomožna spremenljivka 
	uint8_t data;	// tu shranimo naslednji sprejeti podatek

	while(1)
	{
		// Preveri, če v sprejemnem RX medpomnilniku SCI vmesnika na voljo novi podatki.
		if ( BUF_get_data_size( &SCI_RX_buf_handle) )
		{
			// Če so, preberi naslednji sprejeti podatek in ga shrani v pomožno spremenljivko.
			BUF_get_byte( &DOPOLNI, DOPOLNI );

			// Nato pa ta podatek pošlji takoj nazaj s pomočjo SCI_send_byte() funkcije 
			// (tj. brez uporabe prekinitev).
			SCI_send_byte(DOPOLNI);

		}
	}

}




// Funkcija SCI_demo_transmit_with_interrupts() demonstrira pošiljanje podatkov s pomočjo prekinitev.
// To stori tako, da za pošiljanje sporočila uporabi funkcijo SCI_send_string_IT().
void SCI_demo_transmit_with_interrupts(void)
{
	// Definiramo sporočilo, ki ga bomo poslali.
	char message[100] = "This was sent using USART interrupts!\n";

	// Nato pa pričnemo s pošiljanjem enega in istega sporočila.
	while(1)
	{
		// Sporočilo pošljemo z uporabo SCI funkcije za pošiljanja niza znakov s pomočjo prekinitev.
		
			// DOPOLNI

		// Nato pa počakamo eno sekundo (premor med sporočili).
		
			// DOPOLNI

	}

}




// Funkcija SCI_demo_echo_with_interrupts() demonstrira "echo funkcionalnost" s pomočjo uporabe prekintev
// za sprejemanje in pošiljanje podatkov. Ideja testne funkcije je popolnoma enaka kot v primeru "polling demo"
// funkcije SCI_demo_echo_with_polling(), le da tokrat za sprejem podatkov poskrbijo prekinitve v navezi s sprejemnim
// RX medpomnilnikom SCI vmesnika. Pošiljanje podatkov nazaj pa je seveda tudi izvedeno s pomočjo prekinitev s 
// funkcijo SCI_send_bytes_IT().
void SCI_demo_echo_with_interrupts(void)
{

	// spremenljivke, s pomočjo katerih bomo simulirali "zaposlenost procesorja" ("CPU busy")
	#define N_MAX_IT		500

	float a_0 = 0.5;
	float a_n;
	float sum = 0;


	// pomožna spremenljivke za tvorjenje sporočila, ki ga bomo poslali nazaj pošiljatelju
	uint8_t message[SCI_RX_BUF_LEN];
	uint32_t message_size;

	
	// V neskončni zanki
	while(1)
	{


		
		// preverjamo, koliko bajtov novo-sprejetih podatkov je na voljo v sprejemnem RX medpomnilniku SCI vmesnika.
		message_size = BUF_get_data_size( &SCI_RX_buf_handle);
		
		// In če je na voljo vsaj en bajt podatkov,
		if ( message_size > DOPOLNI )
		{
			
			// shranimo te novo-sprejete podatke v pomožno spremenljivko za sporočilo, ki ga bomo poslali nazaj.
			BUF_get_bytes( &SCI_RX_buf_handle, DOPOLNI, DOPOLNI );

			// In nato vsebino te pomožne spremenljivke pošljemo nazaj pošiljatelju z uporabo funkcije, 
			// ki pošilja binarne podatke s pomočjo prekinitev.
			
				// DOPOLNI

		}




		// Potem pa simuliramo "zaposlenost procesorja" ("CPU busy") z drugimi opravili.
		// V našem primeru bomo to simulirali tako, da bomo računali privh N_MAX_IT členov
		// geometrijske vsote.
		//
		// Večajte število členov N_MAX_IT in opazujte, če povečana zaposlenost procesorja
		// še vedno vpliva na sprejem podatkov preko serijskega vmesnika. Napake v sprejemu
		// podatkov seveda opazujete v "echo" odzivu na terminalu.


		a_n = a_0;
		for(uint32_t n=0; n<N_MAX_IT; n++)
		{
			 sum = sum + a_n;
			 a_n = a_n * a_0;
		}


	}


}



















