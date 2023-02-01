#include <math.h>
void setup() {
  Serial.begin(115200);

}



void loop() {
  joystickNormal();
  delay(50);
}

int valx;
int valy;
int stagex;
int stagey;
int normalx;
int normaly;
int kvadrant;
float angle;
bool click;
int stagenumber=50; 
byte button = 0x00;
bool update = 0;

void joystickNormal()
{
  valx=analogRead(7);
  valy=analogRead(6);
  valx+=10;

  stagex=((float)valx/1023)*stagenumber; //stagenumber ker bomo mel stagenumber stagov
  stagey=((float)valy/1023)*stagenumber;
  stagex-=(stagenumber/2);
  stagey-=(stagenumber/2);

  if(stagex == 0 || stagey == 0)
  {
    normalx = stagex;
    normaly = stagey;
    kvadrant = 0;
  }
  else
  {
    int hip;
    if(stagex >= stagey)
      hip = stagex;
    else
      hip = stagey;

     if(stagex > 0)
       if(stagey > 0)
         kvadrant = 4;
       else
         kvadrant = 1;
     else
        if(stagey > 0)
         kvadrant = 3;
       else
         kvadrant = 2;
         
     angle = atan (abs(stagey)/abs(stagex));// * 57,3;
     normalx = abs (round (cos (angle) * hip));
     normaly = abs (round (sin (angle) * hip));
      
    if(kvadrant == 2)
      normaly = normaly *-1;
    else
    {
      if(kvadrant == 1)
      {
        normalx = normalx * (-1);
      }
      normalx = normalx * -1;
      normaly = normaly * -1;
    }
  
         
  }

  Serial.print("Angle: ");
  Serial.println(angle);
  /*
  Serial.print("X: ");
  Serial.print(normalx);
  Serial.print("  Y: ");
  Serial.println(normaly);
  //*/
  
  //*
  Serial.print("X: ");
  Serial.print(stagex);
  Serial.print("  Y: ");
  Serial.println(stagey);
  //*/
}
