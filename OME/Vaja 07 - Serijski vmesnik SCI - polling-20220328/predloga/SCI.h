/*
 * SCI.h
 *
 *  Created on:
 *      Author:
 */

#ifndef INCLUDE_SCI_H_
#define INCLUDE_SCI_H_



// ----------- Include other modules (for public) -------------

// Vključimo nizko-nivojsko LL knjižnjico, da dobimo podporo za delo z USART vmesnikom.

	// DOPOLNI


// Pri implementaciji sistemskih funkcij serijskega vmesnika SCI bomo potrebovali sledeče nizko-nivojske funkcije:
//
//	// DOPOLNI
//
//

// Iz zgornjega seznama funkcij lahko vidimo, da bo potrebno v "handle" strukturi SCI vmesnika hraniti
// samo en parameter, ki določa, katero USARTx periferno enoto bomo uporabili.






// -------------------- Public definitions --------------------


// "Javno" definirajmo še pomožne "vrnjene kode" (angl. return codes), s katerimi bodo
// SCI funkcije sporočale, ali je bila operacija uspešna ali ne.
// Uporabimo naštevni tip.
typedef enum { SCI_ERROR=-1, SCI_NO_ERROR=0} SCI_rtrn_codes_t;





// ---------------- Public function prototypes ----------------

void SCI_init(void);

void SCI_send_char(char c);
void SCI_send_byte(uint8_t data);

uint8_t SCI_is_data_waiting(void);

SCI_rtrn_codes_t SCI_read_char(char *c);
SCI_rtrn_codes_t SCI_read_byte(uint8_t *data);


void SCI_send_string(char *str);
void SCI_send_bytes(uint8_t *data, uint32_t size);


void SCI_demo_Hello_world(void);
void SCI_demo_echo_with_polling(void);
void SCI_demo_Hello_world_printf(void);


#endif /* INCLUDE_SCI_H_ */
