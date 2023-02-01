


// -------- Prekinitvam je potrebno dodati sistemsko funkcionalnost SCI vmesnika:

// Znotraj prekinitvene rutine USART3_IRQHandler() moramo biti sposobni poklicati,
// t.i. "callback" funkcije za sprejemanje novega podatka oziroma pošiljanje novega
// podatka preko serijskega vmesnika SCI. Te "callback" funkcije so pravzaprav del sistema,
// ki se odziva na prekinitve na strojnem nivoju. Vidite lahko, da tokrat pa 
// nižje-nivojski strojni nivo (tj. USART enota) potrebuje storitve 
// višjega sistemskega nivoja (tj. medpomnilnikov SCI vmesnika):
//		- ob sprejemu želimo sprejeti podatek shraniti v sistemski SCI RX medpomnilnik
//		- pri pošiljanju podatkov želimo podatke jemati iz sistemskega SCI TX medpomnilnika


	// 	DOPOLNI #include ...








// ----------- Implementirati je potrebno t. i. "IRQ handler" funkcijo za prekinitve v zvezi z USART3 vmesnikom,
// s pomočjo katerega smo implementirali sistemki serijski vmesnik SCI:


// Funkcija USART3_IRQHandler() se izvede vsakič, ko se sproži katerakoli od prekinitev USART3 vmesnika.
// Funkcija USART3_IRQHandler() je torej pravzaprav splošna prekinitvena rutina USART3 vmesnika.
// Znotraj te splošne prekinitvene rutine je potrebno ugotoviti, kateri od specifičnih prekinitvenih
// dogodkov je sprožil prekinitev. Za nas bosta ključna prekinitvena dogodka sprejetje novega podatka (RXNE)
// ter sprostitev oddajnega podatkovnega registra (TXE).
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

	
	// Kot že rečeno, je potrebno znotraj prekinitvene rutine ugotoviti, kateri od specifičnih 
	// prekinitvenih dogodkov je sprožil globalno USART3 prekinitev in se potem ustrezno odzvati
	// na ta prekinitveni dogodek s "callback funkcijo".

	// Vir prekinitve ugotavljamo s pomočjo prekinitveno-statusnega registra USART vmesnika
	// ob pomoči LL funkcij.

	// Nujno pa je tudi, da preden se odzovemo na specifični vir prekinitve, preverimo, 
	// če je ta specifična prekinitev sploh omogočena. Če tega ne bi storili, tvegamo,
	// da se na prekinitveni dogodek odzovemo z napačno prekinitveno "callback" rutino.
	

	
	

	// ------ Odzivanje na novo-sprejeti podatek (zastavica RXNE = Receive data register not empty) -------

		
		// Najprej preverimo, če je ta specifična prekinitev sploh omogočena. Uporabimo LL funkcijo.
		if( DOPOLNI_Z_IMENOM_LL_FUNKCIJE(USART3) )		// sploh omogočena prekinitev ob RXNE?
		{
			// Če je prekinitev omogočena, potem preverimo še, če je postavljena ustrezna zastavica.
			if( DOPOLNI_Z_IMENOM_LL_FUNKCIJE(USART3) )	// postavljena zastavica RXNE?
			{
				// Če je ta specifična prekinitev omogočena in če je postavljena zastavica tega specifičnega
				// prekinitvenega dogodka, potem se odzovemo s klicem ustrezne "callback" rutine.
				
					// DOPOLNI

				// V vednost: zastavica RXNE se zbriše avtomatsko, ko preberemo sprejemni register RDR.
			}
		}




	// ------ Odzivanje na sprostitev oddajnega podatkovnega registra TDR (zastavica TXE = Transmitter Empty) -------

		// Najprej preverimo, če je ta specifična prekinitev sploh omogočena. Uporabimo LL funkcijo.
		if( DOPOLNI_Z_IMENOM_LL_FUNKCIJE(USART3) )		// sploh omogočena prekinitev ob TXE?
		{
			// Če je prekinitev omogočena, potem preverimo še, če je postavljena ustrezna zastavica.
			if( DOPOLNI_Z_IMENOM_LL_FUNKCIJE(USART3) )		// postavljena zastavica TXE?
			{
				// Če je ta specifična prekinitev omogočena in če je postavljena zastavica tega specifičnega
				// prekinitvenega dogodka, potem se odzovemo s klicem ustrezne "callback" rutine.
				
					// DOPOLNI

				// V vednost: zastavica TXE se zbriše avtomatsko, ko pišemo v oddajni podatkovni register TDR.
			}
		}




  /* USER CODE END USART3_IRQn 0 */
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}






