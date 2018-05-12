
// **********************
//         PORTS
// **********************
#define MOTOR_LEFT1 1
#define MOTOR_LEFT2 2
#define MOTOR_RIGHT1 3
#define MOTOR_RIGHT2 4

#define ULTRA_FRONT 22
#define ULTRA_LEFT 23
#define ULTRA_RIGHT 24

#define S0 26
#define S1 27
#define S2 28
#define S3 29
#define COLOR_LEFT 30
#define COLOR_RIGHT 31

#define LINE_ARRAY_LL A0
#define LINE_ARRAY_L A1
#define LINE_ARRAY_C A2
#define LINE_ARRAY_R A3
#define LINE_ARRAY_RR A4

uint8_t LINE_LIMIT = 600;
uint8_t LINE_CALIBRATION[5] = {0, 0, 0, 0, 0};


// **********************
//        Defines
// **********************

#define OBSTACLE_MAX_MM 10

uint8_t MOVE_POWER[2] = {200, 200};

uint8_t BLACK_WHITE[2] = {200, 150};
uint8_t WHITE_BLACK[2] = {150, 200};

uint8_t Kp = 1; // ERROR FACTOR -> Error multiplier
uint8_t Ki = 1; // INTEGARTION FACTOR -> Period increase multiplier
uint8_t Kd = 1; // DERIVATIVE FACTOR -> Delta ERROR multiplier

#define ROTATE_90_DEGREES_TIME 2000
#define ROTATE_90_DEGREES_PWR 200
