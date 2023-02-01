/*int redPin= 11;
int greenPin = 9;
int bluePin = 10;
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void loop() {
  setColor(20, 0, 0);
  
}
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}*/

const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
unsigned int rgbColour[3];
void setup() {
  // Start off with the LED off.
  
  
         // Start off with red.
      
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0; 
}



  
void loop() {
rainbowloop();
}

void rainbowloop()
{
  // Choose the colours to increment and decrement.
  for (int decColour = 0; decColour < 3; decColour += 1) {
    int incColour = decColour == 2 ? 0 : decColour + 1;

    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;
      
      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[2]);
      delay(5);
    }
  }
  setColourRgb(0,0,0);
}

void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }
