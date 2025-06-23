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
//#include <linux/joystick.h>


//------------------------------------------------------------------------------
// Définition des GPIO

#define GPIO_BACKWARD_L 25
#define GPIO_BACKWARD_R 17
#define GPIO_FORWARD_L 23
#define GPIO_FORWARD_R 22

#define GPIO_MOTOR_CONTROL_L 24
#define GPIO_MOTOR_CONTROL_R 16

#define GPIO_LED 26
#define GPIO_BUTTON 6

//------------------------------------------------------------------------------
// Prototypes de pigpiod pour dev en local

typedef void (*CBFuncEx_t)
    (int pi, unsigned user_gpio, unsigned level, uint32_t tick, void *userdata);

/*
int pigpio_start(const char *addrStr, const char *portStr);
void pigpio_stop(int pi);

int set_mode(int pi, unsigned gpio, unsigned mode);
int set_pull_up_down(int pi, unsigned gpio, unsigned pud);

int callback_ex(int pi, unsigned user_gpio, unsigned edge, CBFuncEx_t f, void *userdata);
int callback_cancel(unsigned callback_id);

uint32_t get_current_tick(int pi);
int gpio_write(int pi, unsigned gpio, unsigned level);
int gpio_trigger(int pi, unsigned user_gpio, unsigned pulseLen, unsigned level);

int set_PWM_dutycycle(int pi, unsigned user_gpio, unsigned dutycycle);
int get_PWM_dutycycle(int pi, unsigned user_gpio);
*/

#define PI_LOW 0
#define PI_HIGH 1
#define PI_INPUT 0
#define PI_OUTPUT 1
#define RISING_EDGE 0
#define FALLING_EDGE 1
#define EITHER_EDGE 2
#define PI_PUD_OFF 0
#define PI_PUD_DOWN 1
#define PI_PUD_UP 2*
#define LED_pin 21
#define Bouton_pin 20