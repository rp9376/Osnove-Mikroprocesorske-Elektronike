
#include "BPLib.h"

BPLib BPMod;

void setup() {
  Serial.begin(9600);
  
  
    
    Serial.println("sm izvedu");
  while(1==1)
      {
        Serial.println("stuck in while"); 
        delay(1000);
      }
  
}

void loop() {
  delay(5000);
  Serial.println("I'm Here");

  BPMod.keyboardPress(BP_KEY_LEFT_ARROW,BP_MOD_NOMOD); //Send Scan code (KEY, MODEFIER key)
  BPMod.keyboardReleaseAll();

}
