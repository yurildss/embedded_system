// VARIAVEIS PARA CONFIGURAÇÂO INTERNA DO MPU
const int MPU_ADDRESS = 0x68; // I2C address of the MPU-6050
const int MPU_FULL_SCALE_RANGE = 1; // full-scale 1 => +/-2g | full-scale 2 => +/-4g | full-scale 3 => +/-8g | full-scale 4 => +/-16g


//VARIAVEIS PARA TRATAMENTO E DETECÇÂO DE QUEDAS
bool fall_detected = false;
bool flag_ready_to_read = false;
float readed_i2c[2];
float history_accelerometer[5] = {0,0,0,0,0};
int index_history = 0;
float fall_detection_treshold = 1.5;
float accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data


//VARIAVEIS PARA TRATAMENTO E DETECÇÂO DE EMERGENCIA
const int EMERGENCY_BUTTON_PIN = 2;
unsigned long DEBOUNCE_DELAY = 50;
unsigned long DOUBLE_CLICK_DELAY = 500;
unsigned long time_last_pressed = millis();
unsigned long first_click_time = millis();
bool first_click = false;
bool emergency_detected = false;




