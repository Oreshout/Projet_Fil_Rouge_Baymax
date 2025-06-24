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
#include "esieabot-ai.h"
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

//Les PINs que l'on utilise
#define LED_pin 20
#define Bouton_pin 21

#define servo_pin 13

// ===================== Marker =====================

typedef struct Marker
{
   int id;      // l’id du marqueur
    int x;      // Sa position sur l’axe X en cm
    int y;      // Sa position sur l’axe Y en cm
    int z;      // Sa position sur l’axe Z en cm
    int pitch;  // Sa rotation (axe tangage) en degré
    int roll;   // Sa rotation (axe roulis) en degré
    int yaw;    // Sa rotation (axe lacet) en degré
} Marker;




