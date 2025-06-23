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
#define LED_pin 21
#define Bouton_pin 20

// ===================== Button =====================
typedef struct Button
{
    int m_pi;
    int m_gpio;
    int m_callbackID;
    bool m_isPressed;
    int m_prevCbCount;
    int m_currCbCount;
} Button;
void Button_init(Button *self, int pi, int gpio);
void Button_quit(Button *self);
void Button_update(Button *self);
bool Button_isPressed(Button *self);

// ===================== LED =====================
typedef struct LED
{
    int m_pi;
    int m_gpio;
    uint32_t m_accu;
    uint32_t m_prevUpdateTick;
    uint32_t m_cycleTime;
    int m_cycleCount;
    int m_cycleIndex;
} LED;
void LED_init(LED *self, int pi, int gpio);
void LED_quit(LED *self);
void LED_update(LED *self);
void LED_blink(LED *self, int count, float cycleTime);
bool LED_isBlinking(LED *self);

// ===================== MotorController =====================
typedef struct MotorController
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
void drive(MotorController *left, MotorController *right, int slotCount, float speed);


// ===================== Tools =====================
int Int_clampAB(int value, int a, int b);
float Float_clamp01(float value);
float Float_clampAB(float value, float a, float b);
float Float_lerp(float value0, float value1, float t);
float Float_invLerp(float value0, float value1, float value);
float Float_remap(float src0, float src1, float dst0, float dst1, float value);