#include "camadaHardware.h" // This library allows you to communicate with I2C devices.

hw_timer_t *My_timer = NULL;

void IRAM_ATTR onTimer() {
  flag_ready_to_read = true;
}

void detect_fall() {
  int abrupt_changes = 0;
    for (int i = 1; i < 5; i++) {
          float diff = (history_accelerometer[i] - history_accelerometer[i - 1]);
          if (diff > fall_detection_treshold) {
              Serial.print(history_accelerometer[i]);
              Serial.print(" | ");
              Serial.print(history_accelerometer[i - 1]);
              abrupt_changes++;
          }
      }
    fall_detected = (abrupt_changes >= 3);
    if(fall_detected){
      Serial.println();
    }
}

void read_accelerometer() {
  read_i2c_MPU_6050(MPU_ADDRESS, readed_i2c, MPU_FULL_SCALE_RANGE);

  accelerometer_x = readed_i2c[0];
  accelerometer_y = readed_i2c[1];
  accelerometer_z = readed_i2c[2];

  history_accelerometer[index_history] = accelerometer_y;

  index_history = (index_history + 1)%5;

  // print out data
  Serial.print("aX = "); Serial.print(accelerometer_x);
  Serial.print(" | aY = "); Serial.print(accelerometer_y);
  Serial.print(" | aZ = "); Serial.print(accelerometer_z);
  Serial.println();

  detect_fall();
}

void config_fallDetect() {
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 100000, true);
  timerAlarmEnable(My_timer);  //Just Enable

  config_MPU_6050(MPU_ADDRESS, MPU_FULL_SCALE_RANGE);
}
