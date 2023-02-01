/*
  BPLib.cpp - Library for communication with RN-42 HID Bluetooth module
  Created by Basel Al-Rudainy, 6 april 2013.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  Modified by: Rok Pleško
  December 2018
*/

#include "Arduino.h"
#include <SoftwareSerial.h>
#include "RN42BT.h"

SoftwareSerial BTserial(2, 3);  //(RX, TX)

RN42BT::RN42BT()
{

  Serial.begin(115200);
  Keycode = 0x00;
  BTserial.begin(115200);
}

bool RN42BT::begin()
{
  BTserial.print(BP_MODE_COMMAND); // Sends  "$$$"

  while (!BTserial.available()) {
    Serial.println("waitnig..");
    delay(1000);
  }
  //delay(5000);
  String wharBTSaid = BTserial.readString();
  Serial.println(wharBTSaid);
  if (wharBTSaid[0] == 'C') //nothing worked so.. this //comunication is bad
    Serial.println("WE IN BOYSSS");
  else
    Serial.println("SOMETHING WENT FUCKING WRONG");

  //you can write code to rename or conigure this little fucker


  BTserial.print(BP_MODE_EXITCOMMAND);  //EXIT CMD
  while (!BTserial.available()) {
    Serial.println("waitnig..");
    delay(1000);
  }
  wharBTSaid = BTserial.readString();
  Serial.println(wharBTSaid);
  if (wharBTSaid[0] == 'E')
    Serial.println("WE OUT");

}


bool RN42BT::ManualConf()//after "$$$" select Newline so it adds "\r\n" at the end
{
  Serial.println("Manual configuration mode");
  while (1) //you are never coming out
  {
    if (BTserial.available())
    {
      Serial.print((char)BTserial.read());
    }
    if (Serial.available())
    {
      BTserial.print((char)Serial.read());
    }
  }
}

bool RN42BT::SerialToBTKeyboard()
{
  Serial.println("Type a string to write");
  while (!Serial.available()) {}
  delay(100);

  char string[32];
  int availableBytes = Serial.available();

  for (int i = 0; i < availableBytes; i++)
    string[i] = Serial.read();

  Serial.print("Typing: ");
  for (int i = 0; i < availableBytes; i++)
    Serial.print(string[i]);

  for (int i = 0; i < availableBytes; i++)
    BTserial.print(string[i]);
}

bool RN42BT::sendKeyCode(byte val, bool mod)
{
  Keycode = val;
  KeyMod = mod;
  sendkey();
  clearkey();
  sendkey();
}

bool RN42BT::sendKeyCode(byte val)
{
  Keycode = val;
  sendkey();
  clearkey();
  sendkey();
}

bool RN42BT::sendkey()
{
  BTserial.write((byte)0xFD); //Start HID Report
  BTserial.write((byte)0x9); //Length byte
  BTserial.write((byte)0x1); //Descriptor byte
  BTserial.write((byte)KeyMod); //Modifier byte
  BTserial.write((byte)0x00); //-
  BTserial.write((byte)Keycode); //Send KEY
  for (byte i = 0; i < 5; i++) { //Send five zero bytes
    BTserial.write((byte)0x00);
  }
}

void RN42BT::clearkey()
{
  Keycode = 0x00;
  KeyMod = BP_MOD_NOMOD;
}

bool RN42BT::sendString(char val[])
{
  int velikost = strlen(val);
  Serial.print(velikost);

  for (int i = 0; i < velikost; i++)
  {
    BTserial.print(val[i]);
    delay(50);
  }
}

bool RN42BT::sendChar(char val)
{
  BTserial.print(val);
}

void RN42BT::mouseClick(byte BP_BUTTON)
{
  mousePress(BP_BUTTON);
  mouseReleaseAll();
}

void RN42BT::sendDataByte(byte val0, byte val1)
{
  BTserial.write((byte)0xFD);
  BTserial.write((byte)0x03);
  BTserial.write((byte)0x03);

  BTserial.write(val1);
  BTserial.write(val0); // ships track because 0x0100 //it goes from back to front



  BTserial.write((byte)0xFD);
  BTserial.write((byte)0x03);
  BTserial.write((byte)0x03);

  BTserial.write((byte)0x00);
  BTserial.write((byte)0x00);
}

void RN42BT::connect()
{
  BTserial.write(BP_MODE_COMMAND);
}

void RN42BT::disconnect()
{
  BTserial.write((byte)0x00);
}
void RN42BT::mouseMove(signed int BP_X, signed int BP_Y, byte BP_BUTTON, signed int WHEEL)
{
  BTserial.write((byte)0xFD); //Start HID Report
  BTserial.write((byte)0x5); //Length byte
  BTserial.write((byte)0x2); //Descriptor byte
  BTserial.write(BP_BUTTON); //Button byte
  BTserial.write(BP_X);  //(-127 to 127)
  BTserial.write(BP_Y);  //(-127 to 127)
  BTserial.write(WHEEL);
}

void RN42BT::mousePress(byte BP_BUTTON)
{
  BTserial.write((byte)0xFD); //Start HID Report
  BTserial.write((byte)0x5); //Length byte
  BTserial.write((byte)0x2); //Descriptor byte
  BTserial.write(BP_BUTTON); //Button byte
  for (byte i = 0; i < 3; i++) { //Send three zero bytes
    BTserial.write((byte)0x00);
  }

}
void RN42BT::mouseReleaseAll()
{
  BTserial.write((byte)0xFD); //Start HID Report
  BTserial.write((byte)0x5); //Length byte
  BTserial.write((byte)0x2); //Descriptor byte
  for (byte i = 0; i < 4; i++) { //Send four zero bytes
    BTserial.write((byte)0x00);
  }
}

void RN42BT::mouseWheel(signed int BP_WHEEL)
{
  BTserial.write((byte)0xFD); //Start HID Report
  BTserial.write((byte)0x5); //Length byte
  BTserial.write((byte)0x2); //Descriptor byte
  for (byte i = 0; i < 3; i++) { //Send three zero bytes
    BTserial.write((byte)0x00);
  }
  BTserial.write(BP_WHEEL); //Wheel byte (-127 to 127)
}
