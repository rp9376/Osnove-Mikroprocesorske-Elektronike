#include "RN42BT.h"

RN42BT Bluetooth;

void setup() {
  Serial.begin(115200);

  //Bluetooth.ManualConf();
  pinMode(A5, INPUT_PULLUP); //joystick switch
  pinMode(6, OUTPUT);// LED Red
  pinMode(5, OUTPUT);// LED Green
  pinMode(A4, INPUT_PULLUP);//L1
  pinMode(A3, INPUT_PULLUP);//L2
  pinMode(A2, INPUT_PULLUP);//L3
  pinMode(7, INPUT_PULLUP);//R1
  pinMode(8, INPUT_PULLUP);//R2
  pinMode(4, INPUT_PULLUP);//R3
  pinMode(13, INPUT_PULLUP);//U1
  pinMode(12, INPUT_PULLUP);//U2
  pinMode(A1, INPUT_PULLUP);//D1
  pinMode(A0, INPUT_PULLUP);//D2

  digitalWrite(6, HIGH); //red light
  //digitalWrite(5, HIGH); //to more bit zakomenteran
}

const int redPin = 9;   //RGB LED
const int greenPin = 10;
const int bluePin = 11;
unsigned int rgbColour[3];//rainbow table
bool clack = 0;

bool mode = 0; // 0=mouse / 1=keyboard
bool change = 1; //goes to 1 if mode changed
bool capsLock = 0;

void loop()
{
  
  tenMagicButtons();

  if (change) //to change the rgb light
  {
    if (mode)
    {
      if (!capsLock)
        setColourRgb(180, 255, 0);
      else
        setColourRgb(255, 255, 0);
    }
    else
    {
      setColourRgb(0, 255, 255);
    }
    change = 0;
  }

  if (!mode)
  {
    joystickBTMouse();
  }
  else
  {
    joystickBTKeyboard();
  }

  delay(5);
}

bool clackU1 = 0;
bool clackU2 = 0;
bool clackR1 = 0;
bool clackR2 = 0;
bool clackR3 = 0;
bool clackL1 = 0;
bool clackL2 = 0;
bool clackL3 = 0;
bool clackD1 = 0;
bool clackD2 = 0;
int eastercounter = 0;
bool outOfEaster = 0;
bool easterLightMode;
//bool capsLock = 0;  //deklatitano zgoraj
byte button = 0x00; //od joymouse funkcije
bool update = 0;    //od joymouse funkcije
int wheel = 0;      //od joymouse funkcije
void tenMagicButtons()
{
  //------------------------------------------------------------------U1
  if (digitalRead(13) == LOW && clackU1 == 0)
  {
    if (outOfEaster)
    {
      outOfEaster = 0;
    }
    else
    {
      digitalWrite(5, HIGH);
      if(!mode)
      Bluetooth.connect();
        else
      Bluetooth.disconnect();
      delay(100);
      digitalWrite(5, LOW);
      delay(50);
      digitalWrite(5, HIGH);
      delay(100);
      digitalWrite(5, LOW);
    }
    clackU1 = 1;
    eastercounter = 0;
    delay(3);
  }
  if (digitalRead(13) == HIGH)
  {
    clackU1 = 0;
  }
  //------------------------------------------------------------------U2    //3x triggers easter egg
  if (digitalRead(12) == LOW && clackU2 == 0)
  {
    eastercounter++;
    if (eastercounter == 5)
    {
      rainbowinit();
      easterLightMode = 0;
      do {
        rainbowloop();
      } while (!outOfEaster);
      eastercounter = 0;
      change = 1;
      //mode = !mode;
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
    }
    else
    {
      mode = !mode;
      change = 1;
    }

    clackU2 = 1;

    delay(3);
  }
  if (digitalRead(12) == HIGH)
  {
    clackU2 = 0;
  }
  //------------------------------------------------------------------R1
  if (digitalRead(7) == LOW)
  {
    if (!mode)
    { // mouse mode
      if (wheel == 0)
        wheel = 1;
      update = 1;
      delay(50);
    }
    else
    { //keyboard mode
      if (clackR1 == 0)
      {
        digitalWrite(5, HIGH);
        Bluetooth.sendChar((int)13);
        delay(3);
        digitalWrite(5, LOW);
      }
    }
    clackR1 = 1;
    eastercounter = 0;
    delay(3);
  }

  if (digitalRead(7) == HIGH)
  {
    if (clackR1 == 1)
    {
      wheel = 0;
      update = 1;
    }

    clackR1 = 0;
  }
  //------------------------------------------------------------------R2
  if (digitalRead(8) == LOW && clackR2 == 0)
  {
    digitalWrite(5, HIGH);
    if (!mode)
    { // mouse mode
      Bluetooth.sendDataByte(0x00, 0x01);
    }
    else
    { //keyboard mode
      Bluetooth.sendKeyCode(0x39);
      change = 1;
      capsLock = !capsLock;

    }
    eastercounter = 0;
    clackR2 = 1;
    delay(3);
    digitalWrite(5, LOW);

  }
  if (digitalRead(8) == HIGH)
  {
    clackR2 = 0;
  }
  //------------------------------------------------------------------R3
  if (digitalRead(4) == LOW)
  {
    if (!mode)
    { // mouse mode
      if (wheel == 0)
        wheel = -1;
      update = 1;
      delay(50);
    }
    else
    { //keyboard mode
      if (clackR3 == 0)
      {
        /*digitalWrite(5, HIGH);
          Bluetooth.sendKeyCode(0x51);
          delay(3);
          digitalWrite(5, LOW);*/
        wordTyper("Pointer Box");
        delay(10);
        Bluetooth.sendChar((int)13); Bluetooth.sendChar((int)13);
        delay(10);
        wordTyper("By: Rok Plesko");
        delay(10);
        Bluetooth.sendChar((int)13); Bluetooth.sendChar((int)13);
        delay(10);
        wordTyper("Vegova 2018/2019");
        delay(10);
        Bluetooth.sendChar((int)13); Bluetooth.sendChar((int)13);
        delay(10);
        wordTyper("plesko.rok@gmail.com"); Bluetooth.sendChar((int)13); //RIP
      }
    }
    clackR3 = 1;
    eastercounter = 0;
    delay(3);
  }

  if (digitalRead(4) == HIGH)
  {
    if (clackR3 == 1)
    {
      wheel = 0;
      update = 1;
    }

    clackR3 = 0;
  }
  //------------------------------------------------------------------D1
  if (digitalRead(A1) == LOW && clackD1 == 0)
  {
    if (!mode)
    { // mouse mode
      button = 0x01;
      update = 1;
    }
    else
    { //keyboard mode
      digitalWrite(5, HIGH);
      Bluetooth.sendKeyCode(0x50);
      delay(3);
      digitalWrite(5, LOW);
    }
    eastercounter = 0;
    clackD1 = 1;
  }
  if (digitalRead(A1) == HIGH)
  {
    if (clackD1 == 1 && !mode) //samo za misko // ce bos hotu tut za tipkovnco dej !mode dol
    {
      button = 0x00;
      update = 1;
    }
    clackD1 = 0;
  }
  //------------------------------------------------------------------D2
  if (digitalRead(A0) == LOW && clackD2 == 0)
  {
    digitalWrite(5, HIGH);
    if (!mode)
    { // mouse mode
      button = 0x02;
      update = 1;
    }
    else
    { //keyboard mode
      digitalWrite(5, HIGH);
      Bluetooth.sendKeyCode(0x4f);
      delay(3);
      digitalWrite(5, LOW);
    }
    eastercounter = 0;
    clackD2 = 1;
    delay(3);
    digitalWrite(5, LOW);
  }
  if (digitalRead(A0) == HIGH)
  {
    if (clackD2 == 1 && !mode)
    {
      button = 0x00;
      update = 1;
    }
    clackD2 = 0;
  }
  //------------------------------------------------------------------L1
  if (digitalRead(A4) == LOW)
  {

    if (!mode)
    { //mouse mode
      digitalWrite(5, HIGH);
      Bluetooth.sendDataByte(0x00, 0x10);
      delay(3);
      digitalWrite(5, LOW);
      delay(50);

    }
    else
    { //keyboard mode
      if (clackL1 == 0)
      {
        digitalWrite(5, HIGH);
        Bluetooth.sendDataByte(0x02, 0x00);
        delay(3);
        digitalWrite(5, LOW);
      }
    }
    eastercounter = 0;
    clackL1 = 1;
  }
  if (digitalRead(A4) == HIGH)
  {
    clackL1 = 0;
  }
  //------------------------------------------------------------------L2
  if (digitalRead(A3) == LOW && clackL2 == 0)
  {
    digitalWrite(5, HIGH);
    if (!mode)
    { //mouse mode
      Bluetooth.sendDataByte(0x00, 0x40);
    }
    else
    { //keyboard mode
      Bluetooth.sendDataByte(0x00, 0x80);
    }
    eastercounter = 0;
    clackL2 = 1;
    delay(3);
    digitalWrite(5, LOW);
  }
  if (digitalRead(A3) == HIGH)
  {
    clackL2 = 0;
  }
  //------------------------------------------------------------------L3
  if (digitalRead(A2) == LOW)
  {
    if (!mode)
    { //mouse mode
      digitalWrite(5, HIGH);
      Bluetooth.sendDataByte(0x00, 0x20);
      delay(3);
      digitalWrite(5, LOW);
      delay(50);
    }
    else
    { //keyboard mode
      if (clackL3 == 0)
      {
        digitalWrite(5, HIGH);
        Bluetooth.sendDataByte(0x01, 0x00);
        delay(3);
        digitalWrite(5, LOW);
      }
    }
    eastercounter = 0;
    clackL3 = 1;
  }
  if (digitalRead(A2) == HIGH)
  {
    clackL3 = 0;
  }
}

//joystick variables
int valx;
int valy;
int stagex;
int stagey;
bool click; //clik clak
int stagenumber = 25;
//byte button = 0x00;   //deklarian zgoraj & tenMagicButtons
//bool update = 0;      //deklarian zgoraj & tenMagicButtons
//int wheel = 0;        //deklarian zgoraj & tenMagicButtons

void joystickBTMouse()
{
  valx = analogRead(7);
  valy = analogRead(6);
  valx += 10; //value correction

  /*
    Serial.print("X: ");
    Serial.print(valx);
    Serial.print("  Y: ");
    Serial.println(valy);
    //*/

  stagex = ((float)valx / 1023) * stagenumber; //stagenumber ker bomo mel stagenumber stagov
  stagey = ((float)valy / 1023) * stagenumber; // _-stagenumber .. 0 .. stagenumber

  stagex -= (stagenumber / 2);
  stagey -= (stagenumber / 2);

  //Serial.println(analogRead(5));
  if (analogRead(5) < 50 && click == 0)
  {
    button = 0x01;
    Serial.println("Click!!");
    click = 1;
    update = 1;
  }
  if (click == 1 && analogRead(5) > 100) //10 da je mal tolerance
  {
    button = 0x00;
    Serial.println("Released");
    click = 0;
    update = 1;
  }

  if (stagex != 0)
    update = 1;
  if (stagey != 0)
    update = 1;

  if (update)
  {
    //Serial.println("Sending");
    Bluetooth.mouseMove(stagey, -stagex, button, wheel);
    digitalWrite(5, HIGH);
    eastercounter = 0;
    delay(6);

    update = 0;
  }
  else
  {
    digitalWrite(5, LOW);
  }
  /*
    Serial.print("X: ");
    Serial.print(stagex);
    Serial.print("  Y: ");
    Serial.println(stagey);
    //*/
}

//keytable
char keyTable[] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
                   'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '9', '8', '7', '6', '5', '4', '3', '2', '1', '0'//, '@', ';', ',', '.'
                  };
int tableLenght = strlen(keyTable) - 1;
int stage = 0; //1=up, 2=down, 3=left, 4=right
bool ready = 1; // if ready to chose another stage
int spaceRepet = 0;
bool enter = 0;
int leftcounter = 0;
int upcounter = 0;
int downcounter = 0;

int tablePos = 0; //where are you in keyTable

void joystickBTKeyboard()
{
  valx = analogRead(7);
  valy = analogRead(6);
  valx += 10;
  //zamenjam koordinate da je prilagojeno izdelku
  stagex = ((float)valy / 1023) * 20; //stagenumber ker bomo mel stagenumber stagov
  stagey = ((float)valx / 1023) * 20; // _-stagenumber .. 0 .. stagenumber

  stagex -= (20 / 2);
  stagey -= (20 / 2);

  if (ready)
  {
    if (stagey > 7)
    {
      //ready = 0;
      stage = 1;
      //Serial.println("Up");
    }
    if (stagey < -7)
    {
      //ready = 0;
      stage = 2;
      //Serial.println("Down");
    }
    if (stagex < -7)
    {
      //ready = 0;
      stage = 3;
      //Serial.println("Left");
    }
    if (stagex > 7)
    {
      ready = 0;
      stage = 4;
      //Serial.println("Right");
    }
  }

  if (stage == 2) //if Down
  {
    tablePos++;  //move in table
    stage = 0;   //reset stage
    if (tablePos > tableLenght) //if out of table
      tablePos = 0;
    //Serial.println(keyTable[tablePos]);
    if (spaceRepet < 3)
      Bluetooth.sendKeyCode(0x2a);
    spaceRepet = 0;
    delay(1);
    Bluetooth.sendChar(keyTable[tablePos]);
    digitalWrite(5, HIGH);
    eastercounter = 0;
    delay(2);
    digitalWrite(5, LOW);
    if (downcounter < 3)
      delay(200);
    else
      delay(100);
    downcounter++;
  }
  else
    downcounter = 0;

  if (stage == 1) //if Up
  {
    tablePos--;
    stage = 0;
    if (tablePos < 0)
      tablePos = tableLenght;
    //Serial.println(keyTable[tablePos]);
    if (spaceRepet < 3)
      Bluetooth.sendKeyCode(0x2a);
    spaceRepet = 0;
    delay(1);
    Bluetooth.sendChar(keyTable[tablePos]);
    digitalWrite(5, HIGH);
    eastercounter = 0;
    delay(2);
    digitalWrite(5, LOW);
    if (upcounter < 3)
      delay(200);
    else
      delay(100);
    upcounter++;
  }
  else
    upcounter = 0;

  if (stage == 3) //if Left
  {
    tablePos = 0;
    stage = 0;
    spaceRepet = 0;
    Bluetooth.sendKeyCode(0x2a);
    digitalWrite(5, HIGH);
    eastercounter = 0;
    delay(2);
    digitalWrite(5, LOW);
    //Serial.println("backspace");
    if (leftcounter < 3)
      delay(400);
    else
      delay(50);
    leftcounter++;
  }
  else
    leftcounter = 0;

  if (stage == 4) //if Right
  {
    /*if(keyTable[tablePos] == '.')
      Bluetooth.sendChar(' ');//*/
    tablePos = 0;
    stage = 0;
    enter = 1;
    spaceRepet++;
    if (spaceRepet < 3)
      Bluetooth.sendChar(keyTable[tablePos]);
    digitalWrite(5, HIGH);
    eastercounter = 0;
    delay(2);
    digitalWrite(5, LOW);
  }

  if (enter && spaceRepet >= 3)
  {
    Bluetooth.sendChar((int)13);
    digitalWrite(5, HIGH);
    eastercounter = 0;
    delay(2);
    digitalWrite(5, LOW);
    enter = 0;
    stage = 0;
  }

  /*
    Serial.print("tablepos: ");
    Serial.println(tablePos);
  */
  if (!ready)
    if (stagey > -2 && stagey < 2 && stagex > -2 && stagex < 2)
    {
      ready = 1;
      stage = 0;
      //Serial.println("Reset!!");
    }

  /*
    Serial.print("X: ");
    Serial.print(stagex);
    Serial.print("  Y: ");
    Serial.println(stagey);
    //*/
}

void rainbowinit()
{
  // Start off with red.
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;
}

int i = 0;
void rainbowloop()
{
  // Choose the colours to increment and decrement.
  for (int decColour = 0; decColour < 3; decColour += 1) {
    int incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade the two colours.
    for (int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;

      setColourRgbFull(rgbColour[0], rgbColour[1], rgbColour[2]);

      delay(1);
      if (digitalRead(13) == LOW)
      {
        outOfEaster = 1;
        return;
      }
    }
    //*
    if (!easterLightMode) //alternating green and red light
    {
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
    } else
    {
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
    }
    easterLightMode = !easterLightMode;//*/
  }
  //setColourRgb(0,0,0);
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red / 5);
  analogWrite(greenPin, green / 5);
  analogWrite(bluePin, blue / 5);
}
void setColourRgbFull(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void wordTyper(String str)
{
  digitalWrite(5, HIGH);
  for (int i = 0; i < str.length(); i++)
  {
    Bluetooth.sendChar(str.charAt(i));
    delay(10);
  }
  delay(200);
  digitalWrite(5, LOW);
}
