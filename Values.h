/*
 * ETE Cícero Dias - NAVE Recife
 * Steaph Copyright
 * Authors: Anderson Laurentino
 * 
 * That code is resposable to control the best robot
 * of the OBR and Robocup Jr Rescue Line
 */
 
// **********************
//         PORTS
// **********************
#define MOTOR_LEFT1 1
#define MOTOR_LEFT2 2
#define MOTOR_RIGHT1 3
#define MOTOR_RIGHT2 4

#define SERVO_TRIGGER_1 9
#define SERVO_TRIGGER_2 10
#define SERVO_TRIGGER_3 2

#define ULTRA_LEFT 22
#define ULTRA_RIGHT 23

#define S0 24
#define S1 25
#define S2 26
#define S3 27
#define COLOR_LEFT 28
#define COLOR_RIGHT 29

#define LINE_ARRAY_LL 30
#define LINE_ARRAY_L 31
#define LINE_ARRAY_C 32
#define LINE_ARRAY_R 33
#define LINE_ARRAY_RR 34


// **********************
//        DEFINES
// **********************
#define OBSTACLE_MAX_MM 10

uint8_t MOVE_POWER = 230; // LEFT - RIGHT

double Kp = 1; // ERROR FACTOR -> Error multiplier
double Ki = 0.1; // INTEGARTION FACTOR -> Area multiplier
double Kd = 1; // DERIVATIVE FACTOR -> Delta ERROR multiplier

#define ROTATE_90_DEGREES_TIME 2000
#define ROTATE_90_DEGREES_PWR 200

#define MAX_TIME_GAP 2000
