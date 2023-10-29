#include "globalVars.h"
#include "camadaSystem.h"
void setup() {
  Serial.begin(9600);
  config_fallDetect();
  config_emergencyButton();
}

void loop() {

  if(fall_detected){
    send_fall_notification();
    fall_detected = false;
  }

  if(emergency_detected){
    send_emergency_notification();
    emergency_detected = false;
  }

  if(flag_ready_to_read){
    read_accelerometer();
    flag_ready_to_read = false; 
  }
}