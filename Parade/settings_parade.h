#pragma once

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pigpiod_if2.h>
#include <fcntl.h>
#include <esieabot.h>

//------------------------------------------------------------------------------
// GPIO definitions
#define GPIO_BACKWARD_L 25
#define GPIO_BACKWARD_R 17
#define GPIO_FORWARD_L 23
#define GPIO_FORWARD_R 22
#define GPIO_MOTOR_CONTROL_L 24
#define GPIO_MOTOR_CONTROL_R 16
#define GPIO_LED 26
#define GPIO_BUTTON 6

// Vitesse minimale acceptée par un moteur asservi. 
#define MIN_SPEED 10.f

// servo moteur
#define servo_pinR 13
#define servo_pinL 18

// girlande led
#define Girlande_1 21
#define Girlande_2 20
#define Girlande_3 26
#define Girlande_4 19