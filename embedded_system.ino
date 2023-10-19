
#include "globalVars.h"
#include "camadaSystem.h"
void setup() {
  Serial.begin(9600);
  config_fallDetect();
}

void loop() {
  if(flag){
   accelerometer_x = readed_i2c[0];
  accelerometer_y = readed_i2c[1];
  accelerometer_z = readed_i2c[2];
  
  // print out data
  Serial.print("aX = "); Serial.print(accelerometer_x);
  Serial.print(" | aY = "); Serial.print(accelerometer_y);
  Serial.print(" | aZ = "); Serial.print(accelerometer_z);
  Serial.println();
  flag = false; 
  }
}