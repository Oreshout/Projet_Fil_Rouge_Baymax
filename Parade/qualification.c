#include "settings_parade.h"

int pi;

void set_servo_to_min(){
    set_servo_pulsewidth(pi, servo_pinR, 500); // Position finale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, 500); // Position finale // ! LEFT
}

void set_servo_to_max(){
    set_servo_pulsewidth(pi, servo_pinR, 1500); // Position finale // ! RIGHT
    set_servo_pulsewidth(pi, servo_pinL, 1500); // Position finale // ! LEFT
}

void gauche_droite(){
    set_servo_to_min();
    sleep(0.5);
    set_servo_to_max();
}

void drift(){
    gpio_write(pi, GPIO_FORWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);

    sleep(0.1);

    gpio_write(pi, GPIO_FORWARD_L, PI_LOW);
    gpio_write(pi, GPIO_FORWARD_R, PI_LOW);

    gpio_write(pi, GPIO_BACKWARD_L, PI_HIGH);
    gpio_write(pi, GPIO_BACKWARD_R, PI_HIGH);

    sleep(0.1);

    gpio_write(pi, GPIO_BACKWARD_L, PI_LOW);
    gpio_write(pi, GPIO_BACKWARD_R, PI_LOW);
}

void triple_drift(){
    for (int i = 0; i < 3; i++)
    {
        gpio_write(pi, GPIO_FORWARD_L, PI_HIGH);
        gpio_write(pi, GPIO_FORWARD_R, PI_HIGH);

        sleep(0.1);

        gpio_write(pi, GPIO_FORWARD_L, PI_LOW);
        gpio_write(pi, GPIO_FORWARD_R, PI_LOW);
    }
    sleep(0.3);
    for (int i = 0; i < 3; i++)
    {
        gpio_write(pi, GPIO_BACKWARD_L, PI_HIGH);
        gpio_write(pi, GPIO_BACKWARD_R, PI_HIGH);

        sleep(0.1);

        gpio_write(pi, GPIO_BACKWARD_L, PI_LOW);
        gpio_write(pi, GPIO_BACKWARD_R, PI_LOW);
    }
}

int main(){
    pi = pigpio_start(NULL, NULL);

    float kp = 4.0f; // Valeurs conseillées pour le contrôleur PI
    float ki = 2.0f;

    float speed = 50.f;

    MotorController motorL; // Création de lobjet contrôleur moteur
    MotorController_init(&motorL, pi, GPIO_FORWARD_L, GPIO_BACKWARD_L, GPIO_MOTOR_CONTROL_L); // Initialisation du contrôleur moteur

    MotorController motorR; // Création de lobjet contrôleur moteur
    MotorController_init(&motorR, pi, GPIO_FORWARD_R, GPIO_BACKWARD_R, GPIO_MOTOR_CONTROL_R); // Initialisation du contrôleur moteur

    MotorController_setStartPower(&motorL, 110);
    MotorController_setController(&motorL, kp, ki);

    MotorController_setStartPower(&motorR, 110);
    MotorController_setController(&motorR, kp, ki);

    MotorController_stop(&motorL);
    MotorController_stop(&motorR);

    //programme principal
    sleep(1);
    printf("starting\n");

    for (int i = 0; i < 5; i++)
    {
        gauche_droite();
        sleep(0.3);
    }

    sleep(3);
    printf("drifting\n");

    drift();
    sleep(0.2);
    drift();
    sleep(0.2);


    sleep(3);
    printf("le grand final\n");
    triple_drift();

    

    return 0;
}