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

#define servo_pin_Recharge 18
#define servo_pin_Lancer 13

// Tir Optimal
#define DISTANCE_TIR_OPTIMAL 5 // Distance optimale pour tirer en cm


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

// ===================== MotorController =====================

/* typedef struct MotorController
{
    int m_pi;
    int m_gpioControl;
    int m_gpioForward;
    int m_gpioBackward;
    int m_gpioMotor;
    int m_callbackID;
    int m_cbCount;
    int m_controllerCbCount;
    float m_kp;
    float m_ki;
    float m_integral;
    float m_targetSpeed;
    float m_speed;
    int m_power;
    int m_startPower;
    uint32_t m_prevCbTick;
    uint32_t m_prevUpdateTick;
    int m_errorCount;
    float m_saturationTime;
} MotorController;
void MotorController_init(MotorController *self, int pi, int gpioForward, int gpioBackward, int gpioControl);
void MotorController_quit(MotorController *self);
void MotorController_update(MotorController *self);
void MotorController_stop(MotorController *self);
void MotorController_setTargetSpeed(MotorController *self, float speed);
void MotorController_setController(MotorController *self, float kp, float ki);
void MotorController_setStartPower(MotorController *self, int startPower);
void MotorController_setBackward(MotorController *self, bool goBackward);
float MotorController_getSpeed(MotorController *self);
float MotorController_getDistance(MotorController *self);
void turn(MotorController *left, MotorController *right, int slotCount, float speed);
void drive(MotorController *left, MotorController *right, int slotCount, float speed); */


