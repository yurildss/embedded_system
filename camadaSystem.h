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



String SendHTML(String per) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta http-equiv=\"refresh\" content=\"0.5\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<link href=\"https://fonts.googleapis.com/css?family=Open+Sans:300,400,600\" rel=\"stylesheet\">\n";
  ptr += "<title>MEDIDOR NÍVEL E AUTOMATIZADOR DO RESERVATÓRIO</title>\n";
  ptr += "<style>html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #333333;}\n";
  ptr += "body{margin-top: 50px;}\n";
  ptr += "h1 {margin: 50px auto 30px;}\n";
  ptr += ".side-by-side{display: inline-block;vertical-align: middle;position: relative;}\n";
  ptr += ".humidity-icon{background-color: #3498db;width: 30px;height: 30px;border-radius: 50%;line-height: 36px;}\n";
  ptr += ".humidity-text{font-weight: 600;padding-left: 15px;font-size: 19px;width: 160px;text-align: left;}\n";
  ptr += ".humidity{font-weight: 300;font-size: 60px;color: #3498db;}\n";
  ptr += ".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -20px;top: 15px;}\n";
  ptr += ".data{padding: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>MEDIDOR DE NÍVEL E AUTOMATIZADOR DO RESERVATÓRIO</h1>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"data\">\n";
  ptr += "<div class=\"side-by-side humidity-icon\">\n";
  ptr += "<svg version=\"1.1\" id=\"Layer_2\" xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" x=\"0px\" y=\"0px\"\n\"; width=\"12px\" height=\"17.955px\" viewBox=\"0 0 13 17.955\" enable-background=\"new 0 0 13 17.955\" xml:space=\"preserve\">\n";
  ptr += "<path fill=\"#FFFFFF\" d=\"M1.819,6.217C3.139,4.064,6.5,0,6.5,0s3.363,4.064,4.681,6.217c1.793,2.926,2.133,5.05,1.571,7.057\n";
  ptr += "c-0.438,1.574-2.264,4.681-6.252,4.681c-3.988,0-5.813-3.107-6.252-4.681C-0.313,11.267,0.026,9.143,1.819,6.217\"></path>\n";
  ptr += "</svg>\n";
  ptr += "</div>\n";
  ptr += "<div class=\"side-by-side humidity-text\">Nivel da agua</div>\n";
  ptr += "<div class=\"side-by-side humidity\">";
  ptr += (String)per;
  ptr += "<span class=\"superscript\">%</span></div>\n";
  ptr += "</div>\n";
  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
