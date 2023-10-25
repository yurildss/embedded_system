#include "Wire.h" // This library allows you to communicate with I2C devices.

void config_MPU_6050(int MPU, int full_scale) {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  int valueConfig = 0x00011000;

  /*
    Wire.write(0b00000000); // full_scale = 1 => fundo de escala do Giroscópio em +/-250°/s  | fundo de escala do Acelerometro em +/-2g
    Wire.write(0b00001000); // full_scale = 2 => fundo de escala do Giroscópio em +/-500°/s  | fundo de escala do Acelerometro em +/-4g
    Wire.write(0b00010000); // full_scale = 3 => fundo de escala do Giroscópio em +/-1000°/s | fundo de escala do Acelerometro em +/-8g
    Wire.write(0b00011000); // full_scale = 4 => fundo de escala do Giroscópio em +/-2000°/s | fundo de escala do Acelerometro em +/-16g
  */

  switch (full_scale) {
    case 1:
      valueConfig = 0x00000000;
      break;
    case 2:
      valueConfig = 0x00001000;
      break;
    case 3:
      valueConfig = 0x00010000;
      break;
    default:
      valueConfig = 0x00011000;
      break;
  }

  // Configura Giroscópio para fundo de escala desejado
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(valueConfig);
  Wire.endTransmission();

  // Configura Acelerometro para fundo de escala desejado
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(valueConfig);
  Wire.endTransmission();
}

void read_i2c_MPU_6050(int MPU,  float* sensorData, int full_scale) {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Solicita os dados ao sensor

  float full_scale_acc = 2048;
  /*
    full_scale = 1 => fundo de escala do Acelerometro +/-2g = 16384
    full_scale = 2 => fundo de escala do Acelerometro +/-4g = 8192
    full_scale = 3 => fundo de escala do Acelerometro +/-8g = 4096
    full_scale = 4 => fundo de escala do Acelerometro +/-16g = 2048
  */

  switch (full_scale) {
    case 1:
      full_scale_acc = 16384;
      break;
    case 2:
      full_scale_acc = 8192;
      break;
    case 3:
      full_scale_acc = 4096;
      break;
    default:
      full_scale_acc = 2048;
      break;
  }
  int16_t AccX = (Wire.read() << 8 | Wire.read()); //AccX
  int16_t AccY = (Wire.read() << 8 | Wire.read()); //AccY
  int16_t AccZ = (Wire.read() << 8 | Wire.read()); //AccZ

  sensorData[0] = (float) AccX;
  sensorData[1] = (float) AccY;
  sensorData[2] = (float) AccZ; 

  sensorData[0] = AccX/full_scale_acc;
  sensorData[1] = AccY/full_scale_acc;
  sensorData[2] = AccZ/full_scale_acc;

  Wire.endTransmission();
}
  