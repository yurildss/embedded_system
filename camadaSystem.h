#include "camadaHardware.h" // This library allows you to communicate with I2C devices.

void config_Acelerometro(int MPU, int full_scale) {
  config_MPU_6050(MPU, full_scale);
}

void read_Acelerometro(int MPU,  float* sensorData, int full_scale) {
  read_i2c_MPU_6050(MPU, sensorData, full_scale);
}
