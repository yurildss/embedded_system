const int MPU_ADDRESS = 0x68; // I2C address of the MPU-6050
 /*
    full-scale 1 => +/-2g
    full-scale 2 => +/-4g
    full-scale 3 => +/-8g  
    full-scale 4 => +/-16g
*/
const int MPU_FULL_SCALE_RANGE = 1;

bool fall_detected = false;
bool flag = false;
float readed_i2c[2];

float accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data