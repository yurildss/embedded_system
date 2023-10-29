#include "camadaHardware.h" // This library allows you to communicate with I2C devices.
#include <math.h> // This library is for calculate abs value of average - current value

hw_timer_t *My_timer = NULL;

void IRAM_ATTR onTimer() {
  flag_ready_to_read = true;
}

void detect_fall(float current_value) {
  if(index_history == (MOVING_AVERAGE_SIZE - 1 )){
    init_fall_detection = true;
    moving_average = (moving_average / MOVING_AVERAGE_SIZE);
  }

  if(init_fall_detection){
    if(fabs(moving_average - current_value) >= FALL_DETECTION_TRESHOLD){
        fall_detected = true;
    }
    
  }

  moving_average = ((moving_average + current_value) - history_accelerometer[index_history]);
  history_accelerometer[index_history] = current_value;

  index_history = (index_history + 1) % (MOVING_AVERAGE_SIZE);
}

void read_accelerometer() {

  read_i2c_MPU_6050(MPU_ADDRESS, MPU_FULL_SCALE_RANGE);

  accelerometer_x = readed_i2c[0];
  accelerometer_y = readed_i2c[1];
  accelerometer_z = readed_i2c[2];
  Serial.println();
  
  detect_fall(readed_i2c[1]);

}

void config_fallDetect() {
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 100000, true);
  timerAlarmEnable(My_timer);  //Just Enable

  for(int i = 0; i< MOVING_AVERAGE_SIZE; i++){
    history_accelerometer[i] = 0;
  }

  config_MPU_6050(MPU_ADDRESS, MPU_FULL_SCALE_RANGE);
}

void button_emergency_pressed() {
  if (millis() - time_last_pressed >= DEBOUNCE_DELAY) {
    
    time_last_pressed = millis();

    if(!first_click){
      first_click = true;
      first_click_time = millis();
    }else{
      first_click = false;
      if (millis() - first_click_time <= DOUBLE_CLICK_DELAY) {
        emergency_detected = true;
      }
      
    }
    
  }
}

void config_emergencyButton() {
  pinMode(EMERGENCY_BUTTON_PIN, INPUT_PULLUP); // Configura o pino como entrada com resistor de pull-up interno
  attachInterrupt(digitalPinToInterrupt(EMERGENCY_BUTTON_PIN), button_emergency_pressed, FALLING); // Configura a interrupção para ocorrer na transição de HIGH para LOW
}

void send_fall_notification() {
  Serial.println("queda detectada");
}

void send_emergency_notification() {
  Serial.println("emergencia detectada");
}
