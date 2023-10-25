
#include "globalVars.h"
#include "camadaSystem.h"
void setup() {
  Serial.begin(9600);
  config_fallDetect();
}

void loop() {
  
  if(fall_detected){
    Serial.print("queda detectada");
    fall_detected = false;
  }

  if(flag_ready_to_read){
    read_accelerometer();
    flag_ready_to_read = false; 
  }
  
}