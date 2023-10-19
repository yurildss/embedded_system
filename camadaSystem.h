#include "camadaHardware.h" // This library allows you to communicate with I2C devices.

hw_timer_t *My_timer = NULL;

void IRAM_ATTR onTimer() {
  read_i2c_MPU_6050(MPU_ADDRESS, readed_i2c, MPU_FULL_SCALE_RANGE);

  // float accelerometer_x = readed_i2c[0];
  // float accelerometer_y = readed_i2c[1];
  // float accelerometer_z = readed_i2c[2];

  flag = true;
}

void config_fallDetect() {
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 1000, true);
  timerAlarmEnable(My_timer);  //Just Enable

  config_MPU_6050(MPU_ADDRESS, MPU_FULL_SCALE_RANGE);
}
