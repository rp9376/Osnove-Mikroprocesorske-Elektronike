/*
 * HC05.c
 *
 *  Created on: June 28, 2022
 *      Author: Rok Plesko
 */
#include "main.h"
#include "HC05.h"
#include "kbd.h"

#include "string.h"
#include "stm32g4xx_hal_uart.h"
#include "stdio.h"

UART_HandleTypeDef* BT_huartx;
UART_HandleTypeDef* CON_huartx;
uint8_t* Is_Connected;


void BT_init(UART_HandleTypeDef* BThuartx, UART_HandleTypeDef* CONhuartx, uint8_t* ConStatusAddr)
{
	BT_huartx = BThuartx;
	CON_huartx = CONhuartx;
	Is_Connected = ConStatusAddr;

}

void BT_test(UART_HandleTypeDef* BT_uart)
{


}


void BT_Connect()
{
	if(*Is_Connected == 0) //ce BT ni povezan na napravo ji pove naj se poveže na zadnji povezan MAC naslov
	{
		HAL_UART_Transmit_IT(BT_huartx, (uint8_t*) BP_MODE_COMMAND, strlen(BP_MODE_COMMAND));	//Poslje $$$ za vstop v commant mode
		HAL_Delay(50);
		HAL_UART_Transmit_IT(BT_huartx, (uint8_t*) BP_CONNENT, strlen(BP_CONNENT));				//Poslje "CFI" komanda za povezavo na zadnji pair
	}
}

void BT_Disconnect()
{
	if(*Is_Connected == 1)
	{
		uint8_t zero = 0x00; 	//hoce naslov in dobu bo naslov
		HAL_UART_Transmit_IT(BT_huartx, &zero, 1);	//pošlje 0 da prekine zvezo
	}
}


void MouseMoveClickWheel(int8_t X, int8_t Y, uint8_t Button, int8_t Wheel) //Generiranje paketa za miško
{
	uint8_t Packet[7];
	Packet[0] = 0xFD; 	//Start HID report: RAW Mode
	Packet[1] = 0x05;	//Lenght from next on					//Note: 0x5 == 0x05
	Packet[2] = 0x02;	//Descriptor byte
	Packet[3] = Button;
	Packet[4] = X;		//(-127 to 127)
	Packet[5] = Y;		//(-127 to 127)
	Packet[6] = Wheel;

	HAL_UART_Transmit(BT_huartx, Packet, sizeof(Packet), 1);	//pošlje paket
	//HAL_Delay(1); //Ali more bit Delay al pa blocking funkcija
}


//Funkcija pošlje en "Consumer key function" to se obnaša kot gumb ki ga je potrebno na koncu spustit (2 Paketa)
void SendDataByte(uint8_t val0, uint8_t val1) //pri uporabi funkcije se parametre vpiše kot je na HID datasheetu
{
	uint8_t Packet[5];
	Packet[0] = 0xFD; 	//Start HID report: RAW Mode
	Packet[1] = 0x03;	//Lenght from next on
	Packet[2] = 0x03;	//Descriptor byte
	Packet[3] = val1;
	Packet[4] = val0;

	HAL_UART_Transmit(BT_huartx, Packet, sizeof(Packet), 1);	//Pošlje paket

	Packet[3] = 0x00; 	//Pošlje da je "gumb" spuscen
	Packet[4] = 0x00; 	//it goes from back to front  //last bite goes first in the correct order //fucked indian

	HAL_UART_Transmit(BT_huartx, Packet, sizeof(Packet), 1);	//Pošlje paket
}

//Za razloko od zgornje funkcije ne pošlje paketa ki bi izpustil tipko
void SendSingleDataByte(uint8_t val0, uint8_t val1) //pri uporabi funkcije se parametre vpiše kot je na HID datasheetu
{
	uint8_t Packet[5];
	Packet[0] = 0xFD; 	//Start HID report: RAW Mode
	Packet[1] = 0x03;	//Lenght from next on
	Packet[2] = 0x03;	//Descriptor byte
	Packet[3] = val1;
	Packet[4] = val0;

	HAL_UART_Transmit(BT_huartx, Packet, sizeof(Packet), 1);	//Pošlje paket

}

//Pritisne tipko. Potrebno jo je tudi spustiti (funkcija se navadno klice 2x zapored)
void SendKey(uint8_t KeyMod, uint8_t KeyCode)
{
	uint8_t Packet[11];
	Packet[0] = 0xFD;		//Start HID report: RAW Mode
	Packet[1] = 0x09;		//Lenght from next on
	Packet[2] = 0x01;		//Identify as Keyboard packet
	Packet[3] = KeyMod;		//Keyboard Modifier (ctrl / shift itd...)
	Packet[4] = 0x00;		//Empty byte
	Packet[5] = KeyCode;	//Key code from chart
	Packet[6] = 0x00;
	Packet[7] = 0x00;		//Skupej je mogoče poslat 6 Keycodes (5 je praznih)
	Packet[8] = 0x00;
	Packet[9] = 0x00;
	Packet[10] = 0x00;

	HAL_UART_Transmit(BT_huartx, Packet, sizeof(Packet), 1);	//Pošlje paket
}

void SendKeyCode(uint8_t KeyCode)
{
	SendKey(0x00, KeyCode); 	//Pritisne tipko
	SendKey(0x00, 0x00);		//Spusti tipko
}

void SendKeyCode_Mod(uint8_t KeyCode, uint8_t KeyMod)
{
	SendKey(KeyMod, KeyCode); 	//Pritisne tipko
	SendKey(0x00, 0x00);		//Spusti tipko
}

//Tam nekje do 15 chatacterjev deluje
void SendString(char str[])
{
	HAL_UART_Transmit(BT_huartx, (uint8_t*) str, strlen(str), 1);
}

void SendCharAddr(char* chr)
{
	HAL_UART_Transmit(BT_huartx, (uint8_t*) chr, 1, 1);
}

void SendChar(char chr)
{
	HAL_UART_Transmit(BT_huartx, (uint8_t*) &chr, 1, 1);
}
