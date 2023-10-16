#include "camadaSystem.h"

const int MPU_ADDRESS = 0x68; // I2C address of the MPU-6050

 /*
    full-scale 1 => +/-250º/s e +/-2g
    full-scale 2 => +/-500º/s e +/-4g
    full-scale 3 => +/-1000º/s e +/-8g
    full-scale 4 => +/-2000º/s e +/-16g
*/
const int MPU_FULL_SCALE_RANGE = 1;

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data

float readed_i2c[7];

void setup() {
  Serial.begin(9600);
  config_Acelerometro(MPU_ADDRESS, MPU_FULL_SCALE_RANGE);
}

void loop() {
  read_Acelerometro(MPU_ADDRESS, readed_i2c, MPU_FULL_SCALE_RANGE);

  accelerometer_x = readed_i2c[0];
  accelerometer_y = readed_i2c[1];
  accelerometer_z = readed_i2c[2];
  temperature = readed_i2c[3];
  gyro_x = readed_i2c[4];
  gyro_y = readed_i2c[5];
  gyro_z = readed_i2c[6];
  
  // print out data
  Serial.print("aX = "); Serial.print(accelerometer_x);
  Serial.print(" | aY = "); Serial.print(accelerometer_y);
  Serial.print(" | aZ = "); Serial.print(accelerometer_z);
  Serial.print(" | gX = "); Serial.print(gyro_x);
  Serial.print(" | gY = "); Serial.print(gyro_y);
  Serial.print(" | gZ = "); Serial.print(gyro_z);
  Serial.println();
  
  // delay
  delay(1000);
}