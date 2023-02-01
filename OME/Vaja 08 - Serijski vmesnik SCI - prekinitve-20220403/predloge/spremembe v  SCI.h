

// ---------- Dopolniti je potrebno seznam uporabljanih LL funkcij ----------

// Pri implementaciji sistemskih funkcij serijskega vmesnika SCI bomo potrebovali 
// sledeče nizko-nivojske funkcije:
//		- void LL_USART_TransmitData8(USART_TypeDef *USARTx, uint8_t Value)
//		- uint8_t LL_USART_ReceiveData8(USART_TypeDef *USARTx)
//		- uint32_t LL_USART_IsActiveFlag_TXE_TXFNF(USART_TypeDef *USARTx)
//		- uint32_t LL_USART_IsActiveFlag_RXNE_RXFNE (USART_TypeDef * USARTx)
//
//			DOPOLNI seznam z novimi LL funkcijami, 
//				s pomočjo katerih uporabljamo USART prekinitve








// ---------  Dodati je potrebno PROTOTIPE za nove funkcije za delo s pomočjo prekinitev:

// SCI modulu bomo namreč dodali novo funkcionalnost, ki temelji na uporabi prekinitev.
// Dodali bomo funkciji za pošiljanje niza znakov oziroma skupine binarnih podatkov:
//
//		- SCI_send_string_IT 
//		- SCI_send_bytes_IT
//
// Mimogrede, končnica "_IT" v imenu funkcij namiguje, da sta ti dve funkciji implementirani
// s pomočjo prekinitev.

	// DOPOLNI s prototipi funkcij



// SCI modulu pa moramo tudi dodati t.i. "callback" funkciji:
//
//		- SCI_receive_char_Callback
//		- SCI_transmit_char_Callback
//
// "Callback" funkcije so funkcije, ki jih polličemo, ko se zgodi ustrezna prekinitev, 
// in pravzaprav realizirajo vsebino prekinitvene rutine.
//
// Prvo funkcijo bomo s pomočjo prekinitev poklicali vsakič, ko bo USART sprejemnik 
// sprejel nov podatek in bo poskrbela, da se ta podatek shrani v 
// sprejemni RX sistemski medpomnilnik.
//
// Drugo funkcijo pa bomo s pomočjo prekinitev poklicali vsakič, ko bo USART oddajnik 
// pripravljen sprejeti nov podatek za pošiljanje. Ta funkcija bo poskrbela, da se
// pošljejo vsi podatki, ki čakajo v oddajnem TX sistemskem medpomnilniku.


	// DOPOLNI s prototipi funkcij

