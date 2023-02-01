/*
 * HC05.h
 *
 *  Created on: May 14, 2022
 *      Author: Rok Plesko
 */

#ifndef INCLUDE_HC05_H_
#define INCLUDE_HC05_H_

#include "HC05_macros.h"
//#include "stm32g4xx_hal_uart.h" //to ocitno ne dela


void BT_init(UART_HandleTypeDef* BThuartx, UART_HandleTypeDef* CONhuartx, uint8_t* ConStatusAddr);
// void BT_test(UART_HandleTypeDef* BT_uart);

void BT_Connect();
void BT_Disconnect();

void MouseMoveClickWheel(int8_t X, int8_t Y, uint8_t Button, int8_t Wheel);
void SendDataByte(uint8_t val0, uint8_t val1);
void SendSingleDataByte(uint8_t val0, uint8_t val1);
void SendKey(uint8_t KeyMod, uint8_t KeyCode);

void SendKeyCode(uint8_t KeyCode);
void SendKeyCode_Mod(uint8_t KeyCode, uint8_t KeyMod);
void SendString(char str[]);
void SendCharAddr(char* chr); //Stupid je k ne mors met isga imena funkcij k majo razlocne parametre
void SendChar(char chr);

#endif /* INCLUDE_HC05_H_ */
