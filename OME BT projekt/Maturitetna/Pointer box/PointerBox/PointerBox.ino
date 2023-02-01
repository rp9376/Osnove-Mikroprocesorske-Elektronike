
#include "RN42BT.h"

RN42BT Bluetooth;

void setup() {
  pinMode(5, INPUT);
  
  Serial.begin(115200);  
}

bool buttonState;
bool butonclick=0;
void test()
{
  buttonState = digitalRead(5);
  if(buttonState == HIGH && butonclick == 0)
  {
    Serial.println("Pressed");
    Bluetooth.sendDataByte(0x80,0x00);
    butonclick = 1;
  }
  
  if(buttonState == LOW && butonclick == 1)
  {
    Serial.println("Released");
    butonclick = 0;
  }
  
}

void loop() {
  
  //Serial.println(digitalRead(5));
  //test();
 /* if(digitalRead(5)== HIGH)
  {
  joystickBTMouse();
  }
  
  else
  {
  joystickBTKeyboard();
  }
  //*/

  
  //test();
  Bluetooth.ManualConf();
  
  delay(15);
}


//joystick variables
int valx;
int valy;
int stagex;
int stagey;
bool click;
int stagenumber=50; 
byte button = 0x00;
bool update = 0;

void joystickBTMouse()
{
  valx=analogRead(7);
  valy=analogRead(6);
  valx+=10; //value correction
  
  /*
  Serial.print("X: ");
  Serial.print(valx);
  Serial.print("  Y: ");
  Serial.println(valy);
  //*/
  
  stagex=((float)valx/1023)*stagenumber; //stagenumber ker bomo mel stagenumber stagov
  stagey=((float)valy/1023)*stagenumber; // _-stagenumber .. 0 .. stagenumber
  
  stagex-=(stagenumber/2);
  stagey-=(stagenumber/2);
   
   Serial.println(analogRead(5));
   if(analogRead(5)==0 &&click==0)
  {
    button = 0x01;
    Serial.println("Click!!");
    click=1;
    update = 1;
  }
  if(click==1&&analogRead(5)>100) //10 da je mal tolerance
  {
    button = 0x00;
    Serial.println("Released");
    click=0;
    update = 1;
  }
  
  if(stagex !=0)
    update = 1;
  if(stagey !=0)
    update = 1;

  if(update)
  {
    //Serial.println("Sending");
    Bluetooth.mouseMove(stagex, stagey, button);
    update = 0;
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
'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '9', '8', '7', '6', '5', '4', '3', '2', '1', '0'};
int tableLenght = strlen(keyTable)-1;
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
    valx=analogRead(7);
    valy=analogRead(6);
    valx+=10;
  
    stagex=((float)valx/1023)*20; //stagenumber ker bomo mel stagenumber stagov
    stagey=((float)valy/1023)*20; // _-stagenumber .. 0 .. stagenumber
    
    stagex-=(20/2);
    stagey-=(20/2);

    if(ready)
    {
      if(stagey < -7)
      {
        //ready = 0;
        stage = 1;
        //Serial.println("Up");
      }
      if(stagey > 7)
      {
        //ready = 0;
        stage = 2;
        //Serial.println("Down");
      }
      if(stagex < -7)
      {
        //ready = 0;
        stage = 3;
        //Serial.println("Left");
      }
      if(stagex > 7)
      {
        ready = 0;
        stage = 4;
        //Serial.println("Right");
      }
    }

    if(stage == 2) //if Down
    {
      tablePos++;  //move in table
      stage = 0;   //reset stage
      if(tablePos > tableLenght)  //if out of table
        tablePos = 0;
      //Serial.println(keyTable[tablePos]);
      if(spaceRepet<3)
      Bluetooth.sendKeyCode(0x2a);
      spaceRepet=0;
      Bluetooth.sendChar(keyTable[tablePos]);
      if(downcounter<3)
      delay(200);
      else
      delay(100);
      downcounter++;
    }
    else
    downcounter = 0;
    
    if(stage == 1)  //if Up
    {
      tablePos--;
      stage = 0;
      if(tablePos < 0)
        tablePos = tableLenght; 
      //Serial.println(keyTable[tablePos]);
      if(spaceRepet<3)
      Bluetooth.sendKeyCode(0x2a);
      spaceRepet=0;
      Bluetooth.sendChar(keyTable[tablePos]);
      if(upcounter<3)
      delay(200);
      else
      delay(100);
      upcounter++;
    }
    else
    upcounter = 0;

    if(stage == 3)  //if Left
    {
      tablePos=0;
      stage = 0; 
      spaceRepet=0;
      Bluetooth.sendKeyCode(0x2a);
      //Serial.println("backspace");
      if(leftcounter<3)
      delay(400);
      else
      delay(50);
      leftcounter++;
    }
    else
    leftcounter = 0;

    if(stage == 4)  //if Right
    {
      tablePos=0;
      stage = 0;
      enter = 1;
      spaceRepet++;
      if(spaceRepet<3)
      Bluetooth.sendChar(keyTable[tablePos]);
    }

     

    if(enter && spaceRepet >= 3)
    {
      Bluetooth.sendChar((int)13);
      enter = 0;
      stage = 0;
    }


    /*
    Serial.print("tablepos: ");
    Serial.println(tablePos);
*/


    if(!ready)
      if(stagey > -2 && stagey < 2 && stagex > -2 && stagex < 2)
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
